#include "dw4/controllers.h"
#include "arenalist.h"
#include "dw4/modelsubcom.h"
#include "dw4/modelai.h"
#include "dw4/actoranim.h"
#include "dw4/arenapack.h"
#include "dw4/frontaudio.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct bone_motion {char *name;dw4_actoranim *animation;struct bone_motion *next;};
struct receiver {
    dw4_controllers *owner;
    const dw4_stageobject *info;
    dw4_modelctrl *model;
    const dw4_modelctrl *external;
    int32_t slot;
    uint64_t token,enemy_token;
    dw4_script_model state;
    int bound;
    int prop;   /* KIND_OBJECT: answers player bullets through its own hit_<model>.lua when the pack carries one (breakable props) */
    struct bone_motion *motions;
    dw4_scene bone_scene;int bone_scene_valid,dependency_peer;
    dw4_arena_pack track_pack;dw4_handle track;
};
struct dw4_controllers {
    dw4_arena *arena;dw4_handle object;
    int frame_valid;int64_t frame_clock;
    dw4_scriptservices *sd;
    const dw4_stageobjects *objects;dw4_frontaudio *audio;
    struct receiver **receiver;
    size_t n;
    struct receiver **peers;size_t npeers;
    /* HITPLAYERTALK group (390e80): receiver indices in accepted info/RAM order. */
    size_t *talk,ntalk;
    char error[256];
    dw4_controllers_action action;void *action_user;
};
static int bind_dependencies(struct receiver *);
static int track_publish(struct receiver *);
static beModelCtrl *manager(const dw4_controllers *c)
{return DW4_ARENA_OBJ(c->arena,beModelCtrl,c->object);}
static int accept_info(dw4_controllers *c,const dw4_stageobject *info)
{
    int32_t list=manager(c)->_infoList;int n=al_count(c->arena,list);int32_t *v=al_words(c->arena,list);
    for(int i=0;i<n;i++)if(v[i]==(int32_t)info->object.off)return 0;
    if(al_reserve(c->arena,list,4,n+1))return -1;
    igDataList *l=al_list(c->arena,list);v=dw4_arena_at(c->arena,al_handle(l->_data),(uint32_t)(n+1)*4);
    v[n]=(int32_t)info->object.off;l->_count=n+1;return 0;
}
static void action_event(void *user,const char *sequence,const char *type,const char *name,int64_t ns)
{
    struct receiver *r=user;(void)sequence;(void)ns;
    if(r->owner->action && !strcmp(type,"beModelCtrlACTION"))r->owner->action(r->owner->action_user,dw4_stageobject_name(r->info),name);
}
void dw4_controllers_actions(dw4_controllers *c,dw4_controllers_action action,void *user)
{
    if(!c)return;
    c->action=action;c->action_user=user;
    for(size_t i=0;i<c->n;i++)if(!c->receiver[i]->external)dw4_modelctrl_observe(c->receiver[i]->model,action?action_event:NULL,action?c->receiver[i]:NULL);
}
static uint32_t field(const dw4_igb_record *r,unsigned ordinal) {
    for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;
    return UINT32_MAX;
}
static struct receiver *named_receiver(dw4_controllers *c,const char *name,int32_t slot)
{
    for(size_t i=0;i<c->n;i++){struct receiver *r=c->receiver[i];
        if(r->slot==slot && !strcmp(dw4_stageobject_name(r->info),name))return r;}
    for(size_t i=0;i<c->npeers;i++){struct receiver *r=c->peers[i];
        if(r->model && r->slot==slot && !strcmp(dw4_stageobject_name(r->info),name))return r;}
    return NULL;
}
static int effect_event(void *u,dw4_modelctrl *source,dw4_handle h,int finish,int *keep)
{
    dw4_controllers *c=((struct receiver *)u)->owner;beModelCtrlSCEffect *e=DW4_ARENA_OBJ(c->arena,beModelCtrlSCEffect,h);
    const char *name=al_text(c->arena,e->_modelName);
    if(finish){
        struct receiver *r=named_receiver(c,name,e->_geneRamNo);
        if(r && !r->external && !r->dependency_peer && dw4_modelctrl_active(r->model)){
            dw4_modelctrl_request_erase(r->model);dw4_scriptservices_active(c->sd,r->token,1);
            if(r->enemy_token)dw4_scriptservices_active(c->sd,r->enemy_token,1);
        }
        return 0;
    }
    *keep=0;
    for(size_t i=0;i<c->n;i++){
        struct receiver *r=c->receiver[i];
        if(r->external || strcmp(dw4_stageobject_name(r->info),name) || dw4_modelctrl_active(r->model))continue;
        /* FIND_SPACE uses accepted info/RAM order. The occupied slot is stored
         * before generation; finish later addresses that identity, not a host
         * pointer that can dangle or change after reuse. */
        e->_geneRamNo=r->slot;float offset[3],rotation[3];memcpy(offset,e->_offset,12);memcpy(rotation,e->_rotation,12);
        const char *kind=dw4_stageobject_kind_string(r->info);int rc;
        if(kind && (!strcmp(kind,"KIND_EFFECT") || !strcmp(kind,"KIND_PBULLET") || !strcmp(kind,"KIND_EBULLET")))
            rc=dw4_modelctrl_generate_effect(r->model,source,al_text(c->arena,e->_seqName),offset,rotation,e->_isPositionLock);
        else rc=dw4_modelctrl_start(r->model,al_text(c->arena,e->_seqName));
        if(rc)return -1;
        if(r->track.off && track_publish(r))return -1;
        dw4_scriptservices_active(c->sd,r->token,dw4_modelctrl_active(r->model));
        if(r->enemy_token)dw4_scriptservices_active(c->sd,r->enemy_token,dw4_modelctrl_active(r->model));
        *keep=e->_isSeqDead!=0;return 0;
    }
    return 0;
}
static int sound_play(void *u,const char *name,int64_t *h,int *type)
{return dw4_frontaudio_model_play(((struct receiver *)u)->owner->audio,name,h,type);}
static int sound_down(void *u,int64_t h)
{return dw4_frontaudio_model_down(((struct receiver *)u)->owner->audio,h);}
void dw4_controllers_audio(dw4_controllers *c,dw4_frontaudio *audio)
{if(c)c->audio=audio;}
static int decode_record(const dw4_igb *g,uint32_t id,dw4_igb_record *r)
{return id<g->table_n && g->id_kind[id]==2 && dw4_igb_decode(g,g->id_off[id],r);}
static dw4_actoranim *bone_motion(struct receiver *r,const char *name)
{
    if(!name)return NULL;
    for(struct bone_motion *m=r->motions;m;m=m->next)if(!strcmp(m->name,name))return m->animation;
    dw4_controllers *c=r->owner;const dw4_stageobject *bank=NULL;
    for(size_t i=0;i<dw4_stageobjects_count(c->objects);i++){
        const dw4_stageobject *o=dw4_stageobjects_at(c->objects,i);
        if(o->scene==r->info->scene && !strcmp(dw4_stageobject_class(o),"beAction2Info") &&
           dw4_stageobject_name(o) && !strcmp(dw4_stageobject_name(o),dw4_stageobject_name(r->info))){bank=o;break;}
    }
    if(!bank)return NULL;
    dw4_igb_record record={0};if(!decode_record(bank->igb,bank->id,&record))return NULL;
    uint32_t rootid=field(&record,7),database=field(&record,8);dw4_igb_record_free(&record);
    /* Prepared presentation graphs may omit actor skins. Decode a private
     * simulation pose graph on first demand without changing that roster. */
    if(!r->bone_scene_valid){
        if(dw4_scene_load_actor_preview(&r->bone_scene,bank->igb->data,bank->igb->size)){
            dw4_scene_close(&r->bone_scene);return NULL;
        }
        r->bone_scene_valid=1;
    }
    dw4_scene *s=&r->bone_scene;uint32_t root=0;
    while(root<s->nnode && s->node[root].id!=rootid)root++;
    if(root==s->nnode)return NULL;
    for(uint32_t n=root;n<s->nnode && (n==root || s->node[n].depth>s->node[root].depth);n++){
        if(dw4_scene_node_mesh(s,n)==UINT32_MAX)continue;
        uint32_t parent=n;
        while(parent<s->nnode && strcmp(s->node[parent].class_name,"igBlendMatrixSelect"))parent=s->node[parent].parent;
        if(parent>=s->nnode)continue;
        dw4_actoranim *a=dw4_actoranim_open_motion_database(bank->igb->data,(uint32_t)bank->igb->size,s,n,name,database,c->error,sizeof c->error);
        if(!a)return NULL;
        struct bone_motion *m=calloc(1,sizeof *m);char *copy=strdup(name);
        if(!m || !copy){free(m);free(copy);dw4_actoranim_close(a);return NULL;}
        *m=(struct bone_motion){copy,a,r->motions};r->motions=m;return a;
    }
    return NULL;
}
int dw4_controllers_bone(dw4_controllers *c,const char *name,int32_t slot,const char *bone,float out[16])
{
    if(!c || !name || !bone || !out)return -1;
    struct receiver *r=named_receiver(c,name,slot);if(!r)return 0;
    const dw4_modelctrl *source=r->external?r->external:r->model;if(!dw4_modelctrl_active(source))return 0;
    dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(source,&actor);
    dw4_actoranim *a=bone_motion(r,actor.motion);if(!a)return -1;
    dw4_actoranim_loop(a,actor.motion_loop);dw4_actoranim_blend(a,0,0);
    if(actor.previous_motion && actor.blend_ns>0 && actor.motion_ns<actor.blend_ns){
        dw4_actoranim *previous=bone_motion(r,actor.previous_motion);if(!previous)return -1;
        if(dw4_actoranim_blend_motion(a,previous,actor.previous_motion_ns*1e-9,1.f-(float)((double)actor.motion_ns/actor.blend_ns)))return -1;
    }
    float local[16],world[16];
    if(dw4_actoranim_bone(a,bone,actor.motion_ns*1e-9,local))return 0;
    dw4_modelctrl_matrix(source,world);dw4_model_local_matrix(out,world,local);return 1;
}
static int bone_world(void *u,dw4_modelctrl *child,const char *name,const char *bone,float out[16])
{
    dw4_controllers *c=((struct receiver *)u)->owner;dw4_modelctrl_record rec=dw4_modelctrl_records(child);
    int32_t slot=DW4_ARENA_OBJ(c->arena,beBaseInfoRam,rec.ram)->_ramNo;
    return dw4_controllers_bone(c,name,slot,bone,out);
}
static int track_publish(struct receiver *r)
{
    if(!r->track.off)return 0;
    dw4_controllers *c=r->owner;beModelCtrlInfoDataTrc *t=DW4_ARENA_OBJ(c->arena,beModelCtrlInfoDataTrc,r->track);
    uint32_t recorder=UINT32_MAX;
    for(uint32_t i=0;i<r->track_pack.nids;i++)if(r->track_pack.map[i].off==(uint32_t)t->_recorderNode){recorder=i;break;}
    dw4_scene snapshot=*r->info->scene;uint32_t node=0;
    while(node<snapshot.nnode && snapshot.node[node].id!=recorder)node++;
    if(node==snapshot.nnode){snprintf(c->error,sizeof c->error,"TRC recorder missing from model graph");return -1;}
    dw4_scene_node *nodes=malloc((size_t)snapshot.nnode*sizeof *nodes);if(!nodes)return -1;
    memcpy(nodes,snapshot.node,(size_t)snapshot.nnode*sizeof *nodes);snapshot.node=nodes;
    const dw4_modelctrl *m=r->external?r->external:r->model;int64_t ns=dw4_modelctrl_time(m);
    /* Sample a private graph, never the renderer's presentation copy. A
     * recorder captures its graph-world matrix at the source Action2 clock. */
    for(uint32_t p=node;p<snapshot.nnode;p=nodes[p].parent){
        if(nodes[p].has_seq)dw4_scene_node_drive(&snapshot,p,0,ns);
        if(!strcmp(nodes[p].class_name,"beModelCtrlNode2")){dw4_modelctrl_matrix(m,nodes[p].m);nodes[p].has_matrix=1;break;}
    }
    dw4_scene_set_engine_time(&snapshot,0);float matrix[16];int rc=dw4_scene_node_world(&snapshot,node,matrix);free(nodes);
    if(rc)return -1;
    unsigned char *record=dw4_arena_at(c->arena,al_handle(t->_recorderNode),160);if(!record)return -1;
    memcpy(record+96,matrix,64);return 0;
}
static int track_data(void *u,dw4_modelctrl *child,const char *name,dw4_handle *out)
{
    dw4_controllers *c=((struct receiver *)u)->owner;dw4_modelctrl_record rec=dw4_modelctrl_records(child);
    int32_t slot=DW4_ARENA_OBJ(c->arena,beBaseInfoRam,rec.ram)->_ramNo;
    struct receiver *r=named_receiver(c,name,slot);
    if(!r || !dw4_modelctrl_active(r->external?r->external:r->model))return 0;
    if(!r->track.off){
        const dw4_igb *g=r->info->igb;dw4_igb_record record={0};if(!decode_record(g,r->info->id,&record))return -1;
        uint32_t list=field(&record,5);dw4_igb_record_free(&record);
        if(!decode_record(g,list,&record))return -1;
        uint32_t n=field(&record,2),bytes=0;const uint8_t *v=dw4_igb_block(g,field(&record,4),&bytes);dw4_igb_record_free(&record);
        if(n && (!v || n>bytes/4))return -1;
        for(uint32_t i=0;i<n;i++){
            uint32_t id;memcpy(&id,v+4*i,4);if(!decode_record(g,id,&record))return -1;
            int match=!strcmp(record.class_name,"beModelCtrlInfoDataTrc") && record.name && !strcmp(record.name,"TRC");dw4_igb_record_free(&record);
            if(!match)continue;
            if(dw4_arena_pack_load_from(c->arena,DW4_REGION_PERSISTENT,g,&id,1,&r->track_pack,c->error,sizeof c->error))return -1;
            r->track=dw4_arena_pack_handle(&r->track_pack,id);break;
        }
    }
    if(r->track.off && track_publish(r))return -1;
    *out=r->track;return r->track.off!=0;
}
static void dependencies_release(void *u)
{
    struct receiver *r=u;
    if(r->dependency_peer){
        if(r->model)dw4_modelctrl_bind_record(r->model,r->slot,(dw4_handle){0},(dw4_handle){0});
        r->model=NULL;
    }
}
static int bind_dependencies(struct receiver *r)
{
    dw4_modelctrl_dependencies d={r,effect_event,sound_play,sound_down,bone_world,track_data,dependencies_release};
    return dw4_modelctrl_dependencies_bind(r->model,&d);
}
static void receiver_resources_close(struct receiver *r)
{
    for(struct bone_motion *b=r->motions,*next;b;b=next){next=b->next;dw4_actoranim_close(b->animation);free(b->name);free(b);}
    dw4_scene_close(&r->bone_scene);
    dw4_arena_pack_release(r->owner->arena,&r->track_pack);free(r);
}
static int instance_count(const dw4_stageobject *info,uint32_t *count) {
    const dw4_igb *g=(info)->igb;dw4_igb_record r={0};uint32_t list;
    if(info->id>=g->table_n || !dw4_igb_decode(g,g->id_off[info->id],&r))return -1;
    list=field(&r,6);dw4_igb_record_free(&r);
    if(list==UINT32_MAX){*count=0;return 0;}
    if(list>=g->table_n || g->id_kind[list]!=2 || !dw4_igb_decode(g,g->id_off[list],&r))return -1;
    int valid=!strcmp(r.class_name,"beBaseInfoRamList");*count=field(&r,2);
    uint32_t bytes=0;const uint8_t *array=dw4_igb_block(g,field(&r,4),&bytes);
    dw4_igb_record_free(&r);
    if(!valid || *count>INT32_MAX || (*count && (!array || *count>bytes/4)))return -1;
    return 0;
}
static int service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *result,char *error,size_t cap) {
    struct receiver *r=user;
    int rc=dw4_modelctrl_service(r->model,method,a,n,result,error,cap);
    dw4_scriptservices_active(r->owner->sd,r->token,dw4_modelctrl_active(r->model));
    if(r->enemy_token)dw4_scriptservices_active(r->owner->sd,r->enemy_token,dw4_modelctrl_active(r->model));
    if(rc)snprintf(r->owner->error,sizeof(r->owner->error),"MODELCTRL %s[%d]: %.180s",
        dw4_stageobject_name(r->info),r->slot,error);
    return rc;
}
void dw4_controllers_close(dw4_controllers *c) {
    if(!c)return;
    /* Specialized owners can outlive this manager. Finish through the old
     * services while all generated children and media still exist. */
    for(size_t i=0;i<c->npeers;i++)if(c->peers[i]->model)dw4_modelctrl_dependencies_bind(c->peers[i]->model,NULL);
    /* Finish while every generated child and media/registry receiver still
     * exists. Closing in record order could otherwise call a freed sibling. */
    for(size_t i=0;i<c->n;i++)if(!c->receiver[i]->external)dw4_modelctrl_remove(c->receiver[i]->model);
    for(size_t i=0;i<c->n;i++) {
        dw4_scriptservices_unregister(c->sd,c->receiver[i]->token);
        if(c->receiver[i]->enemy_token)dw4_scriptservices_unregister(c->sd,c->receiver[i]->enemy_token);
        if(!c->receiver[i]->external){dw4_modelctrl_script(c->receiver[i]->model,NULL,0,NULL);dw4_modelctrl_close(c->receiver[i]->model);}
    }
    /* Retained track references in any model are gone before their closure. */
    for(size_t i=0;i<c->n;i++)receiver_resources_close(c->receiver[i]);
    for(size_t i=0;i<c->npeers;i++)receiver_resources_close(c->peers[i]);
    if(c->object.off){al_drop(c->arena,&manager(c)->_infoList);dw4_arena_object_release(c->arena,c->object);}
    free(c->talk);free(c->receiver);free(c->peers);free(c);
}
dw4_controllers *dw4_controllers_open(dw4_scriptservices *sd,uint64_t scope,
    const dw4_stageobjects *objects,const char *const *exclude,size_t nexclude,
    dw4_random *random,uint32_t *rhythm,dw4_scriptengine *scripts) {
    return dw4_controllers_open_party(sd,scope,objects,exclude,nexclude,random,rhythm,scripts,NULL,0);
}
/* As dw4_controllers_open; `party[s]` (s < nparty) names the player model of co-op slot s: an excluded model is not created for the slots a party
 * member occupies (the lobby owns those players' controllers), only for slot 0 as before. */
dw4_controllers *dw4_controllers_open_party(dw4_scriptservices *sd,uint64_t scope,
    const dw4_stageobjects *objects,const char *const *exclude,size_t nexclude,
    dw4_random *random,uint32_t *rhythm,dw4_scriptengine *scripts,const char *const *party,unsigned nparty) {
    if(!sd || !dw4_stageobjects_layers(objects))return NULL;
    dw4_controllers *c=calloc(1,sizeof(*c));if(!c)return NULL;c->sd=sd;c->objects=objects;
    c->arena=dw4_session_arena();const dw4_metaobject *mo=dw4_metaobject_find("beModelCtrl");
    if(!c->arena || !(c->object=dw4_arena_object_new(c->arena,DW4_REGION_PERSISTENT,mo->vtable)).off)goto fail;
    manager(c)->_infoList=al_new(c->arena,"beModelCtrlInfoList",4,0,NULL);manager(c)->_isUpdateRun=1;
    if(!manager(c)->_infoList)goto fail;

    for(size_t i=0;i<dw4_stageobjects_count(objects);i++) {
        const dw4_stageobject *info=dw4_stageobjects_at(objects,i);
        if(strcmp(dw4_stageobject_class(info),"beModelCtrlInfo"))continue;
        const char *name=dw4_stageobject_name(info);
        if(!name)goto fail;
        int skip=0,excluded=0;
        for(size_t j=0;j<nexclude;j++)if(!strcmp(name,exclude[j]))excluded=1;
        /* Repeated info rows share their native instance owner. */
        for(size_t j=0;j<i;j++)if(dw4_stageobject_same(dw4_stageobjects_at(objects,j),info))skip=1;
        if(skip)continue;
        uint32_t count;if(instance_count(info,&count) || accept_info(c,info))goto fail;
        dw4_modelctrl *first=NULL;
        for(uint32_t slot=0;slot<count;slot++) {
            if(excluded && (!slot || (slot<nparty && !strcmp(party[slot],name))))continue;
            struct receiver *r=calloc(1,sizeof(*r));if(!r)goto fail;
            r->owner=c;r->info=info;r->slot=(int32_t)slot;
            r->model=first?dw4_modelctrl_instance(first):dw4_modelctrl_open_info((info)->igb,info->id);
            if(!first)first=r->model;
            if(!r->model){free(r);goto fail;}
            dw4_modelctrl_bind_record(r->model,(int32_t)slot,info->object,c->object);
            if(bind_dependencies(r)){dw4_modelctrl_close(r->model);free(r);goto fail;}
            dw4_modelctrl_random(r->model,random,rhythm);
            const char *kind=dw4_stageobject_kind_string(info);
            int enemy=kind && !strcmp(kind,"KIND_ENEMY");
            r->prop=kind && !strcmp(kind,"KIND_OBJECT");
            if(scripts && kind && (!strcmp(kind,"KIND_OBJECT") || enemy)) {
                /* Retail Work metadata defaults recNo to -1 (0x3510fc).
                 * GENERATE initializes zero max HP, not collection/binding. */
                r->state=(dw4_script_model){.ram_no=(int32_t)slot,.rec_no=-1,.info_name=name};
                r->bound=1;dw4_modelctrl_script(r->model,scripts,scope,&r->state);
            }
            struct receiver **p=realloc(c->receiver,(c->n+1)*sizeof(*p));
            if(!p){dw4_modelctrl_close(r->model);free(r);goto fail;}
            c->receiver=p;p[c->n++]=r;
            /* 3787a0 registers each RAM slot at info acceptance, before generation:
             * membership comes from the authored HIT talk byte, not Work activity. */
            const float *boxes;size_t nboxes;
            if(dw4_modelctrl_talk_boxes(r->model,&boxes,&nboxes)==1) {
                size_t *t=realloc(c->talk,(c->ntalk+1)*sizeof *t);if(!t)goto fail;
                c->talk=t;t[c->ntalk++]=c->n-1;
            }
            /* Heap receiver addresses stay stable while the registry grows. */
            r->token=dw4_scriptservices_register(sd,scope,"MODELCTRL",name,(int32_t)slot,0,service,r);
            if(!r->token)goto fail;
            /* Enemies also answer the ENEMY category (scripts address them as ENEMY <name> <slot> <sequence/OFCTRL/ONCTRL>). */
            if(enemy){r->enemy_token=dw4_scriptservices_register(sd,scope,"ENEMY",name,(int32_t)slot,0,service,r);if(!r->enemy_token)goto fail;}
        }
    }
    return c;
fail:
    dw4_controllers_close(c);return NULL;
}
void dw4_controllers_sample(dw4_controllers *c,int64_t ns) {
    if(c && !c->frame_valid){c->frame_clock=ns;c->frame_valid=1;}
    if(c && manager(c)->_isUpdateRun)for(size_t i=0;i<c->n;i++)dw4_modelctrl_sample(c->receiver[i]->model,ns);
}
int dw4_controllers_tick(dw4_controllers *c,int64_t ns) {
    if(!c)return 0;
    uint32_t frame=c->frame_valid?dw4_modelsubcom_frame(c->frame_clock,ns):0;c->frame_clock=ns;c->frame_valid=1;
    if(!manager(c)->_isUpdateRun)return 0;
    for(size_t i=0;i<c->n;i++) {
        struct receiver *r=c->receiver[i];
        if(r->external)continue;
        /* The status manager runs before the model's control and movement (the 395b50 order); poison pays the receiver's HP and cannot kill an enemy. */
        if(r->enemy_token && r->bound && dw4_modelctrl_status_tick(r->model,&r->state.hp,NULL)) {
            snprintf(c->error,sizeof(c->error),"MODELCTRL %s[%d] status: %.180s",dw4_stageobject_name(r->info),r->slot,dw4_modelctrl_error(r->model));return -1;
        }
        if(dw4_modelctrl_tick_frame(r->model,ns,frame)) {
            snprintf(c->error,sizeof(c->error),"MODELCTRL %s[%d]: %.180s",dw4_stageobject_name(r->info),r->slot,
                dw4_modelctrl_error(r->model));return -1;
        }
        if(r->track.off && track_publish(r))return -1;
        dw4_scriptservices_active(c->sd,r->token,dw4_modelctrl_active(r->model));
        if(r->enemy_token)dw4_scriptservices_active(c->sd,r->enemy_token,dw4_modelctrl_active(r->model));
    }
    return 0;
}
int dw4_controllers_talk(dw4_controllers *c,const dw4_model_talk_probe *probe) {
    if(!c || !probe)return -1;
    int hits=0;
    /* beMessenger_DispatchSelected visits every registered receiver in list order
     * (selector -1); inactive Work is skipped by the receiver check itself. */
    for(size_t i=0;i<c->ntalk;i++) {
        struct receiver *r=c->receiver[c->talk[i]];
        if(!dw4_modelctrl_active(r->model))continue;
        float world[16];
        dw4_modelctrl_matrix(r->model,world);
        int rc=dw4_modelctrl_talk_hit(r->model,world,probe);
        dw4_scriptservices_active(c->sd,r->token,dw4_modelctrl_active(r->model));
        if(rc<0) {
            snprintf(c->error,sizeof c->error,"MODELCTRL %s[%d] talk: %.180s",dw4_stageobject_name(r->info),r->slot,
                dw4_modelctrl_error(r->model));return -1;
        }
        hits+=rc;
    }
    return hits;
}
size_t dw4_controllers_talk_count(const dw4_controllers *c) {return c?c->ntalk:0;}
const char *dw4_controllers_error(const dw4_controllers *c) {return c?c->error:"no scene controllers";}
size_t dw4_controllers_count(const dw4_controllers *c) {return c?c->n:0;}
const dw4_modelctrl *dw4_controllers_model(const dw4_controllers *c,size_t i,const dw4_stageobject **info,int32_t *slot) {
    if(!c || i>=c->n)return NULL;
    if(info)*info=c->receiver[i]->info;
    if(slot)*slot=c->receiver[i]->slot;
    return c->receiver[i]->external?c->receiver[i]->external:c->receiver[i]->model;
}
int dw4_controllers_external(dw4_controllers *c,const dw4_stageobjects *objects,const char *name,int32_t slot,const dw4_modelctrl *model)
{
    if(!c || !objects || !name || !model || slot<0)return -1;
    const dw4_stageobject *info=dw4_stageobjects_find(objects,"beModelCtrlInfo",name,0);if(!info)return -1;
    for(size_t i=0;i<c->n;i++)if(c->receiver[i]->info==info && c->receiver[i]->slot==slot)return -1;
    struct receiver *r=calloc(1,sizeof *r);if(!r)return -1;
    struct receiver **rows=realloc(c->receiver,(c->n+1)*sizeof *rows);if(!rows){free(r);return -1;}
    r->owner=c;r->info=info;r->slot=slot;r->external=model;c->receiver=rows;rows[c->n++]=r;return 0;
}
int dw4_controllers_bind_model(dw4_controllers *c,const char *name,int32_t slot,dw4_modelctrl *model)
{
    if(!c || !name || !model || slot<0 || named_receiver(c,name,slot))return -1;
    const dw4_stageobject *info=dw4_stageobjects_find(c->objects,"beModelCtrlInfo",name,0);
    dw4_modelctrl_record rec=dw4_modelctrl_records(model);
    if(!info || rec.arena!=c->arena)return -1;
    beBaseInfoRam *ram=DW4_ARENA_OBJ(rec.arena,beBaseInfoRam,rec.ram);
    if(ram->_parentManager || ram->_parentInfo)return -1;
    struct receiver *r=calloc(1,sizeof *r);if(!r)return -1;
    struct receiver **rows=realloc(c->peers,(c->npeers+1)*sizeof *rows);if(!rows){free(r);return -1;}
    c->peers=rows;r->owner=c;r->info=info;r->slot=slot;r->model=model;r->dependency_peer=1;
    if(bind_dependencies(r)){free(r);return -1;}
    dw4_modelctrl_bind_record(model,slot,info->object,c->object);
    c->peers[c->npeers++]=r;return 0;
}
int dw4_controllers_model_state(const dw4_controllers *c,size_t i,dw4_script_model *out) {
    if(!c || i>=c->n || !out || !c->receiver[i]->bound)return -1;
    *out=c->receiver[i]->state;return 0;
}
int dw4_controllers_health(dw4_controllers *c,size_t i,int32_t hp,int32_t max_hp) {
    if(!c || i>=c->n || !c->receiver[i]->bound)return -1;
    dw4_modelctrl_health(c->receiver[i]->model,hp,max_hp);return 0;
}
int dw4_controllers_collision(dw4_controllers *c,const char *name,int32_t slot,
    dw4_modelctrl_collision collision,void *user)
{
    if(!c || !name)return -1;
    for(size_t i=0;i<c->n;i++) {
        struct receiver *r=c->receiver[i];
        if(r->slot==slot && !strcmp(dw4_stageobject_name(r->info),name)) {
            if(r->external)return -1;
            dw4_modelctrl_collide(r->model,collision,user);return 0;
        }
    }
    return -1;
}
dw4_script_model *dw4_controllers_state(dw4_controllers *c,const char *name,int32_t slot)
{
    if(!c || !name)return NULL;
    for(size_t i=0;i<c->n;i++){struct receiver *r=c->receiver[i];if(r->slot==slot && r->bound && !strcmp(dw4_stageobject_name(r->info),name))return &r->state;}
    return NULL;
}
int dw4_controllers_nearest(dw4_controllers *c,const char *name,int32_t slot,
    dw4_modelctrl_near near,void *user)
{
    if(!c || !name)return -1;
    for(size_t i=0;i<c->n;i++) {
        struct receiver *r=c->receiver[i];
        if(r->slot==slot && !strcmp(dw4_stageobject_name(r->info),name))
            return r->external?-1:dw4_modelctrl_nearest(r->model,near,user);
    }
    return -1;
}

int dw4_controllers_send(dw4_controllers *c,const char *name,int32_t slot,const char *method,
    const dw4_script_value *a,size_t n,dw4_script_value *result,char *error,size_t cap)
{
    if(!c || !name || !method)return -1;
    for(size_t i=0;i<c->n;i++) {
        struct receiver *r=c->receiver[i];
        if(r->slot==slot && !r->external && !strcmp(dw4_stageobject_name(r->info),name))return service(r,method,a,n,result,error,cap);
    }
    return -1;
}
int dw4_controllers_live(const dw4_controllers *c,const char *name,int32_t slot)
{
    if(!c || !name)return -1;
    for(size_t i=0;i<c->n;i++) {
        const struct receiver *r=c->receiver[i];
        if(r->slot==slot && !r->external && !strcmp(dw4_stageobject_name(r->info),name))return dw4_modelctrl_active(r->model);
    }
    return -1;
}

int dw4_controllers_enemy_bullet(dw4_controllers *c,dw4_model_bullet *b)
{
    int hits=0;
    if(!c || !b)return -1;
    for(size_t i=0;i<c->n;i++){
        struct receiver *r=c->receiver[i];
        if(!(r->enemy_token || r->prop) || r->external || !dw4_modelctrl_active(r->model))continue;
        float world[16];
        dw4_modelctrl_matrix(r->model,world);
        int rc=dw4_modelctrl_bullet_hit(r->model,world,b);
        if(rc<0){snprintf(c->error,sizeof c->error,"MODELCTRL %s[%d]: %.180s",dw4_stageobject_name(r->info),r->slot,dw4_modelctrl_error(r->model));return -1;}
        dw4_scriptservices_active(c->sd,r->token,dw4_modelctrl_active(r->model));
        if(r->enemy_token)dw4_scriptservices_active(c->sd,r->enemy_token,dw4_modelctrl_active(r->model));
        hits+=rc;
    }
    return hits;
}
const dw4_status *dw4_controllers_status(const dw4_controllers *c,const char *name,int32_t slot)
{
    if(!c || !name)return NULL;
    for(size_t i=0;i<c->n;i++){
        const struct receiver *r=c->receiver[i];
        if(r->slot==slot && !r->external && !strcmp(dw4_stageobject_name(r->info),name))return dw4_modelctrl_status(r->model);
    }
    return NULL;
}
size_t dw4_controllers_enemies_alive(const dw4_controllers *c,const char *name)
{
    size_t n=0;
    for(size_t i=0;c && i<c->n;i++){
        const struct receiver *r=c->receiver[i];
        if(r->enemy_token && dw4_modelctrl_active(r->model) && (!name || !strcmp(dw4_stageobject_name(r->info),name)))n++;
    }
    return n;
}

dw4_modelctrl *dw4_controllers_owned_model(dw4_controllers *c,size_t index)
{return c && index<c->n && !c->receiver[index]->external?c->receiver[index]->model:NULL;}
