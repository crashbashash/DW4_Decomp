/* Original title text callbacks and localized authored glyph layout. */
#include "dw4/fronttext.h"
#include "dw4/fontlayout.h"
#include "dw4/scene.h"
#include "dw4/scriptengine.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
struct string {uint32_t *code;size_t count;};
struct row {char group[32],name[32];float matrix[16],width;int align,face,visible;
    dw4_font_vertex *vertices;size_t count;uint32_t *dynamic;size_t ndynamic;uint8_t luminance;};
struct dw4_fronttext {dw4_fefont face[2];dw4_tex atlas[2];struct row *row;size_t nrow;
    struct string *string;size_t nstring;dw4_be_state state;dw4_scriptengine *engine;
    dw4_ui_draw *draw;size_t capacity;char error[256];};
static uint32_t field(const dw4_igb_record *r,unsigned ordinal)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;return UINT32_MAX;}
static const char *string_field(const dw4_igb *g,const dw4_igb_record *r,unsigned ordinal)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal && r->values[i].type==4)return (const char *)g->data+r->values[i].voff;return NULL;}
static int record(const dw4_igb *g,uint32_t id,dw4_igb_record *r)
{return id<g->table_n && g->id_kind[id]==2 && dw4_igb_decode(g,g->id_off[id],r);}
static const uint8_t *list(const dw4_igb *g,uint32_t id,uint32_t *count)
{
    dw4_igb_record r={0};if(!record(g,id,&r))return NULL;
    *count=field(&r,2);uint32_t block=field(&r,4),size;dw4_igb_record_free(&r);
    const uint8_t *bytes=dw4_igb_block(g,block,&size);
    return bytes && *count<=size/4?bytes:NULL;
}
static uint32_t u32(const uint8_t *p){uint32_t v;memcpy(&v,p,4);return v;}
static int unicode(dw4_fronttext *t,const dw4_igb *g,uint32_t id)
{
    uint32_t count;const uint8_t *ids=list(g,id,&count);if(!ids || count>4096)return -1;
    t->string=calloc(count,sizeof(*t->string));if(!t->string)return -1;t->nstring=count;
    for(uint32_t i=0;i<count;i++){
        dw4_igb_record r={0};if(!record(g,u32(ids+4*i),&r) || strcmp(r.class_name,"beUnicodeObj")){dw4_igb_record_free(&r);return -1;}
        uint32_t bytes;const uint8_t *raw=dw4_igb_block(g,field(&r,3),&bytes);dw4_igb_record_free(&r);
        if(!raw || bytes%2)return -1;
        struct string *s=t->string+i;s->code=calloc(bytes/2+1,sizeof(*s->code));if(!s->code)return -1;
        for(uint32_t j=0;j<bytes;j+=2){uint32_t code=raw[j]|(uint32_t)raw[j+1]<<8;if(!code)break;s->code[s->count++]=code;}
    }
    return 0;
}
static int fonts(dw4_fronttext *t,const dw4_igb *g,const dw4_scene *scene)
{
    for(uint32_t id=0;id<g->table_n;id++)if(g->id_kind[id]==2){
        dw4_igb_record r={0};if(!record(g,id,&r))return -1;
        if(!strcmp(r.class_name,"beFontInfo") && !t->string){
            uint32_t strings=field(&r,7);dw4_igb_record_free(&r);if(unicode(t,g,strings))return -1;continue;
        }
        if(strcmp(r.class_name,"beFontInfoData") || !r.name || strncmp(r.name,"CHRSELFONT",10)){dw4_igb_record_free(&r);continue;}
        const char *kind=string_field(g,&r,10);uint32_t attr=field(&r,4),width=field(&r,7);
        if(!kind || (strcmp(kind,"MINIMUM") && strcmp(kind,"NORMAL")) || strlen(r.name)>=32){dw4_igb_record_free(&r);return -1;}
        struct row row={.align=(int32_t)field(&r,9),.face=!strcmp(kind,"MINIMUM"),.luminance=114};
        snprintf(row.group,sizeof row.group,"%s",r.name);memcpy(&row.width,&width,4);dw4_igb_record_free(&r);
        int found=0;
        for(unsigned j=0;j<scene->nnode;j++)if(scene->node[j].id==attr){
            if(!scene->node[j].name || strlen(scene->node[j].name)>=32 || j+1>=scene->nnode ||
               scene->node[j+1].parent!=j || dw4_scene_node_world(scene,j+1,row.matrix))return -1;
            snprintf(row.name,sizeof row.name,"%s",scene->node[j].name);found=1;break;
        }
        if(!found || !isfinite(row.width) || row.width<=0 || row.align<0 || row.align>2)return -1;
        struct row *rows=realloc(t->row,(t->nrow+1)*sizeof(*rows));if(!rows)return -1;
        t->row=rows;rows[t->nrow++]=row;
    }
    return t->nrow && t->nstring?0:-1;
}
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *result,char *error,size_t cap)
{
    dw4_fronttext *t=user;*result=(dw4_script_value){0};
    if(strcmp(method,"sd") || n!=5 || a[0].type!=DW4_SCRIPT_STRING || strcmp(a[0].string,"TEXTCTL") ||
       a[3].type!=DW4_SCRIPT_STRING || a[4].type!=DW4_SCRIPT_STRING)goto bad;
    char group[32],name[32],value[64];int consumed=0;
    if(sscanf(a[4].string,"%31[^/]/%31[^/]/%63[^\n]%n",group,name,value,&consumed)!=3 ||
       (size_t)consumed!=a[4].length)goto bad;
    int matched=0;
    for(size_t i=0;i<t->nrow;i++){
        struct row *r=t->row+i;if(strcmp(r->group,group) || strcmp(r->name,name))continue;matched++;
        if(!strcmp(a[3].string,"ALIGN")){
            if(!strcmp(value,"LEFT"))r->align=0;else if(!strcmp(value,"RIGHT"))r->align=1;
            else if(!strcmp(value,"CENTER"))r->align=2;else goto bad;
        }else if(!strcmp(a[3].string,"SWITCH")){
            if(!strcmp(value,"DISPON") || !strcmp(value,"SET"))r->visible=1;
            else if(!strcmp(value,"DISPOFF") || !strcmp(value,"CLR"))r->visible=0;else goto bad;
        }else if(!strcmp(a[3].string,"TEXTSET")){
            int index;consumed=0;
            if(sscanf(value,"I<%d>%n",&index,&consumed)!=1 || value[consumed] || index<0 || (size_t)index>=t->nstring)goto bad;
            struct string *s=t->string+index;dw4_font_vertex *v=NULL;size_t count;
            if(dw4_fontlayout_build(t->face+r->face,s->code,s->count,r->width,r->align,&v,&count))goto bad;
            free(r->vertices);r->vertices=v;r->count=count;
            free(r->dynamic);r->dynamic=NULL;r->ndynamic=0;
        }else goto bad;
    }
    if(matched)return 0;
 bad:snprintf(error,cap,"unsupported title text callback: %s",method);return -1;
}
dw4_fronttext *dw4_fronttext_open(const dw4_mount *mount)
{
    if(!mount)return NULL;
    dw4_fronttext *t=calloc(1,sizeof(*t));dw4_igb g={0};dw4_scene scene={0};uint32_t size;
    if(!t)return NULL;
    const uint8_t *blob=dw4_mount_data(mount,"stagIS10/separate/USA_pack.igb",&size);
    if(!blob || dw4_igb_open(&g,blob,size,0) || dw4_igb_refs_open(&g) ||
       dw4_scene_load(&scene,blob,size) || fonts(t,&g,&scene))goto bad;
    dw4_igb_close(&g);dw4_scene_close(&scene);
    if(dw4_fefont_load_face(t->face,mount,"NORMAL") || dw4_fefont_load_face(t->face+1,mount,"MINIMUM"))goto bad;
    for(unsigned i=0;i<2;i++)t->atlas[i]=(dw4_tex){.rgba=t->face[i].atlas,.w=t->face[i].aw,.h=t->face[i].ah};
    dw4_be_init(&t->state);t->engine=dw4_scriptengine_open(&t->state,binding,t);if(!t->engine)goto bad;
    blob=dw4_mount_entry(mount,0,806,&size,NULL);
    if(!blob || dw4_igb_open(&g,blob,size,0) || dw4_igb_refs_open(&g) ||
       dw4_script_load_pack_named(dw4_scriptengine_vm(t->engine),&g,"txt_mem.lua")!=1)goto bad;
    dw4_igb_close(&g);return t;
 bad:dw4_igb_close(&g);dw4_scene_close(&scene);dw4_fronttext_close(t);return NULL;
}
void dw4_fronttext_close(dw4_fronttext *t)
{
    if(!t)return;
    dw4_scriptengine_close(t->engine);
    for(size_t i=0;i<t->nrow;i++){free(t->row[i].vertices);free(t->row[i].dynamic);}
    for(size_t i=0;i<t->nstring;i++)free(t->string[i].code);
    for(unsigned i=0;i<2;i++)dw4_fefont_free(t->face+i);
    free(t->row);free(t->string);free(t->draw);free(t);
}
void dw4_fronttext_clear(dw4_fronttext *t)
{if(t)for(size_t i=0;i<t->nrow;i++)t->row[i].visible=0;}
int dw4_fronttext_event(dw4_fronttext *t,int32_t callno)
{
    if(!t || t->error[0])return -1;
    int rc=dw4_scriptengine_text_event(t->engine,1,"txt_mem.lua",callno);
    if(rc)snprintf(t->error,sizeof t->error,"%s",dw4_scriptengine_error(t->engine));
    return rc;
}
const char *dw4_fronttext_error(const dw4_fronttext *t){return t?t->error:"title text unavailable";}
int dw4_fronttext_set(dw4_fronttext *t,const char *group,const char *name,
    const uint32_t *codes,size_t count,int align,uint8_t luminance)
{
    if(!t || t->error[0] || !group || !name || (count && !codes) || align<0 || align>2 ||
       luminance>128 || count>SIZE_MAX/sizeof(uint32_t)-1)return -1;
    for(size_t i=0;i<t->nrow;i++){
        struct row *r=t->row+i;if(strcmp(group,r->group) || strcmp(name,r->name))continue;
        if(!count){r->visible=0;return 0;}
        if(!r->dynamic || r->ndynamic!=count || r->align!=align || memcmp(r->dynamic,codes,count*sizeof(*codes))){
            uint32_t *copy=calloc(count+1,sizeof(*copy));if(!copy)return -1;
            memcpy(copy,codes,count*sizeof(*copy));dw4_font_vertex *v;size_t n;
            if(dw4_fontlayout_build(t->face+r->face,copy,count,r->width,align,&v,&n)){free(copy);return -1;}
            free(r->vertices);free(r->dynamic);r->vertices=v;r->count=n;r->dynamic=copy;r->ndynamic=count;r->align=align;
        }
        r->luminance=luminance;r->visible=1;return 0;
    }
    return -1;
}
int dw4_fronttext_draw(dw4_fronttext *t,unsigned width,unsigned height,const dw4_ui_draw **out,size_t *count)
{
    if(!t || !out || !count || !width || !height || t->error[0])return -1;
    size_t needed=0;for(size_t i=0;i<t->nrow;i++)if(t->row[i].visible)needed+=t->row[i].count/3;
    if(needed>t->capacity){dw4_ui_draw *draw=realloc(t->draw,needed*sizeof(*draw));if(!draw)return -1;t->draw=draw;t->capacity=needed;}
    size_t used=0;
    for(size_t i=0;i<t->nrow;i++){
        const struct row *r=t->row+i;if(!r->visible)continue;const float *m=r->matrix;
        for(size_t j=0;j<r->count;j+=3){
            dw4_ui_draw *draw=t->draw+used++;memset(draw,0,sizeof(*draw));draw->tex=t->atlas+r->face;
            draw->blend=draw->stq=draw->gs_raster=1;draw->filter=1;
            for(unsigned k=0;k<3;k++){
                const dw4_font_vertex *v=r->vertices+j+k;
                float x=v->x*m[0]+v->y*m[4]+m[12],y=v->x*m[1]+v->y*m[5]+m[13];
                draw->v[k][0]=(320+100*x)*width/640.0f;draw->v[k][1]=(224-100*y)*height/448.0f;
                draw->v[k][2]=v->u;draw->v[k][3]=v->v;draw->v[k][4]=1;
                memset(draw->rgba[k],r->luminance,3);draw->rgba[k][3]=121;
            }
        }
    }
    *out=t->draw;*count=used;return 0;
}
