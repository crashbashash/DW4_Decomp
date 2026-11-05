#include "dw4/stageobjects.h"
#include "dw4/arenapack.h"
#include "dw4/object.h"
#include "dw4/reflected.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pack {
    char *path;
    dw4_igb igb;
    dw4_scene scene;
    dw4_stageobject *infos;
    dw4_arena_pack objects;   /* the info instances (shallow) in the session arena */
    size_t count;
    struct pack *next;
};
struct layer { char *name; int visible,removed; };
struct dw4_stageobjects {
    struct pack *head,*tail;
    size_t count;
    struct layer *layers;
    size_t nlayers;
    dw4_layer_attachment *attachments;
    size_t nattachments;
    const dw4_stageobject *root;
    uint32_t parent_id;
    int failed,bound,actor_skins;
    char error[512];
    dw4_scriptservices *sd;
    uint64_t token;
};
static char *copy(const char *s) {
    size_t n=strlen(s)+1;char *p=malloc(n);if(p)memcpy(p,s,n);return p;
}
static int fail(dw4_stageobjects *s,const char *what,const char *path,uint32_t id) {
    snprintf(s->error,sizeof(s->error),"%s: %s object %u",what,path?path:"",id);
    s->failed=1;return -1;
}
static uint32_t raw(const dw4_igb_record *r,unsigned ordinal) {
    for(uint32_t i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;
    return UINT32_MAX;
}
static uint32_t u32(const uint8_t *p) { uint32_t v;memcpy(&v,p,4);return v; }
static int is_a(const char *name,const char *base) {
    for(unsigned depth=0;name && depth<64;depth++) {
        if(!strcmp(name,base))return 1;
        const dw4_metaobject *m=dw4_metaobject_find(name);name=m?m->parent:NULL;
    }
    return 0;
}
static int record(const dw4_igb *g,uint32_t id,dw4_igb_record *r) {
    uint32_t off;return dw4_igb_ref(g,id,&off,NULL)==2 && dw4_igb_decode(g,off,r)?0:-1;
}
static const uint8_t *list(dw4_igb *g,uint32_t id,const char *class_name,uint32_t *n) {
    dw4_igb_record r={0};
    if(record(g,id,&r))return NULL;
    if(strcmp(r.class_name,class_name)){dw4_igb_record_free(&r);return NULL;}
    *n=raw(&r,2);uint32_t cap=raw(&r,3),block=raw(&r,4),len=0;
    dw4_igb_record_free(&r);const uint8_t *p=dw4_igb_block(g,block,&len);
    if(*n>INT_MAX || *n>cap || (*n && (!p || *n>len/4)))return NULL;
    return *n?p:(const uint8_t *)"";
}
static void pack_close(struct pack *p) {
    if(!p)return;
    dw4_arena *a=dw4_session_arena();
    if(a)dw4_arena_pack_release(a,&p->objects);else dw4_arena_pack_free(&p->objects);
    free(p->infos);dw4_scene_close(&p->scene);
    dw4_igb_close(&p->igb);free(p->path);free(p);
}
dw4_stageobjects *dw4_stageobjects_open(void) { return calloc(1,sizeof(dw4_stageobjects)); }
void dw4_stageobjects_actor_skins(dw4_stageobjects *s,int on) { if(s && !s->head)s->actor_skins=!!on; }
void dw4_stageobjects_close(dw4_stageobjects *s) {
    if(!s)return;
    if(s->sd)dw4_scriptservices_unregister(s->sd,s->token);
    struct pack *p=s->head;
    while(p){struct pack *next=p->next;pack_close(p);p=next;}
    for(size_t i=0;i<s->nlayers;i++)free(s->layers[i].name);
    free(s->layers);free(s->attachments);free(s);
}
int dw4_stageobjects_route(void *user,const char *path,dw4_igb *g,int once) {
    dw4_stageobjects *s=user;
    if(!s || s->failed || s->bound || !g || !path)return -1;
    struct pack *p=calloc(1,sizeof(*p));
    if(!p)return fail(s,"native pack allocation",path,0);
    p->path=copy(path);
    uint32_t bad_id=0;
    if(!p->path || dw4_igb_open(&p->igb,g->data,g->size,0) || dw4_igb_refs_open(&p->igb))goto bad;
    /* Archive completion exposes the igInfoList, not every record in the pack.
     * Enumerate its reference array in authored order, retaining duplicates.
     * No nested model/action data or orphan info is independently published. */
    uint32_t root=UINT32_MAX;
    for(uint32_t id=0;id<p->igb.table_n;id++)if(p->igb.id_kind[id]==2) {
        dw4_igb_record r={0};if(record(&p->igb,id,&r))goto bad;
        int found=!strcmp(r.class_name,"igInfoList");dw4_igb_record_free(&r);
        if(found){if(root!=UINT32_MAX)goto bad;root=id;}
    }
    if(root!=UINT32_MAX) {
        uint32_t n;const uint8_t *ids=list(&p->igb,root,"igInfoList",&n);if(!ids)goto bad;
        p->infos=calloc(n?n:1,sizeof(*p->infos));
        dw4_arena *arena=dw4_session_arena();
        if(!p->infos || !arena)goto bad;
        /* The info objects come first: one shallow load of every listed id, so duplicate ids share an instance. */
        uint32_t *roots=n?malloc(n*sizeof(*roots)):NULL;
        if(n && !roots)goto bad;
        for(uint32_t i=0;i<n;i++)roots[i]=u32(ids+4*i);
        char why[160];int loaded=n?dw4_arena_pack_load_roots(arena,DW4_REGION_PERSISTENT,&p->igb,roots,n,&p->objects,why,sizeof why):0;
        free(roots);if(loaded)goto bad;
        for(uint32_t i=0;i<n;i++) {
            uint32_t id=u32(ids+4*i);bad_id=id;dw4_igb_record r={0};
            if(record(&p->igb,id,&r))goto bad;
            int valid=is_a(r.class_name,"igInfo");
            for(uint32_t k=0;k<r.nvalues && valid;k++) {
                dw4_igb_value *v=r.values+k;
                if(v->raw==UINT32_MAX)continue;
                if(v->type==0)valid=dw4_igb_ref(&p->igb,v->raw,NULL,NULL)==2;
                else if(v->type==7)valid=dw4_igb_ref(&p->igb,v->raw,NULL,NULL)==1;
            }
            dw4_handle h=valid?dw4_arena_pack_handle(&p->objects,id):(dw4_handle){0};
            dw4_igb_record_free(&r);if(!h.off)goto bad;   /* an unknown class or a malformed record */
            p->count++;
            p->infos[i]=(dw4_stageobject){p->path,id,once,h,&p->igb,&p->scene,arena};
        }
        if((s->actor_skins?dw4_scene_load_actor_preview:dw4_scene_load)(&p->scene,g->data,g->size))goto bad;
    }
    if(s->tail)s->tail->next=p;else s->head=p;
    s->tail=p;s->count+=p->count;return 0;
bad:
    pack_close(p);return fail(s,"invalid native info collection",path,bad_id);
}
/* ---- typed reads of the info instances ---------------------------------------------------------------------------------------- */
const char *dw4_stageobject_class(const dw4_stageobject *o) {
    if(!o || !o->arena)return "";
    const char *n=dw4_class_name(o->arena,dw4_arena_object_vtable(o->arena,o->object));return n?n:"";
}
static const char *arena_string(const dw4_stageobject *o,int32_t handle) {
    return handle?(const char *)dw4_arena_at(o->arena,(dw4_handle){(uint32_t)handle},1):NULL;
}
const char *dw4_stageobject_name(const dw4_stageobject *o) {
    const igNamedObject *n=o && o->arena?DW4_ARENA_OBJ(o->arena,igNamedObject,o->object):NULL;
    return n?arena_string(o,n->_name):NULL;
}
const char *dw4_stageobject_kind_string(const dw4_stageobject *o) {
    if(!o || !o->arena || !dw4_arena_object_is(o->arena,o->object,dw4_metaobject_find("beModelCtrlInfo")->vtable))return NULL;
    const beModelCtrlInfo *m=DW4_ARENA_OBJ(o->arena,beModelCtrlInfo,o->object);
    return m?arena_string(o,m->_kindString):NULL;
}
int dw4_stageobject_rgba(const dw4_stageobject *o,float rgba[4]) {
    rgba[0]=rgba[1]=rgba[2]=rgba[3]=0;
    if(!o || !o->arena || !dw4_arena_object_is(o->arena,o->object,dw4_metaobject_find("beBkColorInfo")->vtable))return -1;
    /* igVec4fMetaField is 16 bytes at +28; the reflected struct names only its first word */
    const uint8_t *b=dw4_arena_at(o->arena,o->object,offsetof(beBkColorInfo,_rgba)+16);
    if(!b)return -1;
    memcpy(rgba,b+offsetof(beBkColorInfo,_rgba),16);return 0;
}
int dw4_stageobject_same(const dw4_stageobject *a,const dw4_stageobject *b) { return a && b && a->arena==b->arena && a->object.off==b->object.off; }
uint32_t dw4_stageobject_ref_id(const dw4_stageobject *o,const char *field) {
    dw4_igb_record r={0};dw4_object x={0};uint32_t id=UINT32_MAX;
    if(!o || record(o->igb,o->id,&r))return id;
    if(!dw4_object_from_record(&x,o->igb,&r)){id=dw4_object_get_ref(&x,field);dw4_object_free(&x);}
    dw4_igb_record_free(&r);return id;
}
size_t dw4_stageobjects_count(const dw4_stageobjects *s) { return s && !s->failed?s->count:0; }
const dw4_stageobject *dw4_stageobjects_at(const dw4_stageobjects *s,size_t n) {
    if(!s || s->failed)return NULL;
    for(struct pack *p=s->head;p;p=p->next){if(n<p->count)return p->infos+n;n-=p->count;}
    return NULL;
}
const dw4_stageobject *dw4_stageobjects_find(const dw4_stageobjects *s,const char *kind,const char *name,size_t occurrence) {
    if(!s || s->failed || !kind)return NULL;
    for(struct pack *p=s->head;p;p=p->next)for(size_t i=0;i<p->count;i++) {
        const dw4_stageobject *o=p->infos+i;
        if(strcmp(dw4_stageobject_class(o),kind) || (name && (!dw4_stageobject_name(o) || strcmp(dw4_stageobject_name(o),name))))continue;
        if(!occurrence--)return o;
    }
    return NULL;
}
static int layer_add(dw4_stageobjects *s,const char *name) {
    char *c=copy(name);if(!c)return -1;
    struct layer *p=realloc(s->layers,(s->nlayers+1)*sizeof(*p));if(!p){free(c);return -1;}
    s->layers=p;p[s->nlayers++]=(struct layer){.name=c};return 0;
}
static size_t layer_find(const dw4_stageobjects *s,const char *name) {
    for(size_t i=0;i<s->nlayers;i++)if(!strcmp(s->layers[i].name,name))return i;
    return s->nlayers-1; /* Retail unmatched roots attach to NONE. */
}
static int attach(dw4_stageobjects *s,const dw4_stageobject *o,uint32_t root) {
    struct pack *p=s->head;while(p && &p->scene!=o->scene)p=p->next;
    dw4_igb_record r={0};if(!p || record(&p->igb,root,&r))return -1;
    if(!is_a(r.class_name,"igNode")){dw4_igb_record_free(&r);return -1;}
    const char *name=r.name?r.name:"";
    if(!strcmp(name,"ROOTATTR")) {
        if(!is_a(r.class_name,"igGroup")){dw4_igb_record_free(&r);return -1;}
        dw4_igb_record_free(&r);
        /* Renderer graph walk follows this info's authored node references.
         * Keep the parent edge separately: cross-pack handles never alias. */
        for(uint32_t i=0;i<p->scene.nnode;i++) {
            const dw4_scene_node *node=p->scene.node+i;
            if(!node->name || strcmp(node->name,"LAYERPARENT") || !is_a(node->class_name,"igAttrSet"))continue;
            uint32_t ancestor=i;
            while(ancestor!=UINT32_MAX && p->scene.node[ancestor].id!=root)
                ancestor=p->scene.node[ancestor].parent;
            if(ancestor!=UINT32_MAX){s->root=o;s->parent_id=node->id;return 0;}
        }
        return -1;
    }
    size_t layer=layer_find(s,name);
    dw4_igb_record_free(&r);
    dw4_layer_attachment *a=realloc(s->attachments,(s->nattachments+1)*sizeof(*a));if(!a)return -1;
    s->attachments=a;a[s->nattachments++]=(dw4_layer_attachment){o,root,layer};return 0;
}
int dw4_stageobjects_bind(dw4_stageobjects *s) {
    if(!s || s->failed || s->bound)return -1;
    /* Layer groups are referenced data, never sorted names or every group
     * record. The integrated title/lobby rosters have one layer definition.
     * Reject additional definitions until their repeated ORDER ownership is
     * established, rather than guessing a winning definition. */
    const dw4_stageobject *definition=NULL;struct pack *owner=NULL;
    for(struct pack *p=s->head;p;p=p->next)for(size_t i=0;i<p->count;i++)
        if(!strcmp(dw4_stageobject_class(p->infos+i),"beLayerInfo")) {
            if(definition)return fail(s,"multiple native layer definitions unsupported",p->path,p->infos[i].id);
            definition=p->infos+i;owner=p;
        }
    if(!definition)return fail(s,"missing authored layer definition",NULL,0);
    dw4_igb_record r={0};if(record(&owner->igb,definition->id,&r))goto bad;
    uint32_t groups=raw(&r,7),n;dw4_igb_record_free(&r);
    const uint8_t *ids=list(&owner->igb,groups,"beLayerGroupList",&n);if(!ids)goto bad;
    for(uint32_t i=0;i<n;i++) {
        if(record(&owner->igb,u32(ids+4*i),&r))goto bad;
        int ok=!strcmp(r.class_name,"beLayerGroup") && r.name && !layer_add(s,r.name);
        dw4_igb_record_free(&r);memset(&r,0,sizeof(r));if(!ok)goto bad;
    }
    if(layer_add(s,"NONE"))goto bad;
    for(struct pack *p=s->head;p;p=p->next)for(size_t i=0;i<p->count;i++) {
        dw4_stageobject *o=p->infos+i;
        if(strcmp(dw4_stageobject_class(o),"igSceneInfo"))continue;
        if(record(&p->igb,o->id,&r))goto bad;
        uint32_t root=raw(&r,5);dw4_igb_record_free(&r);memset(&r,0,sizeof(r));
        if(root==UINT32_MAX)continue;
        if(record(&p->igb,root,&r))goto bad;
        int paths=!strcmp(r.class_name,"igGraphPathList");dw4_igb_record_free(&r);memset(&r,0,sizeof(r));
        if(paths) {
            uint32_t count;const uint8_t *entries=list(&p->igb,root,"igGraphPathList",&count);if(!entries)goto bad;
            for(uint32_t j=0;j<count;j++) {
                if(record(&p->igb,u32(entries+4*j),&r))goto bad;
                int valid=!strcmp(r.class_name,"igGraphPath");uint32_t nodes=raw(&r,2);
                dw4_igb_record_free(&r);memset(&r,0,sizeof(r));if(!valid)goto bad;
                uint32_t len;const uint8_t *roots=list(&p->igb,nodes,"igNodeList",&len);if(!roots)goto bad;
                /* A graph path is an ancestor chain, not independent roots. */
                if(len && attach(s,o,u32(roots)))goto bad;
            }
        } else if(attach(s,o,root))goto bad;
    }
    if(!s->root)goto bad;
    s->bound=1;
    for(size_t i=0;i<s->nlayers;i++)if(!strcmp(s->layers[i].name,"LOADING")){s->layers[i].visible=1;break;}
    return 0;
bad:
    dw4_igb_record_free(&r);return fail(s,"invalid authored layer binding",definition->path,definition->id);
}
int dw4_stageobjects_bind_layers(void *s) { return dw4_stageobjects_bind(s); }
const char *dw4_stageobjects_error(const dw4_stageobjects *s) { return s?s->error:"no native scene objects"; }
const dw4_stageobject *dw4_stageobjects_root(const dw4_stageobjects *s,uint32_t *parent_id) {
    if(!s || !s->bound || s->failed)return NULL;
    if(parent_id)*parent_id=s->parent_id;
    return s->root;
}
size_t dw4_stageobjects_layers(const dw4_stageobjects *s) { return s && s->bound && !s->failed?s->nlayers:0; }
const char *dw4_stageobjects_layer(const dw4_stageobjects *s,size_t i) { return i<dw4_stageobjects_layers(s)?s->layers[i].name:NULL; }
int dw4_stageobjects_layer_visible(const dw4_stageobjects *s,size_t i) { return i<dw4_stageobjects_layers(s) && !s->layers[i].removed?s->layers[i].visible:0; }
size_t dw4_stageobjects_attachments(const dw4_stageobjects *s) { return s && s->bound && !s->failed?s->nattachments:0; }
const dw4_layer_attachment *dw4_stageobjects_attachment(const dw4_stageobjects *s,size_t i) { return i<dw4_stageobjects_attachments(s)?s->attachments+i:NULL; }
static int string(const dw4_script_value *v) {
    return v->type==DW4_SCRIPT_STRING && v->string && strlen(v->string)==v->length;
}
int dw4_stageobjects_layer_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    dw4_stageobjects *s=user;
    if(!dw4_stageobjects_layers(s) || strcmp(method,"sd") || n!=5 || !string(a+3) || !string(a+4))goto bad;
    /* Retail SWITCH name/action targets the first equal layer. ALL FLIP is a
     * no-op; ALL CLR/SET changes every mask bit (0x389718 onward). */
    if(!strcmp(a[3].string,"REMOVE")) {
        /* Loading's external roots retire without moving retained layer ids. */
        for(size_t i=0;i<s->nlayers;i++)if(!strcmp(s->layers[i].name,a[4].string)) {
            s->layers[i].visible=0;s->layers[i].removed=1;
            for(size_t j=s->nattachments;j>0;j--)if(s->attachments[j-1].layer==i){
                memmove(s->attachments+j-1,s->attachments+j,(s->nattachments-j)*sizeof *s->attachments);s->nattachments--;
            }
            break;
        }
        *r=(dw4_script_value){0};return 0;
    }
    if(strcmp(a[3].string,"SWITCH"))goto bad;
    char name[128],action[32];const char *value=a[4].string;
    const char *space=strchr(value,'/');
    if(!space || (size_t)(space-value)>=sizeof(name) || strlen(space+1)>=sizeof(action))goto bad;
    memcpy(name,value,(size_t)(space-value));name[space-value]=0;strcpy(action,space+1);
    int operation=(!strcmp(action,"CLR") || !strcmp(action,"DISPOFF"))?0:
        (!strcmp(action,"SET") || !strcmp(action,"DISPON"))?1:!strcmp(action,"FLIP")?2:-1;
    if(operation<0)goto bad;
    if(!strcmp(name,"ALL")) {
        if(operation!=2)for(size_t i=0;i<s->nlayers;i++)if(!s->layers[i].removed)s->layers[i].visible=operation;
    } else {
        for(size_t i=0;i<s->nlayers;i++)if(!s->layers[i].removed && !strcmp(s->layers[i].name,name)) {
            s->layers[i].visible=operation==2?!s->layers[i].visible:operation;break;
        }
    }
    *r=(dw4_script_value){0};return 0;
bad:
    snprintf(error,cap,"unsupported/invalid LAYERCTL call: %s",method);return -1;
}
int dw4_stageobjects_switch_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    dw4_stageobjects *s=user;*r=(dw4_script_value){0};
    if(!s || strcmp(method,"sd") || n!=4 || !string(a+3) ||
       (strcmp(a[3].string,"ALLON") && strcmp(a[3].string,"ALLOFF")))goto bad;
    for(size_t i=0;i<s->count;i++) {
        const dw4_stageobject *info=dw4_stageobjects_at(s,i);
        if(strcmp(dw4_stageobject_class(info),"beSwitchCtrlInfo"))continue;
        dw4_igb_record row={0};if(record(info->igb,info->id,&row))goto bad;
        uint32_t id=raw(&row,7);dw4_igb_record_free(&row);
        dw4_scene *scene=info->scene;unsigned node=0;
        while(node<scene->nnode && scene->node[node].id!=id)node++;
        if(node==scene->nnode || dw4_scene_switch_set(scene,node,-1,!strcmp(a[3].string,"ALLON")))goto bad;
    }
    return 0;
bad:snprintf(error,cap,"unsupported or unresolved SWITCHCTRL %s",method);return -1;
}
int dw4_stageobjects_publish(dw4_stageobjects *s,dw4_scriptservices *sd,uint64_t scope) {
    if(!dw4_stageobjects_layers(s) || !sd || s->token)return -1;
    s->token=dw4_scriptservices_register(sd,scope,"LAYERCTL",NULL,-1,1,dw4_stageobjects_layer_service,s);
    if(!s->token)return fail(s,"layer receiver publication",NULL,0);
    s->sd=sd;return 0;
}
