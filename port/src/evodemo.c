#include "dw4/evodemo.h"
#include "dw4/filelist.h"
#include "dw4/database.h"
#include "dw4/stageobjects.h"
#include "dw4/modelview.h"
#include "dw4/playertransactions.h"
#include "dw4/cameratime.h"
#include "dw4/gl_layer.h"
#include "dw4/igb.h"
#include "dw4/dialogue.h"
#include "dw4/frontaudio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct dw4_evodemo {
    dw4_mount *mount;dw4_be_state state;dw4_playerrecords *players;
    dw4_scriptengine *scripts;dw4_scriptservices *sd;dw4_filelist *files;
    dw4_stageobjects *objects;dw4_controllers *models;dw4_databases *databases;dw4_modelview *view;dw4_dialogue *dialogue;
    dw4_stagetravel *travel;
    uint64_t origin_ns,now_ns,ticks;char error[512];
    /* SETDEMOCAMERA "entry": beCameraCtrlInfo/beCameraDemoData and the igCamera at the end of its path. */
    const dw4_stageobject *camera_pack;uint32_t camera_graph,camera_node;float near_plane,far_plane;
    dw4_camera_time camera_time;int camera_demo;
    uint8_t background[4];
    char sounds[256];dw4_frontaudio *audio;
    dw4_gl_layer *gpu;
};
static void fail(dw4_evodemo *d,const char *what){if(!d->error[0])snprintf(d->error,sizeof d->error,"%s",what);}
static int string_is(const dw4_script_value *v,const char *s){return v->type==DW4_SCRIPT_STRING && v->string && !strcmp(v->string,s);}
static uint32_t field(const dw4_igb_record *r,unsigned ord)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ord)return r->values[i].raw;return UINT32_MAX;}
static uint64_t field64(const dw4_igb_record *r,unsigned ord)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ord)return r->values[i].raw64;return 0;}
static int record(const dw4_igb *g,uint32_t id,dw4_igb_record *r)
{return id<g->table_n && g->id_kind[id]==2 && dw4_igb_decode(g,g->id_off[id],r);}

/* ---- services ---- */
static int gameram(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{return dw4_playerrecords_service(((dw4_evodemo *)user)->players,method,a,n,r,error,cap);}
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_evodemo *d=user;int rc=dw4_playerrecords_call(d->players,method,a,n,r,error,cap);
    if(rc>0)rc=dw4_playertransactions_folder_call(d->players,method,a,n,r,error,cap);
    if(rc<=0)return rc;
    if(!strcmp(method,"PLAYERgetPos") && !n){*r=(dw4_script_value){DW4_SCRIPT_NUMBER,d->travel->generate_pos,NULL,0};return 0;}
    dw4_scriptservices_scope(d->sd,dw4_scriptengine_scope(d->scripts));
    return dw4_scriptservices_call(d->sd,method,a,n,r,error,cap);
}
/* SOUND: the demo's DM_EVOLV/AM_EVOLV through the stage's own sound bank (dw4_frontaudio_stage_service); requests are also
 * recorded for diagnostics. */
static int sound(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_evodemo *d=user;*r=(dw4_script_value){0};
    if(n<4 || a[3].type!=DW4_SCRIPT_STRING || !a[3].string){snprintf(error,cap,"unsupported demo SOUND %s",method);return -1;}
    char row[64];snprintf(row,sizeof row,"%s%s %s",d->sounds[0]?",":"",method,a[3].string);
    if(n==5 && a[4].type==DW4_SCRIPT_STRING && a[4].string)snprintf(row+strlen(row),sizeof row-strlen(row)," %s",a[4].string);
    if(strlen(d->sounds)+strlen(row)<sizeof d->sounds)strcat(d->sounds,row);
    return dw4_frontaudio_stage_service(d->audio,method,a,n,r,error,cap);
}
static int text_initialize(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    (void)user;*r=(dw4_script_value){0};
    if(!strcmp(method,"sd") && n==4 && string_is(a+3,"INITIALIZE"))return 0;
    snprintf(error,cap,"the digivolution demo has no text owner for TEXTCTL %s",method);return -1;
}
/* CAMERA: SETDEMOCAMERA "entry" starts the authored demo path's clock; ISDEMOCAMERA reports it running. */
static int camera(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_evodemo *d=user;*r=(dw4_script_value){0};
    if(!d->camera_time.loaded || n<4 || n>5)goto bad;
    if(!strcmp(method,"querySD") && n==4 && string_is(a+3,"ISDEMOCAMERA")){
        *r=(dw4_script_value){DW4_SCRIPT_NUMBER,d->camera_demo && !d->camera_time.finished,NULL,0};return 0;
    }
    if(!strcmp(method,"sd") && n==5 && string_is(a+3,"SETDEMOCAMERA") && string_is(a+4,"entry")){
        uint64_t end=d->camera_time.end;d->camera_time=(dw4_camera_time){.end=end,.loaded=1};d->camera_demo=1;return 0;
    }
    if(!strcmp(method,"sd") && n==4 && (string_is(a+3,"ONFREEZE") || string_is(a+3,"OFFREEZE"))){
        d->camera_time.frozen=string_is(a+3,"ONFREEZE");return 0;
    }
bad:snprintf(error,cap,"unsupported demo CAMERA %s (entry only)",method);return -1;
}

/* ---- the authored demo camera and background ---- */
static int load_camera(dw4_evodemo *d)
{
    for(size_t i=0;i<dw4_stageobjects_count(d->objects);i++){
        const dw4_stageobject *o=dw4_stageobjects_at(d->objects,i);
        if(strcmp(dw4_stageobject_class(o),"beCameraCtrlInfo") || !dw4_stageobject_name(o) || strcmp(dw4_stageobject_name(o),"entry"))continue;
        dw4_igb_record r={0},demo={0};const dw4_igb *g=(o)->igb;
        if(!record(g,o->id,&r))return -1;
        int ok=record(g,field(&r,7),&demo) && !strcmp(demo.class_name,"beCameraDemoData");
        if(ok){d->camera_time.end=field64(&demo,3);d->camera_time.loaded=1;}
        dw4_igb_record_free(&demo);dw4_igb_record_free(&r);if(!ok)return -1;
        d->camera_pack=o;break;
    }
    if(!d->camera_pack || !d->camera_pack->scene)return -1;
    const dw4_scene *s=d->camera_pack->scene;d->camera_graph=UINT32_MAX;d->camera_node=UINT32_MAX;
    for(uint32_t j=0;j<s->ngraph;j++)if(s->graph[j].name && !strcmp(s->graph[j].name,"entry"))d->camera_graph=j;
    if(d->camera_graph==UINT32_MAX)return -1;
    /* The demo path ends at the deepest igCamera of the "entry" graph (animCamera01_60 -> ... -> cameraanimShape01). */
    for(uint32_t j=0;j<s->nnode;j++)if(s->node[j].scene==d->camera_graph && s->node[j].class_name && !strcmp(s->node[j].class_name,"igCamera") &&
        (d->camera_node==UINT32_MAX || s->node[j].depth>s->node[d->camera_node].depth))d->camera_node=j;
    if(d->camera_node==UINT32_MAX)return -1;
    dw4_igb_record c={0};const dw4_igb *g=(d->camera_pack)->igb;
    if(!record(g,s->node[d->camera_node].id,&c) || strcmp(c.class_name,"igCamera")){dw4_igb_record_free(&c);return -1;}
    uint32_t near=field(&c,9),far=field(&c,10);dw4_igb_record_free(&c);
    memcpy(&d->near_plane,&near,4);memcpy(&d->far_plane,&far,4);
    if(!isfinite(d->near_plane) || !isfinite(d->far_plane) || d->near_plane<=0 || d->far_plane<=d->near_plane)return -1;
    return 0;
}

/* beBkColorInfo._rgba: the frame clear colour (normalized floats). */
static int load_background(dw4_evodemo *d)
{
    for(size_t i=0;i<dw4_stageobjects_count(d->objects);i++){
        const dw4_stageobject *o=dw4_stageobjects_at(d->objects,i);
        if(strcmp(dw4_stageobject_class(o),"beBkColorInfo"))continue;
        float rgba[4];if(dw4_stageobject_rgba(o,rgba))return -1;
        for(unsigned k=0;k<4;k++){if(!isfinite(rgba[k]) || rgba[k]<0 || rgba[k]>1)return -1;d->background[k]=(uint8_t)lrintf(rgba[k]*255);}
        d->background[3]=255;return 0;
    }
    return -1;
}
/* The demo camera at the current demo clock: the "entry" graph's sequences driven to camera_time, then the igCamera's world
 * inverted (row vectors, as the lobby's stage camera). Before SETDEMOCAMERA the path's start pose is used. */
static int demo_camera(dw4_evodemo *d,unsigned width,unsigned height,float view[16],float projection[16])
{
    const dw4_scene *source=d->camera_pack->scene;dw4_scene s=*source;
    dw4_scene_node *nodes=malloc((size_t)s.nnode*sizeof *nodes);if(!nodes)return -1;
    memcpy(nodes,source->node,(size_t)s.nnode*sizeof *nodes);s.node=nodes;
    for(uint32_t j=0;j<s.nnode;j++)if(s.node[j].scene==d->camera_graph && s.node[j].has_seq)
        dw4_scene_node_drive(&s,j,0,(long long)d->camera_time.time);
    dw4_scene_set_engine_time(&s,0);
    float world[16];int rc=dw4_scene_node_camera(&s,d->camera_node,world,view);free(nodes);if(rc)return -1;
    for(unsigned i=0;i<3;i++)view[12+i]=-(world[12]*view[i]+world[13]*view[4+i]+world[14]*view[8+i]);
    /* The engine projection (DW4_SCENE_CAMERA_FOV, horizontal 0.7*w/h), as the lobby's: view space +Z forward, Y up. */
    float t=tanf(DW4_SCENE_CAMERA_FOV*.5f),n=d->near_plane,f=d->far_plane;
    memset(projection,0,16*sizeof *projection);
    projection[0]=dw4_scene_camera_aspect((int)width,(int)height)*height/width/t;projection[5]=1/t;
    projection[10]=(f+n)/(f-n);projection[11]=1;projection[14]=-2*f*n/(f-n);
    return 0;
}
dw4_evodemo *dw4_evodemo_open(dw4_mount *mount,const dw4_evodemo_source *source,char *error,size_t cap)
{
    dw4_evodemo *d=calloc(1,sizeof *d);if(!d)return NULL;
    const char *step="session snapshot";d->mount=mount;
    if(!mount || !source || !source->state || !source->travel || !(d->players=dw4_playerrecords_snapshot(source->records)))goto fail;
    d->state=*source->state;d->travel=source->travel;d->origin_ns=d->now_ns=source->world_ns;
    step="demo audio";
    static const char *const cues[]={"DM_EVOLV","AM_EVOLV"};
    d->audio=dw4_frontaudio_prepare_stage(mount,"stagml14.igb",cues,2);if(!d->audio)goto fail;
    step="script engine";
    d->sd=dw4_scriptservices_open();if(!d->sd)goto fail;
    d->scripts=dw4_scriptengine_open(&d->state,binding,d);d->files=dw4_filelist_open(mount);if(!d->scripts || !d->files)goto fail;
    dw4_scriptengine_filelist(d->scripts,d->files);dw4_scriptengine_record_flags(d->scripts,1);
    if(!dw4_scriptservices_register(d->sd,0,"GAMERAM",NULL,-1,1,gameram,d) ||
       !dw4_scriptservices_register(d->sd,0,"SOUND",NULL,-1,1,sound,d) ||
       !dw4_scriptservices_register(d->sd,0,"STAGECTL",NULL,-1,1,dw4_stagetravel_service,d->travel) ||
       !dw4_scriptservices_register(d->sd,0,"PLAYERPOINT",NULL,-1,1,dw4_stagetravel_service,d->travel))goto fail;
    step="demo stage pack and native objects";
    d->objects=dw4_stageobjects_open();if(!d->objects)goto fail;
    dw4_stageobjects_actor_skins(d->objects,1);   /* the s_<species> packs are skinned igActors */
    if(dw4_filelist_begin(d->files,d->scripts,"stagML14",1) || dw4_filelist_shared(d->files) ||
       dw4_filelist_route_assets(d->files,dw4_stageobjects_route,d->objects) ||
       dw4_filelist_bind_layers(d->files,dw4_stageobjects_bind_layers,d->objects) ||
       dw4_stageobjects_publish(d->objects,d->sd,1))goto fail;
    step="database/model owners";
    d->databases=dw4_databases_open(d->objects,d->error,sizeof d->error);
    if(!d->databases || dw4_databases_publish(d->databases,d->sd,1))goto fail;
    d->models=dw4_controllers_open(d->sd,1,d->objects,NULL,0,&d->state.random,&d->state.action_rhythm,d->scripts);
    d->dialogue=dw4_dialogue_open(d->sd,1,d->objects);   /* TEXTCTL: the shared start chunk initializes text */
    if(!d->models || !d->dialogue)goto fail;
    /* The engine's stage start sends TEXTCTL INITIALIZE to every stage; this pack has no font owner to receive it. */
    if(!dw4_scriptservices_category(d->sd,"TEXTCTL") && !dw4_scriptservices_register(d->sd,1,"TEXTCTL",NULL,-1,1,text_initialize,d))goto fail;
    dw4_controllers_sample(d->models,(int64_t)d->origin_ns);
    if(dw4_scriptservices_tick(d->sd,d->origin_ns))goto fail;
    step="demo camera";if(load_camera(d)){fail(d,"the entry demo camera path is not readable");goto fail;}
    step="demo models";d->view=dw4_modelview_open_world(d->objects,d->models,d->error,sizeof d->error);if(!d->view)goto fail;
    step="background colour";if(load_background(d)){fail(d,"beBkColorInfo is not readable");goto fail;}
    step="scene services";
    if(!dw4_scriptservices_register(d->sd,1,"CAMERA",NULL,-1,1,camera,d) ||
       !dw4_scriptservices_register(d->sd,1,"SWITCHCTRL",NULL,-1,1,dw4_stageobjects_switch_service,d->objects))goto fail;
    step="original start/first";
    if(dw4_filelist_start(d->files) || dw4_filelist_first(d->files))goto fail;
    return d;
fail:
    snprintf(error,cap,"stagML14 %s: %.120s; %.180s; %.120s",step,d->error,d->files?dw4_filelist_error(d->files):"",
        d->scripts?dw4_scriptengine_error(d->scripts):"");
    dw4_evodemo_close(d);return NULL;
}
void dw4_evodemo_close(dw4_evodemo *d)
{
    if(!d)return;
    if(d->scripts && d->sd)dw4_scriptengine_remove_all(d->scripts,d->sd);
    dw4_gl_layer_close(d->gpu);dw4_modelview_close(d->view);dw4_dialogue_close(d->dialogue);dw4_controllers_close(d->models);dw4_databases_close(d->databases);
    dw4_stageobjects_close(d->objects);dw4_filelist_close(d->files);dw4_scriptengine_close(d->scripts);dw4_scriptservices_close(d->sd);
    dw4_playerrecords_close(d->players);dw4_frontaudio_close(d->audio);free(d);
}
int dw4_evodemo_tick(dw4_evodemo *d,uint64_t ns)
{
    if(!d || d->error[0])return -1;
    if(ns<d->origin_ns || ns>INT64_MAX || (d->ticks && ns<=d->now_ns)){fail(d,"demo tick requires the next admitted session clock sample");return -1;}
    d->now_ns=ns;dw4_controllers_sample(d->models,(int64_t)ns);
    if(d->camera_demo)dw4_camera_time_tick(&d->camera_time,ns);
    if(dw4_scriptservices_tick(d->sd,ns) || dw4_scriptengine_tick(d->scripts) || dw4_controllers_tick(d->models,(int64_t)ns) || dw4_dialogue_tick(d->dialogue)){
        snprintf(d->error,sizeof d->error,"%.160s; %.160s; %.160s",dw4_scriptengine_error(d->scripts),dw4_scriptservices_error(d->sd),
            dw4_controllers_error(d->models));return -1;
    }
    d->ticks++;return 0;
}
const char *dw4_evodemo_enable_gpu(dw4_evodemo *d,int w,int h)
{
    if(!d)return NULL;
    dw4_gl_layer_close(d->gpu);d->gpu=dw4_gl_layer_open(w,h);
    return d->gpu?dw4_gl_layer_info(d->gpu):NULL;
}
int dw4_evodemo_draw(dw4_evodemo *d,dw4_fb *fb)
{
    if(!d || !fb)return -1;
    const dw4_ui_draw *draw;size_t n;char error[256]="";
    /* The frame clear: beBkColorInfo's colour, depth cleared (the GPU layer clears both; the CPU path below clears depth). */
    if(!d->gpu || dw4_gl_layer_clear(d->gpu,fb,d->background[0],d->background[1],d->background[2],255))
        for(size_t i=0;i<(size_t)fb->w*fb->h;i++)memcpy(fb->rgba+4*i,d->background,4);
    float view[16],projection[16];
    if(demo_camera(d,640,448,view,projection)){fail(d,"demo camera evaluation failed");return -1;}
    dw4_modelview_camera(d->view,view,projection);
    if(dw4_modelview_draw(d->view,fb->w,fb->h,&draw,&n,error,sizeof error)){snprintf(d->error,sizeof d->error,"%s",error);return -1;}
    if(!d->gpu)dw4_render_zbuf_clear(fb);
    dw4_gl_layer_ui_or_cpu(&d->gpu,fb,draw,(int)n,8);
    size_t total=n;
    if(dw4_dialogue_draw(d->dialogue,fb->w,fb->h,&draw,&n))return -1;
    dw4_gl_layer_ui_or_cpu(&d->gpu,fb,draw,(int)n,8);
    return (int)(total+n);
}
const char *dw4_evodemo_error(const dw4_evodemo *d){return d?d->error:"missing digivolution demo";}
dw4_playerrecords *dw4_evodemo_records(dw4_evodemo *d){return d?d->players:NULL;}
const dw4_be_state *dw4_evodemo_state(const dw4_evodemo *d){return d?&d->state:NULL;}
const dw4_controllers *dw4_evodemo_models(const dw4_evodemo *d){return d?d->models:NULL;}
const dw4_stageobjects *dw4_evodemo_objects(const dw4_evodemo *d){return d?d->objects:NULL;}
dw4_frontaudio *dw4_evodemo_audio(dw4_evodemo *d){return d?d->audio:NULL;}
int dw4_evodemo_info_get(const dw4_evodemo *d,dw4_evodemo_info *out)
{
    if(!d || !out)return -1;
    memset(out,0,sizeof *out);
    out->camera_demo=d->camera_demo;out->camera_ns=d->camera_time.time;out->camera_end=d->camera_time.end;
    snprintf(out->sounds,sizeof out->sounds,"%s",d->sounds);
    out->music[0]=dw4_frontaudio_stage_playing(d->audio,"DM_EVOLV");out->music[1]=dw4_frontaudio_stage_playing(d->audio,"AM_EVOLV");
    /* The original chunk 0 publishes player one's names as Lua globals. */
    dw4_script *vm=dw4_scriptengine_vm(((dw4_evodemo *)d)->scripts);dw4_script_value v;
    if(!dw4_script_get(vm,"g_oldNameP1",&v) && v.type==DW4_SCRIPT_STRING && v.string)snprintf(out->old_model,sizeof out->old_model,"%s",v.string);
    if(!dw4_script_get(vm,"g_nowNameP1",&v) && v.type==DW4_SCRIPT_STRING && v.string)snprintf(out->new_model,sizeof out->new_model,"%s",v.string);
    return 0;
}
