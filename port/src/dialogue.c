#include "dw4/dialogue.h"
#include "dw4/wndepth.h"
#include "dw4/textcodec.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
struct selector {
    dw4_dialogue *owner;
    const char *name;
    int32_t slot,default_count;
    uint64_t token,generation;
    dw4_selectctrl state;
    uint8_t *enabled;
};
struct font {
    dw4_dialogue_text text;
    const dw4_stageobject *info;
    uint32_t *codes;
    size_t face;
    uint32_t node,inner,outer;
    int32_t cbit,tbit;
    dw4_font_vertex *vertices;size_t nvertices;
};
struct face { const char *name;const dw4_igb *igb;uint32_t id;dw4_fefont font;dw4_tex atlas; };
struct dw4_dialogue {
    dw4_scriptservices *sd;
    struct selector **select;size_t nselect;
    struct font *font;size_t nfont;
    struct face *face;size_t nface;
    const dw4_stageobjects *objects;
    dw4_ui_draw *draw;size_t ndraw,drawcap;
    uint64_t font_token;
    dw4_subwindows *subwindows;
    uint32_t analog[4],held[4],pressed[4];
    int claimed;
    size_t text_split;int text_part; /* dw4_dialogue_text_split */
    int talk_late;                  /* dw4_dialogue_talk_late */
    char error[256];
};
static uint32_t field(const dw4_igb_record *r,unsigned ord)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ord)return r->values[i].raw;return UINT32_MAX;}
static const char *strfield(const dw4_igb_record *r,unsigned ord)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ord)return r->values[i].str;return NULL;}
static float number(uint32_t b){float f;memcpy(&f,&b,4);return f;}
static int record(const dw4_igb *g,uint32_t id,dw4_igb_record *r)
{return id<g->table_n && g->id_kind[id]==2 && dw4_igb_decode(g,g->id_off[id],r);}
static uint32_t item(const uint8_t *p,size_t i){uint32_t v;memcpy(&v,p+4*i,4);return v;}
static const uint8_t *list(const dw4_igb *g,uint32_t id,size_t *count)
{
    dw4_igb_record r={0};uint32_t bytes=0;*count=0;
    if(!record(g,id,&r))return NULL;
    const uint8_t *p=dw4_igb_block(g,field(&r,4),&bytes);uint32_t n=field(&r,2);
    dw4_igb_record_free(&r);if(!p || n>bytes/4)return NULL;*count=n;return p;
}
static dw4_script_value string(const char *s)
{return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int equal(dw4_script_value v,const char *s)
{return v.type==DW4_SCRIPT_STRING && v.string && v.length==strlen(s) && !memcmp(v.string,s,v.length);}
static int argument(dw4_script_value v,char *out,size_t cap)
{
    if(v.type!=DW4_SCRIPT_STRING || !v.string || v.length>=cap || memchr(v.string,0,v.length))return -1;
    memcpy(out,v.string,v.length);out[v.length]=0;return 0;
}
static int call(struct selector *s,const char *method,const char *key,const char *value)
{
    dw4_script_value a[]={string("MODELCTRL"),string(s->name),{DW4_SCRIPT_NUMBER,s->slot,NULL,0},string(key),{0}},r={0};
    if(value)a[4]=string(value);
    if(dw4_scriptservices_call(s->owner->sd,method,a,value?5:4,&r,s->owner->error,sizeof s->owner->error))return -1;
    if(!strcmp(method,"querySD")) {
        if(r.type!=DW4_SCRIPT_NUMBER){snprintf(s->owner->error,sizeof s->owner->error,"SELECTCTRL %s[%d]: MODELCTRL query unavailable",s->name,s->slot);return -1;}
        return r.number!=0;
    }
    return 0;
}
static int select_io(void *user,int query,const char *key,const char *value)
{
    struct selector *s=user;
    if(!strcmp(key,"SOUND")) {
        dw4_script_value a[]={string("SOUND"),{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},string("PLAY"),string("CURSOR_NG")},r;
        return dw4_scriptservices_call(s->owner->sd,"sd",a,5,&r,s->owner->error,sizeof s->owner->error);
    }
    if(!query && !strcmp(key,"GENERATE")) {
        char encoded[160];snprintf(encoded,sizeof encoded,"SQ_OPEN/V<%.9g,%.9g,%.9g>",s->state.position[0],s->state.position[1],s->state.position[2]);
        return call(s,"sd",key,encoded);
    }
    return call(s,query?"querySD":"sd",key,query?value:NULL);
}
/* Typed encoded values are decoded before mutation. Original choice helpers
 * use NOCANCEL/I<count[,selected]>/V<x,y,z>. Boolean flags are separate tokens. */
static int select_args(struct selector *s,const dw4_script_value *value,dw4_selectctrl *out,uint8_t **flags,int generate)
{
    *out=s->state;*flags=NULL;
    if(generate){*out=(dw4_selectctrl){.active=1,.count=s->default_count,.vertical=s->state.vertical,.cancel=1};}
    if(!value){if(generate)out->enabled=NULL;return 0;}
    char encoded[2048];if(argument(*value,encoded,sizeof encoded))return -1;
    unsigned nf=0,nv=0;uint8_t enable[256];char *p=encoded;
    while(*p) {
        char *end=strchr(p,'/');if(end)*end=0;
        int used=0,a,b;
        if(!strcmp(p,"NOCANCEL"))out->cancel=0;
        else if(sscanf(p,"I<%d,%d>%n",&a,&b,&used)==2 && p[used]==0){out->count=a;out->selected=b;}
        else if((used=0,sscanf(p,"I<%d>%n",&a,&used)==1) && p[used]==0){out->count=a;if(!generate)out->selected=0;}
        else if(p[0]=='V') {
            float vector[3];used=0;
            if(sscanf(p,"V<%f,%f,%f>%n",vector,vector+1,vector+2,&used)!=3 || p[used])return -1;
            for(unsigned i=0;i<3;i++)if(!isfinite(vector[i]))return -1;
            if(!nv++)memcpy(out->position,vector,sizeof vector);
        }
        else if(!strcmp(p,"TRUE") || !strcmp(p,"FALSE")){if(nf==256)return -1;enable[nf++]=!strcmp(p,"TRUE");}
        else return -1;
        if(!end)break;
        p=end+1;
    }
    if(out->count<1 || out->count>256 || out->selected<0 || out->selected>=out->count)return -1;
    for(unsigned i=0;i<3;i++)if(!isfinite(out->position[i]))return -1;
    if(nf && nf==(unsigned)out->count){*flags=malloc(nf);if(!*flags)return -1;memcpy(*flags,enable,nf);}
    out->enabled=*flags;return 0;
}
static int select_service(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct selector *s=user;*r=(dw4_script_value){0};if(n<4 || n>5)goto bad;
    dw4_selectctrl *state=&s->state;
    if(equal(a[3],"ISEND") || equal(a[3],"GETSELECT") || equal(a[3],"ISSELECTNOW") || equal(a[3],"ISFO2TOP")) {
        r->type=DW4_SCRIPT_NUMBER;
        r->number=equal(a[3],"ISEND")?!state->active:equal(a[3],"GETSELECT")?state->selected:
            equal(a[3],"ISSELECTNOW")?state->active && state->state!=2 && state->state!=3:
            !(state->state==1 && state->sub==0);
        return 0;
    }
    if(strcmp(method,"sd"))goto bad;
    if(equal(a[3],"GENERATE") || equal(a[3],"FO2TOP")) {
        int generate=equal(a[3],"GENERATE");
        if(!generate && (state->state!=1 || state->sub!=0)){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};return 0;}
        dw4_selectctrl next;uint8_t *flags;
        if(select_args(s,n==5?a+4:NULL,&next,&flags,generate))goto bad;
        if(!generate){next.selected=0;next.state=10;next.sub=next.delay=next.latch=0;}
        if(!generate && !flags && s->enabled) {
            flags=malloc((size_t)next.count);if(!flags)goto bad;
            memset(flags,1,(size_t)next.count);
            size_t count=state->count<next.count?(size_t)state->count:(size_t)next.count;
            memcpy(flags,s->enabled,count);
        }
        free(s->enabled);s->enabled=flags;s->state=next;s->state.enabled=flags;s->generation++;
        dw4_scriptservices_active(s->owner->sd,s->token,state->active);
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,1,NULL,0};return 0;
    }
    if(n==4 && equal(a[3],"REMOVE")){state->selected=-1;state->state=2;state->sub=state->delay=state->latch=0;s->generation++;return 0;}
bad:snprintf(error,cap,"unsupported SELECTCTRL %s[%d] command/arguments",s->name,s->slot);return -1;
}
static int unicode(const struct font *f,int32_t index,uint32_t **codes,size_t *count)
{
    const dw4_igb *g=(f->info)->igb;dw4_igb_record r={0};size_t n=0;
    if(!record(g,f->info->id,&r))return -1;
    uint32_t id=field(&r,7);dw4_igb_record_free(&r);
    const uint8_t *ids=list(g,id,&n);if(!ids || index<0 || (size_t)index>=n)return -1;
    if(!record(g,item(ids,index),&r))return -1;
    uint32_t bytes=0;const uint8_t *text=dw4_igb_block(g,field(&r,3),&bytes);dw4_igb_record_free(&r);
    if(!text || bytes%2)return -1;
    *codes=malloc((bytes/2+1)*sizeof(**codes));if(!*codes)return -1;*count=0;
    for(unsigned i=0;i<bytes;i+=2){uint32_t code=text[i]|(uint32_t)text[i+1]<<8;if(!code)break;(*codes)[(*count)++]=code;}
    return 0;
}
static int selected(const struct font *f,const char *group,const char *name)
{return (!strcmp(group,"ALL") || !strcmp(group,f->text.group)) && !strcmp(name,f->text.name);}
/* Prepare every matching row before publishing any text or geometry. */
static int set_text(dw4_dialogue *d,const char *group,const char *name,const uint32_t *codes,size_t count,int indexed,int32_t index)
{
    struct prepared {uint32_t *codes;size_t count;dw4_font_vertex *v;size_t nv;} *p;
    p=calloc(d->nfont?d->nfont:1,sizeof(*p));if(!p)return -1;
    int failed=0;
    for(size_t i=0;i<d->nfont;i++) {
        struct font *f=d->font+i;if(!selected(f,group,name))continue;
        if(indexed)failed=unicode(f,index,&p[i].codes,&p[i].count);
        else {
            if(count>SIZE_MAX/sizeof(uint32_t)-1){failed=1;break;}
            p[i].codes=calloc(count+1,sizeof(uint32_t));
            if(!p[i].codes){failed=1;break;}
            if(count)memcpy(p[i].codes,codes,count*sizeof(uint32_t));
            p[i].count=count;
        }
        if(failed || dw4_fontlayout_build(&d->face[f->face].font,p[i].codes,p[i].count,
            f->text.width,f->text.align,&p[i].v,&p[i].nv)){failed=1;break;}
    }
    if(!failed)for(size_t i=0;i<d->nfont;i++) {
        struct font *f=d->font+i;if(!selected(f,group,name))continue;
        free(f->codes);free(f->vertices);f->codes=p[i].codes;f->vertices=p[i].v;
        f->text.codes=f->codes;f->text.count=p[i].count;f->nvertices=p[i].nv;
        p[i].codes=NULL;p[i].v=NULL;
    }
    for(size_t i=0;i<d->nfont;i++){free(p[i].codes);free(p[i].v);}free(p);
    if(!failed)d->claimed=1;
    return failed?-1:0;
}
int dw4_dialogue_set_unicode(dw4_dialogue *d,const char *group,const char *name,const uint16_t *codes,size_t count)
{
    if(!d || !group || !name || (count && !codes) || count>SIZE_MAX/sizeof(uint32_t)-1)return -1;
    uint32_t *copy=calloc(count+1,sizeof(*copy));if(!copy)return -1;
    size_t n=0;while(n<count && codes[n]){copy[n]=codes[n];n++;}
    int rc=set_text(d,group,name,copy,n,0,0);free(copy);return rc;
}
int dw4_dialogue_replace_unknown(dw4_dialogue *d,uint16_t *codes,size_t count,uint16_t replacement)
{
    if(!d || !d->nface || (count && !codes))return -1;
    return dw4_fontlayout_replace_unknown(&d->face[0].font,codes,count,replacement);
}
static int switch_text(struct font *f,int visible)
{
    dw4_scene *scene=f->info->scene;
    if(dw4_scene_switch_set(scene,f->inner,f->tbit,visible))return -1;
    const dw4_scene_node *inner=scene->node+f->inner;
    const uint32_t *mask=inner->switch_values?inner->switch_values:dw4_scene_host(scene,inner->switch_mask);
    int any=0;
    for(uint32_t i=0;i<inner->switch_bits;i++)if(mask[i>>5]&(1u<<(i&31)))any=1;
    if(dw4_scene_switch_set(scene,f->outer,f->cbit,any))return -1;
    f->text.visible=visible;return 0;
}
static int font_service(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_dialogue *d=user;*r=(dw4_script_value){0};if(strcmp(method,"sd") || n<4 || n>5)goto bad;
    if(n==4 && equal(a[3],"INITIALIZE"))return 0;
    char encoded[8192];if(n!=5 || argument(a[4],encoded,sizeof encoded))goto bad;
    char *group=encoded,*name=strchr(group,'/');if(!name)goto bad;*name++=0;
    char *value=strchr(name,'/');if(value)*value++=0;
    int textset=equal(a[3],"TEXTSET"),sw=equal(a[3],"SWITCH"),align=equal(a[3],"ALIGN"),pos=equal(a[3],"SETPOSITION");
    int color=equal(a[3],"COLOR"),def=equal(a[3],"DEFAULTCOLOR"),cancel=equal(a[3],"CANCELCOLOR");
    if(!textset && !sw && !align && !pos && !color && !def && !cancel)goto bad;
    int used=0,index=0,mode=0;float vector[3]={0};
    if(textset) {
        if(!value)goto bad;
        if(sscanf(value,"I<%d>%n",&index,&used)==1 && value[used]==0) {
            if(set_text(d,group,name,NULL,0,1,index))goto bad;
        } else {
            size_t count=strlen(value);uint32_t *codes=malloc((count+1)*sizeof(*codes));if(!codes)goto bad;
            size_t converted;
            int rc=dw4_textcodec_decode(value,count,codes,count+1,&converted);
            if(!rc)rc=set_text(d,group,name,codes,converted,0,0);
            free(codes);if(rc)goto bad;
        }
        return 0;
    } else if(sw) {
        if(!value)goto bad;
        if(!strcmp(value,"SET") || !strcmp(value,"DISPON"))mode=1;
        else if(!strcmp(value,"CLR") || !strcmp(value,"DISPOFF"))mode=0;
        else if(sscanf(value,"I<%d>%n",&mode,&used)!=1 || value[used])goto bad;
    } else if(align) {
        if(!value)goto bad;
        mode=!strcmp(value,"LEFT")?0:!strcmp(value,"RIGHT")?1:!strcmp(value,"CENTER")?2:-1;if(mode<0)goto bad;
    } else if(pos || color) {
        if(!value || sscanf(value,"V<%f,%f,%f>%n",vector,vector+1,vector+2,&used)!=3 || value[used])goto bad;
        for(unsigned i=0;i<3;i++)if(!isfinite(vector[i]))goto bad;
    }
    for(size_t i=0;i<d->nfont;i++) {
        struct font *f=d->font+i;if(!selected(f,group,name))continue;
        if(sw){if(switch_text(f,mode!=0))goto bad;}
        else if(align)f->text.align=mode; /* Retail updates layout for the next TEXTSET. */
        else if(pos){dw4_scene_node *node=f->info->scene->node+f->node;
            node->m[12]=vector[0];node->m[13]=vector[1];node->m[14]=vector[2];
            f->text.x=vector[0];f->text.y=vector[1];}
        else for(unsigned j=0;j<3;j++)f->text.color[j]=color?vector[j]:def?.9f:.5f;
    }
    d->claimed=1;return 0;
bad:snprintf(error,cap,"unsupported TEXTCTL command/arguments or unavailable Unicode index");return -1;
}
static int fonts(dw4_dialogue *d,const dw4_stageobject *info)
{
    const dw4_igb *g=(info)->igb;dw4_igb_record r={0};size_t n=0;
    if(!record(g,info->id,&r))return -1;
    uint32_t id=field(&r,5);dw4_igb_record_free(&r);
    const uint8_t *ids=list(g,id,&n);if(!ids)return -1;
    struct font *p=realloc(d->font,(d->nfont+n)*sizeof(*p));if(!p)return -1;d->font=p;
    for(size_t i=0;i<n;i++) {
        struct font *f=p+d->nfont++;memset(f,0,sizeof(*f));f->info=info;
        if(!record(g,item(ids,i),&r) || strcmp(r.class_name,"beFontInfoData")){dw4_igb_record_free(&r);return -1;}
        f->cbit=(int32_t)field(&r,5);f->tbit=(int32_t)field(&r,6);
        f->text.group=r.name;f->text.kind=strfield(&r,10);f->text.width=number(field(&r,7));f->text.height=number(field(&r,8));f->text.align=(int32_t)field(&r,9);
        id=field(&r,4);dw4_igb_record_free(&r);
        if(!record(g,id,&r))return -1;
        f->text.name=r.name;uint32_t attr=id;id=field(&r,7);dw4_igb_record_free(&r);
        size_t children=0;const uint8_t *child=list(g,id,&children);
        if(!child || !children || !record(g,item(child,0),&r))return -1;
        uint32_t transform=item(child,0);f->node=f->inner=f->outer=UINT32_MAX;
        dw4_scene *scene=info->scene;
        for(unsigned j=0;j<scene->nnode;j++)if(scene->node[j].id==attr){
            f->inner=scene->node[j].parent;
            if(f->inner>=scene->nnode)break;
            uint32_t group=scene->node[f->inner].parent;
            if(group<scene->nnode)f->outer=scene->node[group].parent;
            for(unsigned k=j+1;k<scene->nnode && scene->node[k].depth>scene->node[j].depth;k++)
                if(scene->node[k].id==transform){f->node=k;break;}
            break;
        }
        if(f->node==UINT32_MAX || f->outer>=scene->nnode || f->inner>=scene->nnode ||
           f->cbit<0 || (uint32_t)f->cbit>=scene->node[f->outer].switch_bits ||
           f->tbit<0 || (uint32_t)f->tbit>=scene->node[f->inner].switch_bits){dw4_igb_record_free(&r);return -1;}
        for(unsigned j=0;j<r.nvalues;j++)if(r.values[j].ordinal==8 && r.values[j].vsize==64) {
            float matrix[16];memcpy(matrix,g->data+r.values[j].voff,sizeof matrix);f->text.x=matrix[12];f->text.y=matrix[13];
        }
        dw4_igb_record_free(&r);
        for(unsigned j=0;j<3;j++)f->text.color[j]=.9f;
        if(!f->text.name || !f->text.group || !f->text.kind || !isfinite(f->text.width) || !isfinite(f->text.height))return -1;
        f->face=0;for(size_t j=0;j<d->nface;j++)if(!strcmp(f->text.kind,d->face[j].name)){f->face=j;break;}
    }
    return 0;
}
void dw4_dialogue_forget_gpu(const dw4_dialogue *d,dw4_gl_layer *gpu)
{
    if(d && gpu)for(size_t i=0;i<d->nface;i++)dw4_gl_layer_texture_forget(gpu,&d->face[i].atlas);
}
void dw4_dialogue_close(dw4_dialogue *d)
{
    if(!d)return;
    for(size_t i=0;i<d->nselect;i++){dw4_scriptservices_unregister(d->sd,d->select[i]->token);free(d->select[i]->enabled);free(d->select[i]);}
    dw4_scriptservices_unregister(d->sd,d->font_token);
    dw4_subwindows_close(d->subwindows);
    for(size_t i=0;i<d->nfont;i++){free(d->font[i].codes);free(d->font[i].vertices);}
    for(size_t i=0;i<d->nface;i++)dw4_fefont_free(&d->face[i].font);
    free(d->draw);free(d->face);free(d->font);free(d->select);free(d);
}
dw4_dialogue *dw4_dialogue_open(dw4_scriptservices *sd,uint64_t scope,const dw4_stageobjects *objects)
{
    if(!sd || !objects)return NULL;
    dw4_dialogue *d=calloc(1,sizeof(*d));if(!d)return NULL;d->sd=sd;d->objects=objects;
    /* Retail named-object collection supplies face order and fallback index zero. */
    for(size_t i=0;i<dw4_stageobjects_count(objects);i++) {
        const dw4_stageobject *info=dw4_stageobjects_at(objects,i);
        if(strcmp(dw4_stageobject_class(info),"igNamedObjectInfo"))continue;
        const dw4_igb *g=(info)->igb;dw4_igb_record r={0};size_t n;
        if(!record(g,info->id,&r))goto bad;
        uint32_t id=field(&r,5);dw4_igb_record_free(&r);const uint8_t *ids=list(g,id,&n);if(!ids)goto bad;
        for(size_t j=0;j<n;j++) {
            id=item(ids,j);if(!record(g,id,&r))goto bad;
            if(strcmp(r.class_name,"beFontImage")){dw4_igb_record_free(&r);continue;}
            const char *name=r.name;dw4_igb_record_free(&r);int duplicate=0;
            for(size_t k=0;k<d->nface;k++)if(d->face[k].igb==g && d->face[k].id==id)duplicate=1;
            if(duplicate)continue;
            struct face *rows=realloc(d->face,(d->nface+1)*sizeof(*rows));if(!rows)goto bad;d->face=rows;
            struct face *face=rows+d->nface++;memset(face,0,sizeof(*face));face->name=name;face->igb=g;face->id=id;
            if(!name || dw4_fefont_decode(&face->font,g,id))goto bad;
            face->atlas=(dw4_tex){.rgba=face->font.atlas,.w=face->font.aw,.h=face->font.ah};
        }
    }
    for(size_t i=0;i<dw4_stageobjects_count(objects);i++) {
        const dw4_stageobject *info=dw4_stageobjects_at(objects,i);int duplicate=0;
        for(size_t j=0;j<i;j++)if(dw4_stageobject_same(dw4_stageobjects_at(objects,j),info))duplicate=1;
        if(duplicate)continue;
        const char *type=dw4_stageobject_class(info);
        if(!strcmp(type,"beFontInfo")){if(!d->nface || fonts(d,info))goto bad;continue;}
        if(strcmp(type,"beSelectCtrlInfo"))continue;
        const dw4_igb *g=(info)->igb;dw4_igb_record r={0};size_t n=0;
        if(!record(g,info->id,&r))goto bad;
        uint32_t id=field(&r,6);dw4_igb_record_free(&r);
        const uint8_t *ids=list(g,id,&n);if(!ids)goto bad;
        for(size_t j=0;j<n;j++) {
            struct selector *s=calloc(1,sizeof(*s));if(!s)goto bad;s->owner=d;s->name=dw4_stageobject_name(info);s->slot=(int32_t)j;
            struct selector **rows=realloc(d->select,(d->nselect+1)*sizeof(*rows));if(!rows){free(s);goto bad;}d->select=rows;rows[d->nselect++]=s;
            if(!s->name || !record(g,item(ids,j),&r))goto bad;
            id=field(&r,10);dw4_igb_record_free(&r);
            size_t np=0;const uint8_t *props=list(g,id,&np);if(!props)goto bad;
            int found=0;
            for(size_t k=0;k<np;k++) {
                if(!record(g,item(props,k),&r))goto bad;
                if(r.name && !strcmp(r.name,"ONE") && !strcmp(r.class_name,"beSelectCtrlInfoRamData")) {
                    s->state.vertical=field(&r,4)!=0;s->default_count=(int32_t)field(&r,5);s->state.selected=(int32_t)field(&r,6);found=1;
                }
                dw4_igb_record_free(&r);
            }
            if(!found || s->default_count<1 || s->default_count>256)goto bad;
            s->state.count=s->default_count;
            s->token=dw4_scriptservices_register(sd,scope,"SELECTCTRL",s->name,s->slot,0,select_service,s);if(!s->token)goto bad;
        }
    }
    if(d->nfont){d->font_token=dw4_scriptservices_register(sd,scope,"TEXTCTL",NULL,-1,1,font_service,d);if(!d->font_token)goto bad;}
    d->subwindows=dw4_subwindows_open(sd,scope,objects);if(!d->subwindows)goto bad;
    return d;
bad:dw4_dialogue_close(d);return NULL;
}
void dw4_dialogue_input(dw4_dialogue *d,unsigned p,uint32_t analog,uint32_t held,uint32_t pressed)
{if(d && p<4){d->analog[p]=analog;d->held[p]=held;d->pressed[p]=pressed;}}
int dw4_dialogue_tick(dw4_dialogue *d)
{
    if(!d)return 0;
    for(size_t i=0;i<d->nselect;i++) {
        struct selector *s=d->select[i];unsigned p=(unsigned)s->slot;
        uint64_t generation=s->generation;dw4_selectctrl next=s->state;
        uint8_t flags[256];
        if(next.enabled){memcpy(flags,next.enabled,(size_t)next.count);next.enabled=flags;}
        if(dw4_selectctrl_tick(&next,p<4?d->analog[p]:0,p<4?d->held[p]:0,p<4?d->pressed[p]:0,select_io,s))return -1;
        if(generation==s->generation){s->state=next;s->state.enabled=s->enabled;}
        if(!s->state.active){free(s->enabled);s->enabled=NULL;s->state.enabled=NULL;}
        dw4_scriptservices_active(d->sd,s->token,s->state.active);
    }
    if(dw4_subwindows_tick(d->subwindows)){snprintf(d->error,sizeof d->error,"SUBWND: %.240s",dw4_subwindows_error(d->subwindows));return -1;}
    memset(d->pressed,0,sizeof d->pressed);return 0;
}
const char *dw4_dialogue_error(const dw4_dialogue *d){return d?d->error:"no dialogue owner";}
int dw4_dialogue_claimed(const dw4_dialogue *d){return d && d->claimed;}
int dw4_dialogue_talk_open(const dw4_dialogue *d)
{
    for(size_t i=0;d && i<d->nfont;i++){
        const dw4_dialogue_text *t=&d->font[i].text;
        if(t->visible && t->count && !strncmp(t->group,"TALKFONT",8))return 1;
    }
    return 0;
}
size_t dw4_dialogue_text_count(const dw4_dialogue *d){return d?d->nfont:0;}
const dw4_dialogue_text *dw4_dialogue_text_at(const dw4_dialogue *d,size_t i){return d && i<d->nfont?&d->font[i].text:NULL;}
int dw4_dialogue_subwindow(dw4_dialogue *d,dw4_script_binding handler,void *user)
{return d?dw4_subwindows_override(d->subwindows,handler,user):-1;}
dw4_subwindows *dw4_dialogue_subwindows(dw4_dialogue *d){return d?d->subwindows:NULL;}

/* The layer index a font graph is attached to, or SIZE_MAX when it is not attached. */
static size_t font_layer(const dw4_dialogue *d,const struct font *f)
{
    for(size_t i=0;i<dw4_stageobjects_attachments(d->objects);i++) {
        const dw4_layer_attachment *a=dw4_stageobjects_attachment(d->objects,i);
        if(a->info->scene!=f->info->scene)continue;
        uint32_t node=f->node;
        while(node<f->info->scene->nnode){
            if(f->info->scene->node[node].id==a->root_id)return a->layer;
            node=f->info->scene->node[node].parent;
        }
    }
    return SIZE_MAX;
}
static int font_visible(const dw4_dialogue *d,const struct font *f)
{
    if(!f->text.visible || !dw4_scene_node_visible(f->info->scene,f->node,0))return 0;
    size_t layer=font_layer(d,f);
    return layer!=SIZE_MAX && dw4_stageobjects_layer_visible(d->objects,layer); /* An unattached font graph is not published for rendering. */
}
void dw4_dialogue_text_split(dw4_dialogue *d,const char *layer,int part)
{
    if(!d)return;
    d->text_part=0;
    if(!layer || !part)return;
    for(size_t i=0;i<dw4_stageobjects_layers(d->objects);i++)
        if(!strcmp(dw4_stageobjects_layer(d->objects,i),layer)){d->text_split=i;d->text_part=part;return;}
}
/* The Digimon info card (DMINFOFONT, window i_dminfown in WN03) is a FONT-layer text like the stage-change name: late. A field stage's message windows (the practice stage's tutorial window, model i_*wn in WN03) sit below the FONT layer, which follows WN04 in the
 * stage's layer list: their TALKFONT text is drawn after the models of the layers from the split on, not between WN01 and WN02 (it was dimmed by
 * the window drawn over it). The lobby UI keeps its own window/text order. */
void dw4_dialogue_talk_late(dw4_dialogue *d,int on){if(d)d->talk_late=!!on;}
/* The stage-change window (i_zzstchgwb/wn) lives in WN03 and its area name (STCHGFONT00) belongs on top of it, as the original FONT layer
 * follows WN04; that text draws after the models of the layers from the split on. All other text keeps its place below the split, where
 * the full-screen fade models of WN02 hide a point-message label left open over a stage change. */
static int text_in_part(const dw4_dialogue *d,const struct font *f)
{
    if(!d->text_part)return 1;
    size_t layer=font_layer(d,f);
    int late=layer!=SIZE_MAX && layer>=d->text_split && (!strncmp(f->text.group,"STCHGFONT",9) || !strncmp(f->text.group,"DMINFOFONT",10) || (d->talk_late && !strncmp(f->text.group,"TALKFONT",8)));
    return d->text_part==2?late:!late;
}
static int window_depth(const dw4_scene *s,uint32_t node,float x,float y,float z,float *depth)
{
    const float *view=NULL,*projection=NULL;
    for(uint32_t n=node;n<s->nnode;n=s->node[n].parent){
        if(!view && s->node[n].has_view)view=s->node[n].view;
        if(!projection && s->node[n].has_projection)projection=s->node[n].projection;
    }
    /* Font graphs borrow the authored WN01/N01 traversal camera; unlike model
     * XY, their local XY is in font units, while Z remains in scene units. */
    for(uint32_t n=0;n<s->nnode && (!view || !projection);n++){
        const dw4_scene_node *p=s->node+n;if(!p->name)continue;
        if(!view && p->has_view && !strcmp(p->name,"WN01"))view=p->view;
        if(!projection && p->has_projection && !strcmp(p->name,"N01"))projection=p->projection;
    }
    if(!view || !projection)return 0;
    float world[4]={100*x,100*y,z,1},camera[4],clip[4];
    for(unsigned k=0;k<4;k++)camera[k]=world[0]*view[k]+world[1]*view[4+k]+world[2]*view[8+k]+view[12+k];
    for(unsigned k=0;k<4;k++)clip[k]=camera[0]*projection[k]+camera[1]*projection[4+k]+camera[2]*projection[8+k]+camera[3]*projection[12+k];
    if(clip[3]<=0)return 0;
    *depth=dw4_wn_depth(clip[2],clip[3],0,1);return 1;
}
int dw4_dialogue_draw(dw4_dialogue *d,unsigned width,unsigned height,const dw4_ui_draw **draws,size_t *count)
{
    if(!d || !draws || !count || !width || !height)return -1;
    d->ndraw=0;*draws=NULL;*count=0;
    int talk=dw4_dialogue_talk_open(d);
    for(size_t i=0;i<d->nfont;i++) {
        const struct font *f=d->font+i;if(!f->nvertices || !font_visible(d,f) || !text_in_part(d,f))continue;
        if(talk && !strncmp(f->text.group,"POINTFONT",9))continue; /* the point-message label closes while a message window is open */
        float m[16];if(dw4_scene_node_world(f->info->scene,f->node,m))return -1;
        size_t n=f->nvertices/3;
        if(n>SIZE_MAX/sizeof(dw4_ui_draw)-d->ndraw)return -1;
        if(d->ndraw+n>d->drawcap){
            size_t cap=d->ndraw+n;dw4_ui_draw *p=realloc(d->draw,cap*sizeof(*p));if(!p)return -1;
            d->draw=p;d->drawcap=cap;
        }
        for(size_t j=0;j<n;j++) {
            dw4_ui_draw *draw=d->draw+d->ndraw++;memset(draw,0,sizeof(*draw));
            draw->tex=&d->face[f->face].atlas;draw->blend=draw->stq=1;draw->gs_raster=1;
            draw->depth_mode=2;draw->filter=1; /* ALWAYS, ZMSK=1, nearest font atlas. */
            for(unsigned k=0;k<3;k++) {
                const dw4_font_vertex *v=f->vertices+3*j+k;
                float x=v->x*m[0]+v->y*m[4]+v->z*m[8]+m[12];
                float y=v->x*m[1]+v->y*m[5]+v->z*m[9]+m[13];
                draw->v[k][0]=(320+100*x)*width/640.0f;draw->v[k][1]=(224-100*y)*height/448.0f;
                /* A quarter-texel inset: the glyph rect's left edge lands exactly on a texel boundary, where rounding sampled one column of the
                 * neighbouring atlas glyph (a thin tick left of narrow letters). */
                draw->v[k][2]=v->u+.25f/(float)d->face[f->face].atlas.w;draw->v[k][3]=v->v;draw->v[k][4]=1;
                float z=v->x*m[2]+v->y*m[6]+v->z*m[10]+m[14];
                window_depth(f->info->scene,f->node,x,y,z,draw->z+k);
                for(unsigned c=0;c<3;c++)draw->rgba[k][c]=(uint8_t)fminf(128,fmaxf(0,f->text.color[c]*127));
                draw->rgba[k][3]=121;
            }
        }
    }
    *draws=d->draw;*count=d->ndraw;return 0;
}
