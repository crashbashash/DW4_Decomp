#include "dw4/stageobjects.h"
#include "dw4/titleservices.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int binding(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap) {
    (void)error;(void)cap;
    *r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
    if(!strcmp(method,"SYSgetLightMode"))r->number=*(int *)user;
    else if(!strcmp(method,"SYSisJoinPlayer"))r->number=n==1 && a[0].number==0;
    else if(!strcmp(method,"SYSgetPlayerName"))*r=(dw4_script_value){DW4_SCRIPT_STRING,0,"m_dorumon",9};
    else if(!strcmp(method,"SYSgetWeaponName"))*r=(dw4_script_value){DW4_SCRIPT_STRING,0,"w_axe01",7};
    return 0;
}
static size_t layer(dw4_stageobjects *s,const char *name) {
    for(size_t i=0;i<dw4_stageobjects_layers(s);i++)if(!strcmp(dw4_stageobjects_layer(s,i),name))return i;
    assert(0);return 0;
}
static void command(dw4_scriptservices *sd,const char *value,int delay) {
    dw4_script_value a[]={ {DW4_SCRIPT_STRING,0,"LAYERCTL",8},{0},
        {DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,"SWITCH",6},
        {DW4_SCRIPT_STRING,0,value,strlen(value)},{DW4_SCRIPT_NUMBER,delay,NULL,0} },r={0};
    char error[256];assert(!dw4_scriptservices_call(sd,"sd",a,delay?6:5,&r,error,sizeof(error)));
}
static uint32_t field(dw4_igb_record *r,unsigned ordinal) {
    for(uint32_t i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;
    assert(0);return 0;
}
static void corrupt(dw4_mount *m,int mode) {
    uint32_t n;const uint8_t *bytes=dw4_mount_entry(m,0,806,&n,NULL);
    uint8_t *blob=malloc(n);assert(blob);memcpy(blob,bytes,n);
    dw4_igb g={0};assert(!dw4_igb_open(&g,blob,n,0) && !dw4_igb_refs_open(&g));
    for(uint32_t id=0;id<g.table_n;id++)if(g.id_kind[id]==2) {
        dw4_igb_record r={0};assert(dw4_igb_decode(&g,g.id_off[id],&r));
        if(!mode && !strcmp(r.class_name,"igInfoList")) {
            uint32_t len;const uint8_t *array=dw4_igb_block(&g,field(&r,4),&len);assert(array && len);
            /* A nested data/list object is not a native info. */
            uint32_t wrong=id;memcpy(blob+(array-g.data),&wrong,4);
        } else if(mode==1 && !strcmp(r.class_name,"beLayerInfo")) {
            for(uint32_t k=0;k<r.nvalues;k++)if(r.values[k].ordinal==7) {
                /* Valid object reference, wrong target class. */
                memcpy(blob+r.values[k].voff,&id,4);
            }
        } else if(mode==2 && r.name && !strcmp(r.name,"ROOTATTR")) {
            blob[r.name-(const char *)g.data]='X';
        }
        dw4_igb_record_free(&r);
    }
    dw4_stageobjects *s=dw4_stageobjects_open();assert(s);
    int rc=dw4_stageobjects_route(s,"corrupt-title",&g,0);
    if(!mode)assert(rc==-1 && !dw4_stageobjects_count(s));
    else assert(!rc && dw4_stageobjects_bind(s)==-1 && !dw4_stageobjects_layers(s));
    dw4_scriptservices *sd=dw4_scriptservices_open();assert(sd);
    assert(dw4_stageobjects_publish(s,sd,1)==-1);
    assert(strstr(dw4_stageobjects_error(s),"corrupt-title"));
    dw4_stageobjects_close(s);dw4_scriptservices_close(sd);dw4_igb_close(&g);free(blob);
}
static void identity_and_fallback(dw4_mount *m) {
    uint32_t n;const uint8_t *bytes=dw4_mount_entry(m,0,806,&n,NULL);
    uint8_t *blob=malloc(n);assert(blob);memcpy(blob,bytes,n);
    dw4_igb g={0};assert(!dw4_igb_open(&g,blob,n,0) && !dw4_igb_refs_open(&g));
    uint32_t excluded=UINT32_MAX;
    for(uint32_t id=0;id<g.table_n;id++)if(g.id_kind[id]==2) {
        dw4_igb_record r={0};assert(dw4_igb_decode(&g,g.id_off[id],&r));
        if(!strcmp(r.class_name,"igInfoList")) {
            uint32_t len;const uint8_t *array=dw4_igb_block(&g,field(&r,4),&len);assert(array && len>=8);
            memcpy(&excluded,array,4);memcpy(blob+(array-g.data),array+4,4);
        }
        dw4_igb_record_free(&r);
    }
    assert(excluded!=UINT32_MAX);
    dw4_stageobjects *s=dw4_stageobjects_open();assert(s);
    assert(!dw4_stageobjects_route(s,"shared-title",&g,0));dw4_igb_close(&g);
    const dw4_stageobject *a=dw4_stageobjects_at(s,0),*b=dw4_stageobjects_at(s,1);
    assert(a && b && a->id==b->id && dw4_stageobject_same(a,b) && a->id!=excluded);
    for(size_t i=0;i<dw4_stageobjects_count(s);i++)assert(dw4_stageobjects_at(s,i)->id!=excluded);
    assert(dw4_stageobjects_find(s,dw4_stageobject_class(a),dw4_stageobject_name(a),1)==b);
    /* A subsequent callback uses a separate id space. Its unknown root name
     * attaches to NONE, without aliasing the title's equal numeric ids. */
    bytes=dw4_mount_data(m,"_common/w_axe01.igb",&n);assert(bytes);
    uint8_t *weapon=malloc(n);assert(weapon);memcpy(weapon,bytes,n);
    assert(!dw4_igb_open(&g,weapon,n,0) && !dw4_igb_refs_open(&g));
    for(uint32_t id=0;id<g.table_n;id++)if(g.id_kind[id]==2) {
        dw4_igb_record r={0};assert(dw4_igb_decode(&g,g.id_off[id],&r));
        if(r.name && !strcmp(r.name,"PC01"))memcpy(weapon+(r.name-(const char *)g.data),"XXXX",4);
        dw4_igb_record_free(&r);
    }
    assert(!dw4_stageobjects_route(s,"unknown-layer-weapon",&g,0));dw4_igb_close(&g);
    assert(!dw4_stageobjects_bind(s));
    const dw4_layer_attachment *last=dw4_stageobjects_attachment(s,dw4_stageobjects_attachments(s)-1);
    assert(last && !strcmp(last->info->path,"unknown-layer-weapon") && last->layer==layer(s,"NONE"));
    dw4_stageobjects_close(s);free(weapon);free(blob);
}
int main(int argc,char **argv) {
    dw4_mount m;assert(!dw4_mount_open(&m,argc>1?argv[1]:"../local/extracted"));
    int light=1;dw4_be_state state;dw4_be_init(&state);
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&light);assert(e);
    dw4_filelist *f=dw4_filelist_open(&m);assert(f);dw4_scriptengine_filelist(e,f);
    const char *stages[]={"stagIS10","stagML11"};
    const char *layers[]={"BG01","BG02","GM01","GM02","EM01","NP01","PC01","EF01","EF02","EF03",
        "BG03","GM03","WN00","WN01","WN02","WN03","WN04","FONT","LOADING","NONE"};
    unsigned cycles=argc>2?1:128;
    dw4_scriptservices *sd=dw4_scriptservices_open();assert(sd);
    for(unsigned cycle=0;cycle<cycles;cycle++) {
        unsigned i=cycle%2;light=cycle&1;
        assert(!dw4_filelist_begin(f,e,stages[i],i+1));assert(!dw4_filelist_shared(f));
        dw4_stageobjects *s=dw4_stageobjects_open();assert(s);
        assert(dw4_stageobjects_publish(s,sd,i+1)==-1);
        int rc=dw4_filelist_route_assets(f,dw4_stageobjects_route,s);
        if(rc)fprintf(stderr,"route: %s; %s\n",dw4_filelist_error(f),dw4_stageobjects_error(s));
        assert(!rc);
        assert(dw4_stageobjects_count(s)==(i?211:162));
        /* First object is the retained directory's referenced file-list info;
         * ordering is independent of the serialized record/id order. */
        const dw4_stageobject *first=dw4_stageobjects_at(s,0);
        assert(first && !strcmp(dw4_stageobject_class(first),"beFileListInfo"));
        assert(!strcmp(dw4_stageobject_name(first),stages[i]));
        assert(dw4_stageobjects_find(s,"beLuaInfo",NULL,0));
        assert(!dw4_stageobjects_find(s,"beLayerGroup",NULL,0));
        assert(!dw4_stageobjects_at(s,dw4_stageobjects_count(s)));
        assert(dw4_filelist_start(f)==-1);
        rc=dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,s);
        if(rc)fprintf(stderr,"bind: %s\n",dw4_stageobjects_error(s));
        assert(!rc);assert(dw4_stageobjects_bind(s)==-1);
        assert(dw4_stageobjects_layers(s)==20 && dw4_stageobjects_attachments(s)==(i?16:14));
        uint32_t parent;const dw4_stageobject *root=dw4_stageobjects_root(s,&parent);assert(root);
        assert(parent && dw4_scene_handle(root->scene,parent).off);
        for(size_t k=0;k<20;k++) {
            assert(!strcmp(layers[k],dw4_stageobjects_layer(s,k)));
            assert(dw4_stageobjects_layer_visible(s,k)==(k==18));
        }
        unsigned font=0,player=0,weapon=0;
        for(size_t k=0;k<dw4_stageobjects_attachments(s);k++) {
            const dw4_layer_attachment *a=dw4_stageobjects_attachment(s,k);
            assert(a && a->layer<20 && dw4_scene_handle(a->info->scene,a->root_id).off);
            font+=a->layer==17;
            if(i && !strcmp(a->info->path,"_common/m_dorumon.igb")){assert(a->layer==6);player++;}
            if(i && !strcmp(a->info->path,"_common/w_axe01.igb")){assert(a->layer==6);weapon++;}
        }
        assert(font==1 && (!i || (player==1 && weapon==1)));
        static const char *title_names[]={"j_startlogo","j_startmenu01","j_startmenu02","j_startback",
            "j_optionwin02","j_optioncursor11","j_optioncursor12","i_fadewn01"};
        static const char *window_names[]={"i_messwn","i_talkwn","n_digilffic","i_messky","i_talkky"};
        for(unsigned k=0;k<(i?5:8);k++)assert(dw4_stageobjects_find(s,"beModelCtrlInfo",i?window_names[k]:title_names[k],0));
        assert(!dw4_stageobjects_publish(s,sd,i+1));
        if(argc>2) {
            for(int j=2;j<argc;j++)command(sd,argv[j],0);
            for(size_t k=0;k<20;k++)printf("%s:%d\n",layers[k],dw4_stageobjects_layer_visible(s,k));
        } else {
            command(sd,"ALL/SET",0);command(sd,"BG02/CLR",0);
            assert(!dw4_stageobjects_layer_visible(s,layer(s,"BG02")));
            command(sd,"BG02/FLIP",0);assert(dw4_stageobjects_layer_visible(s,layer(s,"BG02")));
            command(sd,"ALL/FLIP",0);assert(dw4_stageobjects_layer_visible(s,layer(s,"BG02")));
            command(sd,"ALL/DISPOFF",0);command(sd,"WN01/DISPON",0);
            assert(dw4_stageobjects_layer_visible(s,layer(s,"WN01")));
            command(sd,"missing/SET",0);assert(!dw4_stageobjects_layer_visible(s,layer(s,"NONE")));
            command(sd,"BG02/SET",30);assert(dw4_scriptservices_pending(sd)==1);
            assert(!dw4_scriptservices_tick(sd,0));
            assert(!dw4_stageobjects_layer_visible(s,layer(s,"BG02")));
            dw4_script_value remove[]={ {DW4_SCRIPT_STRING,0,"LAYERCTL",8},{0},{DW4_SCRIPT_NUMBER,-1,NULL,0},
                {DW4_SCRIPT_STRING,0,"REMOVE",6},{DW4_SCRIPT_STRING,0,"LOADING",7}},r={0};char error[128];
            assert(!dw4_scriptservices_call(sd,"sd",remove,5,&r,error,sizeof error));
            command(sd,"ALL/SET",0);assert(!dw4_stageobjects_layer_visible(s,layer(s,"LOADING")));
        }
        /* Teardown cancels borrowed callbacks before destroying arenas. */
        assert(!dw4_scriptengine_reset_scene(e,sd));
        dw4_stageobjects_close(s);assert(!dw4_scriptservices_pending(sd));
    }
    if(argc<=2) {
        for(int mode=0;mode<3;mode++)corrupt(&m,mode);
        identity_and_fallback(&m);
    }
    dw4_scriptengine_filelist(e,NULL);dw4_scriptengine_close(e);dw4_scriptservices_close(sd);
    dw4_filelist_close(f);dw4_mount_close(&m);
    if(argc<=2)puts("native objects: ordered title/lobby infos, authored layers/roots, receivers, failed publication and 128 reloads passed");
}
