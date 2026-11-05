#include "dw4/filelist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <errno.h>

struct resident { char *path; dw4_igb pack; int onetime,lua; };
struct dw4_filelist {
    dw4_mount *mount;
    dw4_scriptengine *engine;
    uint64_t scope;
    char stage[128],directory[160],error[512];
    struct resident directory_pack;
    struct resident *packs;
    size_t count;
    char **queue;
    size_t queued;
    unsigned phase;
    int once,failed,routing;
};
static char *copy(const char *s) {
    size_t n=strlen(s)+1;char *p=malloc(n);if(p)memcpy(p,s,n);return p;
}
static int fail(dw4_filelist *f,const char *what,const char *path) {
    snprintf(f->error,sizeof(f->error),"%s: %s",what,path?path:"");f->failed=1;return -1;
}
static void clear_queue(dw4_filelist *f) {
    for(size_t i=0;i<f->queued;i++)free(f->queue[i]);
    free(f->queue);f->queue=NULL;f->queued=0;
}
static int queue(dw4_filelist *f,const char *path) {
    /* Retail CFLsetName 0x372b50 compares exact strings, preserving first order. */
    for(size_t i=0;i<f->queued;i++)if(!strcmp(f->queue[i],path))return 0;
    char *name=copy(path);if(!name)return fail(f,"file queue allocation",path);
    char **p=realloc(f->queue,(f->queued+1)*sizeof(*p));
    if(!p){free(name);return fail(f,"file queue allocation",path);}
    f->queue=p;p[f->queued++]=name;return 0;
}
static uint32_t raw(const dw4_igb_record *r,unsigned ordinal) {
    for(uint32_t i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;
    return UINT32_MAX;
}
static uint32_t u32(const uint8_t *p) {
    return p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;
}
static int record(dw4_igb *g,uint32_t id,const char *kind,dw4_igb_record *r) {
    uint32_t off;
    if(dw4_igb_ref(g,id,&off,NULL)!=2 || !dw4_igb_decode(g,off,r))return -1;
    if(kind && strcmp(r->class_name,kind)){dw4_igb_record_free(r);memset(r,0,sizeof(*r));return -1;}
    return 0;
}
static const uint8_t *list(dw4_igb *g,uint32_t id,const char *kind,uint32_t *n) {
    dw4_igb_record r={0};uint32_t len=0;
    if(record(g,id,kind,&r))return NULL;
    *n=raw(&r,2);uint32_t capacity=raw(&r,3),array=raw(&r,4);
    dw4_igb_record_free(&r);
    const uint8_t *p=dw4_igb_block(g,array,&len);
    if(*n>INT_MAX || *n>capacity || (*n && (!p || *n>len/4)))return NULL;
    return *n?p:(const uint8_t *)"";
}
static const uint8_t *source_bytes(dw4_filelist *f,const char *path,uint32_t *size) {
    if(path[0]=='[') {
        char *end;errno=0;
        unsigned long pt=strtoul(path+1,&end,10);
        if(end==path+1 || *end!='.' || errno || pt>INT_MAX)return NULL;
        const char *second=end+1;errno=0;
        unsigned long entry=strtoul(second,&end,10);
        if(end==second || *end!=']' || end[1] || errno || entry>INT_MAX)return NULL;
        return dw4_mount_entry(f->mount,(int)pt,(int)entry,size,NULL);
    }
    const dw4_manifest_file *row=dw4_manifest_find(&f->mount->man,path);
    /* Root filenames also need retail case-insensitivity, without selecting
     * a different regional subdirectory through basename fallback. */
    if(!row && !strchr(path,'/'))
        for(uint32_t i=0;i<f->mount->man.nfiles;i++)
            if(!strcasecmp(f->mount->man.files[i].path,path)){row=f->mount->man.files+i;break;}
    return row?dw4_mount_entry(f->mount,row->pt,row->entry,size,NULL):NULL;
}
static int mounted_source(void *user,const char *path,const void **bytes,size_t *size) {
    dw4_filelist *f=user;uint32_t n=0;*bytes=source_bytes(f,path,&n);*size=n;return *bytes?0:2;
}
static void release_scene(dw4_filelist *f) {
    dw4_igb_close(&f->directory_pack.pack);free(f->directory_pack.path);
    memset(&f->directory_pack,0,sizeof(f->directory_pack));
    size_t kept=0;
    for(size_t i=0;i<f->count;i++) {
        struct resident r=f->packs[i];
        if(r.onetime)f->packs[kept++]=r;
        else {dw4_igb_close(&r.pack);free(r.path);}
    }
    f->count=kept;clear_queue(f);
}
dw4_filelist *dw4_filelist_open(dw4_mount *mount) {
    if(!mount)return NULL;
    dw4_filelist *f=calloc(1,sizeof(*f));if(f)f->mount=mount;return f;
}
void dw4_filelist_close(dw4_filelist *f) {
    if(!f)return;
    for(size_t i=0;i<f->count;i++){dw4_igb_close(&f->packs[i].pack);free(f->packs[i].path);}
    dw4_igb_close(&f->directory_pack.pack);free(f->directory_pack.path);
    free(f->packs);clear_queue(f);free(f);
}
static int load(dw4_filelist *f,const char *path,int once) {
    /* CFL uniqueness is within its queue, not between separate collections. */
    struct resident r={0};uint32_t size=0;
    const uint8_t *bytes=source_bytes(f,path,&size);
    if(!bytes)return fail(f,"missing stage asset",path);
    if(dw4_igb_open(&r.pack,bytes,size,0) || dw4_igb_refs_open(&r.pack)) {
        dw4_igb_close(&r.pack);return fail(f,"invalid stage pack",path);
    }
    r.lua=dw4_igb_find_class(&r.pack,"beLuaInfo")!=NULL;
    if(r.lua) {
        dw4_script *check=dw4_script_open(NULL,NULL);
        int n=check?dw4_script_collect_pack(check,&r.pack):-1;
        dw4_script_close(check);
        if(n<0){dw4_igb_close(&r.pack);return fail(f,"invalid Lua-info collection",path);}
    }
    r.path=copy(path);r.onetime=once;
    struct resident *p=r.path?realloc(f->packs,(f->count+1)*sizeof(*p)):NULL;
    if(!p){free(r.path);dw4_igb_close(&r.pack);return fail(f,"stage pack allocation",path);}
    f->packs=p;p[f->count++]=r;return 0;
}
static int collect(dw4_filelist *f,size_t begin) {
    for(size_t i=begin;i<f->count;i++)if(f->packs[i].lua &&
        dw4_script_collect_pack_scoped(dw4_scriptengine_vm(f->engine),f->scope,&f->packs[i].pack)<0)
        return fail(f,"Lua-info publication",f->packs[i].path);
    return 0;
}
int dw4_filelist_begin(dw4_filelist *f,dw4_scriptengine *engine,const char *stage,uint64_t scope) {
    if(!f || !engine || !stage || f->routing || !dw4_scriptengine_can_start(engine))return -1;
    release_scene(f);f->engine=engine;f->scope=scope;f->phase=0;f->failed=0;f->error[0]=0;
    size_t n=strlen(stage);
    if(n>=sizeof(f->stage))return fail(f,"stage name too long",stage);
    memcpy(f->stage,stage,n+1);
    if(n>=4 && !strcasecmp(f->stage+n-4,".igb"))f->stage[n-4]=0;
    snprintf(f->directory,sizeof(f->directory),"%s/lua",f->stage);
    char path[160];snprintf(path,sizeof(path),"%s.igb",f->stage);
    uint32_t size=0;const uint8_t *bytes=source_bytes(f,path,&size);
    dw4_igb g={0};dw4_igb_record info={0};char **names=NULL;uint32_t count=0;int found=0,rc=-1;
    if(!bytes || dw4_igb_open(&g,bytes,size,0) || dw4_igb_refs_open(&g)) {
        fail(f,"missing/invalid stage file list",path);goto done;
    }
    /* beFileListInfo._fnames (ordinal 6) -> named object list. Do not scan
     * bracket strings in unrelated records or content-pool bytes. */
    for(uint32_t id=0;id<g.table_n;id++) {
        if(g.id_kind[id]!=2 || record(&g,id,NULL,&info))continue;
        if(!strcmp(info.class_name,"beFileListInfo") && info.name && !strcasecmp(info.name,f->stage)) {
            if(found++){fail(f,"ambiguous stage file list",path);goto done;}
            uint32_t len;const uint8_t *ids=list(&g,raw(&info,6),"igNamedObjectList",&len);
            if(!ids){fail(f,"invalid stage filename list",path);goto done;}
            names=calloc(len?len:1,sizeof(*names));if(!names){fail(f,"stage filename allocation",path);goto done;}
            count=len;
            for(uint32_t i=0;i<len;i++) {
                dw4_igb_record name={0};
                if(record(&g,u32(ids+4*i),"igNamedObject",&name) || !name.name || !(names[i]=copy(name.name))) {
                    dw4_igb_record_free(&name);fail(f,"invalid stage filename reference",path);goto done;
                }
                dw4_igb_record_free(&name);
            }
        }
        dw4_igb_record_free(&info);memset(&info,0,sizeof(info));
    }
    if(!found){fail(f,"stage has no authored file list",path);goto done;}
    if(!f->once) {
        size_t old=f->count;
        if(load(f,"BecText.igb",1) || load(f,"_common/sbiallse.igb",1)) {
            while(f->count>old) {
                struct resident *r=f->packs+--f->count;
                dw4_igb_close(&r->pack);free(r->path);
            }
            goto done;
        }
        f->once=1;
    }
    size_t first=f->count;
    /* Retail phase 1 extracts /s filenames before phase 102 appends the rest. */
    for(int support=1;support>=0;support--)for(uint32_t i=0;i<count;i++) {
        size_t len=strlen(names[i]);int special=len>=2 && !strcmp(names[i]+len-2,"/s");
        if(special!=support)continue;
        if(special) {
            /* Keep the classification intact for the second pass. */
            char *plain=copy(names[i]);if(!plain){fail(f,"filename allocation",names[i]);goto done;}
            plain[len-2]=0;int result=load(f,plain,0);free(plain);if(result)goto done;
        } else if(load(f,names[i],0))goto done;
    }
    if(collect(f,first))goto done;
    dw4_script_source_set(dw4_scriptengine_vm(engine),mounted_source,f,f->directory);
    f->directory_pack.path=copy(path);
    if(!f->directory_pack.path){fail(f,"stage directory allocation",path);goto done;}
    f->directory_pack.pack=g;memset(&g,0,sizeof(g));
    f->phase=1;rc=0;
done:
    dw4_igb_record_free(&info);dw4_igb_close(&g);
    for(uint32_t i=0;i<count;i++)free(names[i]);
    free(names);return rc;
}
int dw4_filelist_shared(dw4_filelist *f) {
    if(!f || f->failed || f->phase!=1)return -1;
    if(dw4_scriptengine_startup(f->engine,DW4_SCRIPT_START_SHARED))return fail(f,"shared startup boundary",f->stage);
    const dw4_script_start_status *s=dw4_scriptengine_start_status(f->engine);
    if(s->func || s->boot)return fail(f,"original func/boot failed",dw4_script_error(dw4_scriptengine_vm(f->engine)));
    size_t first=f->count;
    for(size_t i=0;i<f->queued;i++)if(load(f,f->queue[i],0))return -1;
    if(collect(f,first))return -1;
    f->phase=2;return 0;
}
int dw4_filelist_route_assets(dw4_filelist *f,dw4_filelist_route route,void *user) {
    if(!f || f->failed || f->routing || f->phase!=2 || !route)return -1;
    f->routing=1;
    if(route(user,f->directory_pack.path,&f->directory_pack.pack,0)) {
        f->routing=0;return fail(f,"native stage directory routing failed",f->directory_pack.path);
    }
    for(size_t i=0;i<f->count;i++)if(route(user,f->packs[i].path,&f->packs[i].pack,f->packs[i].onetime)) {
        f->routing=0;return fail(f,"native stage object routing failed",f->packs[i].path);
    }
    f->routing=0;
    f->phase=3;return 0;
}
int dw4_filelist_bind_layers(dw4_filelist *f,dw4_filelist_bind bind,void *user) {
    if(!f || f->failed || f->routing || f->phase!=3 || !bind)return -1;
    f->routing=1;int rc=bind(user);f->routing=0;
    if(rc)return fail(f,"native layer binding failed",f->stage);
    f->phase=4;return 0;
}
int dw4_filelist_start(dw4_filelist *f) {
    if(!f || f->failed || f->phase!=4)return -1;
    if(dw4_scriptengine_startup(f->engine,DW4_SCRIPT_START_STAGE))return fail(f,"stage startup boundary",f->stage);
    const dw4_script_start_status *s=dw4_scriptengine_start_status(f->engine);
    if(s->text || s->start)return fail(f,"original text/start failed",dw4_script_error(dw4_scriptengine_vm(f->engine)));
    f->phase=5;return 0;
}
int dw4_filelist_first(dw4_filelist *f) {
    if(!f || f->failed || f->phase!=5)return -1;
    if(dw4_scriptengine_startup(f->engine,DW4_SCRIPT_START_FIRST))return fail(f,"first startup boundary",f->stage);
    if(dw4_scriptengine_start_status(f->engine)->first)return fail(f,"original first failed",dw4_script_error(dw4_scriptengine_vm(f->engine)));
    f->phase=6;return 0;
}
const char *dw4_filelist_error(const dw4_filelist *f){return f?f->error:"no file-list loader";}
const char *dw4_filelist_stage(const dw4_filelist *f){return f?f->stage:NULL;}
size_t dw4_filelist_count(const dw4_filelist *f){return f?f->count:0;}
const char *dw4_filelist_path(const dw4_filelist *f,size_t i){return f && i<f->count?f->packs[i].path:NULL;}
size_t dw4_filelist_queue_count(const dw4_filelist *f){return f?f->queued:0;}
const char *dw4_filelist_queue_path(const dw4_filelist *f,size_t i){return f && i<f->queued?f->queue[i]:NULL;}
int dw4_filelist_call(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    dw4_filelist *f=user;
    if(!f || f->failed)goto bad;
    if(!strcmp(method,"CFLclear") && !n){clear_queue(f);return 0;}
    if(!strcmp(method,"CFLsetName") && n==1 && a[0].type==DW4_SCRIPT_STRING && a[0].string &&
        !memchr(a[0].string,0,a[0].length) && strlen(a[0].string)==a[0].length) {
        if(queue(f,a[0].string)){snprintf(error,cap,"%s",f->error);return -1;}return 0;
    }
    if(!strcmp(method,"CFLgetFolderName") && !n) {
        *r=(dw4_script_value){DW4_SCRIPT_STRING,0,f->stage,strlen(f->stage)};return 0;
    }
    /* Retail USA 0x371ed0/0x371ee0/0x371f00 return integer 1. */
    if((!strcmp(method,"SYSgetArea") || !strcmp(method,"SYSgetCountry") || !strcmp(method,"SYSgetIsPackOnly")) && !n) {
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;
    }
bad:
    snprintf(error,cap,"file-list service unavailable/invalid: %s",method);return -1;
}
