#include "dw4/fieldgen.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "dw4/modelctrl.h"
struct dw4_fieldgen {
    dw4_gene *gene;size_t count;
    dw4_scriptservices *sd;const dw4_databases *db;dw4_controllers *models;dw4_scriptengine *scripts;
    unsigned spawned;
    dw4_random *rng;
    dw4_drop *drops;size_t ndrops,cap_drops;dw4_fieldgen_drop_hook drop_hook;void *drop_user;
};
static const uint8_t *list_block(const dw4_igb *g,uint32_t list,uint32_t *count,uint32_t *bytes)
{
    dw4_igb_record r={0};uint32_t off;
    if(dw4_igb_ref(g,list,&off,NULL)!=2 || !dw4_igb_decode(g,off,&r))return NULL;
    uint32_t n=0,block=UINT32_MAX;
    for(unsigned i=0;i<r.nvalues;i++){if(r.values[i].ordinal==2)n=r.values[i].raw;if(r.values[i].ordinal==4)block=r.values[i].raw;}
    dw4_igb_record_free(&r);
    const uint8_t *p=dw4_igb_block(g,block,bytes);
    if(!p)return NULL;*count=n;return p;
}
static int read_floats(const dw4_igb *g,uint32_t list,unsigned width,uint32_t *n,float **out)
{
    uint32_t count=0,bytes=0;const uint8_t *p=list_block(g,list,&count,&bytes);
    *n=0;*out=NULL;
    if(!p)return list==UINT32_MAX?0:-1;      /* an absent list is an empty one */
    if(count*width*4>bytes)return -1;
    float *v=malloc((count?count:1)*width*sizeof *v);if(!v)return -1;
    memcpy(v,p,(size_t)count*width*4);*n=count;*out=v;return 0;
}
/* A drop list: list of beGeneraterItemData (by difficulty when the list carries all three) -> beGeneraterItemDataOneList -> beGeneraterItemDataOne rows. */
static int load_drop_list(const dw4_igb *g,uint32_t list,int difficulty,dw4_drop_entry **out,unsigned *n)
{
    *out=NULL;*n=0;
    uint32_t count=0,bytes=0;const uint8_t *p=list_block(g,list,&count,&bytes);
    if(!p || !count || count*4>bytes)return list==UINT32_MAX?0:0;
    uint32_t pick=count==3?(uint32_t)difficulty:0,id;memcpy(&id,p+4*pick,4);
    dw4_igb_record r={0};uint32_t off;
    if(dw4_igb_ref(g,id,&off,NULL)!=2 || !dw4_igb_decode(g,off,&r))return -1;
    uint32_t one=UINT32_MAX;
    if(!strcmp(r.class_name,"beGeneraterItemData"))for(unsigned i=0;i<r.nvalues;i++)if(r.values[i].ordinal==3)one=r.values[i].raw;
    dw4_igb_record_free(&r);
    uint32_t m=0,ob=0;const uint8_t *q=list_block(g,one,&m,&ob);
    if(!q || m*4>ob)return 0;
    dw4_drop_entry *v=calloc(m?m:1,sizeof *v);if(!v)return -1;
    for(uint32_t i=0;i<m;i++){
        uint32_t eid;memcpy(&eid,q+4*i,4);
        dw4_igb_record e={0};
        if(dw4_igb_ref(g,eid,&off,NULL)!=2 || !dw4_igb_decode(g,off,&e) || strcmp(e.class_name,"beGeneraterItemDataOne")){dw4_igb_record_free(&e);free(v);return -1;}
        snprintf(v[i].category,sizeof v[i].category,"%s",e.name?e.name:"");
        for(unsigned k=0;k<e.nvalues;k++){int32_t raw=(int32_t)e.values[k].raw;switch(e.values[k].ordinal){case 3:v[i].id=raw;break;case 4:v[i].rank=raw;break;case 5:v[i].rate=raw;break;}}
        dw4_igb_record_free(&e);
    }
    *out=v;*n=m;return 0;
}
static int load_player_counts_x(const dw4_igb *g,uint32_t list,dw4_gene *e,int difficulty)
{
    uint32_t count=0,bytes=0;const uint8_t *p=list_block(g,list,&count,&bytes);
    if(!p || count>4 || count*4>bytes)return -1;
    for(uint32_t i=0;i<count;i++) {
        uint32_t id;memcpy(&id,p+4*i,4);
        dw4_igb_record r={0};dw4_object o;uint32_t off;
        if(dw4_igb_ref(g,id,&off,NULL)!=2 || !dw4_igb_decode(g,off,&r))return -1;
        if(strcmp(r.class_name,"beGeneraterPlayerData") || dw4_object_from_record(&o,g,&r)){dw4_igb_record_free(&r);return -1;}
        e->count[i]=dw4_object_get_i32(&o,"_geneCount");e->max_count[i]=dw4_object_get_i32(&o,"_geneMaxCount");
        if(i==0){
            if(load_drop_list(g,dw4_object_get_ref(&o,"_itemDataList"),difficulty,&e->drops[0],&e->ndrops[0]) ||
               load_drop_list(g,dw4_object_get_ref(&o,"_itemLastDataList"),difficulty,&e->drops[1],&e->ndrops[1])){dw4_object_free(&o);dw4_igb_record_free(&r);return -1;}
        }
        dw4_object_free(&o);dw4_igb_record_free(&r);
    }
    /* A generator authored for fewer players serves larger sessions with its last row. */
    for(uint32_t i=count;i<4 && count;i++){e->count[i]=e->count[count-1];e->max_count[i]=e->max_count[count-1];}
    return 0;
}
dw4_fieldgen *dw4_fieldgen_open(dw4_mount *mount,const char *stage,int difficulty)
{
    static const char suffix[]="nhv";
    char path[96];dw4_fieldgen *g=calloc(1,sizeof *g);dw4_igfile file={0};dw4_igb igb={0};
    if(!g)return NULL;
    if(difficulty<0 || difficulty>2 || !stage)goto fail;
    snprintf(path,sizeof path,"%s/separate/generator%c.igb",stage,suffix[difficulty]);
    for(char *c=path;*c;c++)if(*c>='A' && *c<='Z')*c+=32;
    if(dw4_igfile_open_named(&file,mount,path) || dw4_igb_open(&igb,file.data,file.len,0) || dw4_igb_refs_open(&igb))goto fail;
    for(uint32_t id=0;id<igb.table_n;id++) {
        if(igb.id_kind[id]!=2)continue;
        dw4_igb_record r={0};dw4_object o;
        if(!dw4_igb_decode(&igb,igb.id_off[id],&r))continue;
        if(strcmp(r.class_name,"beGeneraterData") || !r.name){dw4_igb_record_free(&r);continue;}
        if(dw4_object_from_record(&o,&igb,&r)){dw4_igb_record_free(&r);goto fail;}
        dw4_gene *grown=realloc(g->gene,(g->count+1)*sizeof *grown);
        if(!grown){dw4_object_free(&o);dw4_igb_record_free(&r);goto fail;}
        g->gene=grown;dw4_gene *e=&g->gene[g->count++];memset(e,0,sizeof *e);
        const char *mode=dw4_object_get_str(&o,"_startModeStr"),*fill=dw4_object_get_str(&o,"_fillModeStr"),*seq=dw4_object_get_str(&o,"_geneEnemySeq");
        snprintf(e->name,sizeof e->name,"%s",r.name);snprintf(e->start_mode,sizeof e->start_mode,"%s",mode?mode:"");
        snprintf(e->fill_mode,sizeof e->fill_mode,"%s",fill?fill:"");snprintf(e->sequence,sizeof e->sequence,"%s",seq && *seq?seq:"SQ_ENTR");
        {const char *cl=dw4_object_get_str(&o,"_callLua");if(cl && *cl)snprintf(e->call_lua,sizeof e->call_lua,"%s",cl);}
        e->enemy_row=dw4_object_get_i32(&o,"_geneEnemyId");e->start_data=dw4_object_get_f32(&o,"_startData");e->fill_data=dw4_object_get_f32(&o,"_fillData");
        dw4_object_get_vec3(&o,"_pos",e->pos);e->global=dw4_object_get_i32(&o,"_genePosIsGlobal")!=0;
        uint32_t nrot=0;
        int bad=read_floats(&igb,dw4_object_get_ref(&o,"_genePosList"),3,&e->npoints,&e->points) ||
                read_floats(&igb,dw4_object_get_ref(&o,"_geneRotYRadianList"),1,&nrot,&e->rotations) ||
                load_player_counts_x(&igb,dw4_object_get_ref(&o,"_playerDataList"),e,difficulty);
        if(!bad && nrot<e->npoints)bad=1;
        dw4_object_free(&o);dw4_igb_record_free(&r);
        if(bad)goto fail;
    }
    dw4_igb_close(&igb);dw4_igfile_close(&file);return g;
fail:
    dw4_igb_close(&igb);dw4_igfile_close(&file);dw4_fieldgen_close(g);return NULL;
}
void dw4_fieldgen_close(dw4_fieldgen *g)
{
    if(!g)return;
    for(size_t i=0;i<g->count;i++){free(g->gene[i].points);free(g->gene[i].rotations);free(g->gene[i].drops[0]);free(g->gene[i].drops[1]);}
    free(g->drops);
    free(g->gene);free(g);
}
size_t dw4_fieldgen_count(const dw4_fieldgen *g){return g?g->count:0;}
const dw4_gene *dw4_fieldgen_at(const dw4_fieldgen *g,size_t i){return g && i<g->count?&g->gene[i]:NULL;}
const dw4_gene *dw4_fieldgen_find(const dw4_fieldgen *g,const char *name)
{
    for(size_t i=0;g && name && i<g->count;i++)if(!strcmp(g->gene[i].name,name))return &g->gene[i];
    return NULL;
}
unsigned dw4_fieldgen_spawned(const dw4_fieldgen *g){return g?g->spawned:0;}
void dw4_fieldgen_scripts(dw4_fieldgen *g,dw4_scriptengine *s){if(g)g->scripts=s;}
void dw4_fieldgen_attach(dw4_fieldgen *g,dw4_scriptservices *sd,const dw4_databases *db,dw4_controllers *models){if(g){g->sd=sd;g->db=db;g->models=models;}}
int dw4_fieldgen_service(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_fieldgen *g=user;*r=(dw4_script_value){0};
    /* GENERATER nil -1 ONFREEZE / OFFREEZE (no generator named: the talk scripts of the field NPCs, e.g. stag0101's n_recorder, bracket their dialogue
     * with it). Like the named forms below, freezing the generators is not ported: the call is accepted and changes nothing. */
    if(!strcmp(method,"sd") && n==4 && a[3].type==DW4_SCRIPT_STRING && a[3].string && a[3].length==8 &&
       (!memcmp(a[3].string,"ONFREEZE",8) || !memcmp(a[3].string,"OFFREEZE",8)))return 0;
    if(strcmp(method,"sd") || (n!=5 && n!=6) || a[3].type!=DW4_SCRIPT_STRING || a[4].type!=DW4_SCRIPT_STRING || !a[3].string || !a[4].string){
        snprintf(error,cap,"unsupported GENERATER call %s/%zu",method,n);return -1;
    }
    char command[24],name[16];
    if(a[3].length>=sizeof command || a[4].length>=sizeof name){snprintf(error,cap,"GENERATER operand too long");return -1;}
    memcpy(command,a[3].string,a[3].length);command[a[3].length]=0;memcpy(name,a[4].string,a[4].length);name[a[4].length]=0;
    dw4_gene *e=(dw4_gene *)dw4_fieldgen_find(g,name);
    if(!e){snprintf(error,cap,"GENERATER %s: no authored generator %s",command,name);return -1;}
    /* START begins an idle generator and resumes a stopped one; on a running or finished generator it changes nothing (stagGF03's room script starts GENE-00 on
 * every entry, which must not respawn a defeated boss). RESTART re-arms it. */
    if(!strcmp(command,"START")){if(e->state==DW4_GENE_IDLE){e->state=DW4_GENE_STARTED;e->starts++;e->armed=0;}else if(e->state==DW4_GENE_STOPPED){e->state=DW4_GENE_STARTED;e->starts++;}return 0;}
    if(!strcmp(command,"RESTART")){e->state=DW4_GENE_STARTED;e->starts++;e->armed=0;return 0;}
    if(!strcmp(command,"STOP") || !strcmp(command,"STOPREVERS")){e->state=DW4_GENE_STOPPED;return 0;}
    if(!strcmp(command,"RESET")){e->state=DW4_GENE_IDLE;e->armed=0;e->remaining=0;return 0;}
    if(!strcmp(command,"PERFECTDROP") || !strcmp(command,"ONFREEZE") || !strcmp(command,"OFFREEZE"))return 0;
    snprintf(error,cap,"unsupported GENERATER command %s",command);return -1;
}
/* One MODELCTRL GENERATE of the generator's model at its next point (FUN_00384540: cursor wraps modulo the point count). */
static int spawn(dw4_fieldgen *g,dw4_gene *e,const char *model,char *error,size_t cap)
{
    if(!e->npoints){snprintf(error,cap,"generator %s has no spawn point",e->name);return -1;}
    int32_t slot=dw4_scriptservices_first_inactive(g->sd,"MODELCTRL",model);
    if(slot<0 || e->nlive>=16)return 0;     /* the model pool is full: the wave stops (FUN_00384540 returns 0) */
    uint32_t i=e->cursor%e->npoints;const float *p=e->points+3*i;
    float world[3]={p[0],p[1],p[2]};
    if(!e->global)for(unsigned k=0;k<3;k++)world[k]+=e->pos[k];
    char value[160];snprintf(value,sizeof value,"V<%.9g,%.9g,%.9g>/V<0,%.9g,0>/%s",world[0],world[1],world[2],e->rotations[i]*57.29578f,e->sequence);
    dw4_script_value a[5]={{DW4_SCRIPT_STRING,0,"MODELCTRL",9},{DW4_SCRIPT_STRING,0,model,strlen(model)},{DW4_SCRIPT_NUMBER,slot,NULL,0},
        {DW4_SCRIPT_STRING,0,"GENERATE",8},{DW4_SCRIPT_STRING,0,value,strlen(value)}};
    dw4_script_value r;
    if(dw4_scriptservices_call(g->sd,"sd",a,5,&r,error,cap))return -1;
    /* The instance carries its stat-table row and full HP (enemy database HPMAX): script hit chunks read and edit this state. */
    dw4_script_model *state=dw4_controllers_state(g->models,model,slot);
    if(state){
        int32_t hp=0;const dw4_database *enemy=dw4_databases_get(g->db,"enemy");
        if(!enemy || dw4_database_number(enemy,e->enemy_row,"HPMAX",&hp)){snprintf(error,cap,"enemy row %d has no HPMAX",e->enemy_row);return -1;}
        state->rec_no=e->enemy_row;state->max_hp=state->hp=hp;
    }
    e->live_id[e->nlive++]=slot;e->cursor=(i+1)%e->npoints;e->spawned_total++;g->spawned++;return 1;
}
static int actor_position(const dw4_fieldgen *g,const char *model,int32_t slot,float out[3])
{
    for(size_t k=0;k<dw4_controllers_count(g->models);k++){
        const dw4_stageobject *info;int32_t s;const dw4_modelctrl *m=dw4_controllers_model(g->models,k,&info,&s);
        if(!m || s!=slot || !info || !info->object.off || strcmp(dw4_stageobject_name(info),model))continue;
        dw4_modelctrl_actor a;dw4_modelctrl_actor_state(m,&a);memcpy(out,a.position,12);return 1;
    }
    return 0;
}
static void add_drop(dw4_fieldgen *g,const dw4_gene *e,const dw4_drop_entry *d,const float pos[3])
{
    if(g->ndrops==g->cap_drops){size_t c=g->cap_drops?g->cap_drops*2:16;dw4_drop *n=realloc(g->drops,c*sizeof *n);if(!n)return;g->drops=n;g->cap_drops=c;}
    dw4_drop *o=&g->drops[g->ndrops++];memset(o,0,sizeof *o);snprintf(o->generator,sizeof o->generator,"%s",e->name);o->entry=*d;memcpy(o->position,pos,12);
    if(g->drop_hook)g->drop_hook(g->drop_user,o,g->rng);
}
/* Drop the instances that ended since the last tick from the live list; each one rolls the generator's drop list (FUN_00384800: the last enemy of the
 * generator uses _itemLastDataList). */
static void reap(dw4_fieldgen *g,dw4_gene *e,const char *model)
{
    unsigned keep=0,gone=0;int32_t ids[16];float pos[16][3];
    for(unsigned i=0;i<e->nlive;i++){
        if(dw4_scriptservices_is_active(g->sd,"MODELCTRL",model,e->live_id[i])==1){
            actor_position(g,model,e->live_id[i],e->live_pos[i]);
            memcpy(e->live_pos[keep],e->live_pos[i],12);e->live_id[keep++]=e->live_id[i];
        }else{ids[gone]=e->live_id[i];memcpy(pos[gone],e->live_pos[i],12);gone++;}
    }
    e->nlive=keep;
    for(unsigned i=0;i<gone && g->rng;i++){
        dw4_drop_entry d;int last=!e->remaining && !e->nlive && i+1==gone;
        if(dw4_fieldgen_roll_drop(e,last,dw4_random_next(g->rng),&d))add_drop(g,e,&d,pos[i]);
    }
}
int dw4_fieldgen_tick(dw4_fieldgen *g,int64_t now_ns,const float (*players)[3],unsigned nplayers,char *error,size_t cap)
{
    if(!g || !g->sd || !g->db)return 0;
    const dw4_database *enemy=dw4_databases_get(g->db,"enemy");
    if(!enemy){snprintf(error,cap,"enemy database unavailable");return -1;}
    unsigned np=nplayers<1?1:nplayers>4?4:nplayers;
    for(size_t k=0;k<g->count;k++) {
        dw4_gene *e=&g->gene[k];
        if(e->state!=DW4_GENE_STARTED && !(e->state==DW4_GENE_STOPPED && e->nlive))continue;
        const char *model=dw4_database_string(enemy,e->enemy_row,"MODEL");
        if(!model || !*model){snprintf(error,cap,"generator %s: enemy row %d has no model",e->name,e->enemy_row);return -1;}
        /* A stopped generator (the player left its region box) spawns nothing, but an instance of it that ends is still dropped from the live list and rolls its drop in
         * that tick: retail GENE-09 victims killed with the player outside the box were destroyed and their items appeared in the same tick. */
        if(e->state==DW4_GENE_STOPPED){reap(g,e,model);continue;}
        if(!e->armed){
            e->armed=1;e->wave1=0;e->remaining=e->count[np-1]>0?(unsigned)e->count[np-1]:0;
            e->boot_due_ns=!strcmp(e->start_mode,"timer")?now_ns+(int64_t)(e->start_data*1e9f/60.0f):now_ns;
            e->refill_due_ns=now_ns;
        }
        if(now_ns<e->boot_due_ns)continue;
        if(!strcmp(e->start_mode,"radar") && !e->spawned_total) {
            int near=0;
            for(unsigned p=0;p<nplayers;p++){float d=0;for(unsigned c=0;c<3;c++){float x=players[p][c]-e->pos[c];d+=x*x;}if(d<e->start_data)near=1;}
            if(!near)continue;
        }
        if(getenv("DW4_GEN_DEBUG"))fprintf(stderr,"gen %s armed model %s remaining %u fill %s nlive %u now %lld boot %lld\n",e->name,model,e->remaining,e->fill_mode,e->nlive,(long long)now_ns,(long long)e->boot_due_ns);
        reap(g,e,model);
        if(e->spawned_total && !e->remaining && !e->nlive && !e->finished && e->call_lua[0]){
            /* The wave is finished: the generator's _callLua chunk runs (stagGF03's gene00.lua opens the lift once the boss is down). */
            e->finished=1;
            char script[40];size_t cl=strlen(e->call_lua);snprintf(script,sizeof script,"%s%s",e->call_lua,cl>4 && !strcmp(e->call_lua+cl-4,".lua")?"":".lua");
            if(!g->scripts || dw4_scriptengine_run(g->scripts,script)){snprintf(error,cap,"generator %s: callLua %s: %.100s",e->name,script,g->scripts?dw4_scriptengine_error(g->scripts):"no script engine");return -1;}
            continue;
        }
        unsigned maxc=e->max_count[np-1]>0?(unsigned)e->max_count[np-1]:1;
        if(!e->remaining)continue;
        if(!e->wave1) {
            /* State 1 of the recovered machine: the first wave fills the generator to its
             * concurrent count in one tick, whatever the fill mode; the fill mode only rules the
             * maintain pass after it. Retail dng102b3 GENE-09 (add, 10 total / 6 concurrent): all
             * six within 18 ms of the player entering, remaining 4. */
            e->wave1=1;
            unsigned batch=e->remaining<maxc?e->remaining:maxc;
            for(unsigned b=0;b<batch;b++){int rc=spawn(g,e,model,error,cap);if(rc<0)return -1;if(!rc)break;e->remaining--;}
            continue;
        }
        if(!strcmp(e->fill_mode,"wipeout")) {
            if(e->nlive)continue;
            unsigned batch=e->remaining<maxc?e->remaining:maxc;
            for(unsigned b=0;b<batch;b++){int rc=spawn(g,e,model,error,cap);if(rc<0)return -1;if(!rc)break;e->remaining--;}
        } else if(!strcmp(e->fill_mode,"add")) {
            if(e->nlive<maxc){int rc=spawn(g,e,model,error,cap);if(rc<0)return -1;if(rc)e->remaining--;}
        } else if(!strcmp(e->fill_mode,"timer")) {
            if(now_ns>=e->refill_due_ns && e->nlive<maxc){
                int rc=spawn(g,e,model,error,cap);if(rc<0)return -1;
                if(rc){e->remaining--;e->refill_due_ns=now_ns+(int64_t)(e->fill_data*1e9f/60.0f);}
            }
        } else {snprintf(error,cap,"generator %s: unknown fill mode '%s'",e->name,e->fill_mode);return -1;}
    }
    return 0;
}

int dw4_fieldgen_roll_drop(const dw4_gene *e,int last,uint32_t draw,dw4_drop_entry *out)
{
    if(!e || !out)return 0;
    const dw4_drop_entry *v=e->drops[last?1:0];unsigned n=e->ndrops[last?1:0];
    int32_t r=(int32_t)(draw%10000);
    for(unsigned i=0;i<n;i++){r-=v[i].rate;if(r<=0){*out=v[i];return 1;}   /* FUN_00384800: subu then bgtz, the running remainder <= 0 selects the entry */}
    return 0;
}
const dw4_drop *dw4_fieldgen_drops(const dw4_fieldgen *g,size_t *count){if(count)*count=g?g->ndrops:0;return g?g->drops:NULL;}
void dw4_fieldgen_clear_drops(dw4_fieldgen *g){if(g)g->ndrops=0;}
void dw4_fieldgen_random(dw4_fieldgen *g,dw4_random *r){if(g)g->rng=r;}
void dw4_fieldgen_on_drop(dw4_fieldgen *g,dw4_fieldgen_drop_hook hook,void *user){if(g){g->drop_hook=hook;g->drop_user=user;}}
dw4_drop *dw4_fieldgen_inject_drop(dw4_fieldgen *g,const char *generator,const dw4_drop_entry *entry,const float position[3])
{
    const dw4_gene *e=g&&generator?dw4_fieldgen_find(g,generator):NULL;
    if(!g || !e || !entry || !position)return NULL;
    size_t before=g->ndrops;add_drop(g,e,entry,position);
    return g->ndrops>before?&g->drops[g->ndrops-1]:NULL;
}
dw4_drop *dw4_fieldgen_drops_mut(dw4_fieldgen *g,size_t *count){if(count)*count=g?g->ndrops:0;return g?g->drops:NULL;}
