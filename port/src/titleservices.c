#include "dw4/titleservices.h"
#include <stdlib.h>
#include <string.h>
struct model_receiver { dw4_title_host *host; const char *name; int target;
    dw4_scriptservices *sd; uint64_t token;
    const dw4_stageobject *native; };
struct dw4_title_services {
    dw4_scriptservices *sd;
    dw4_frontlayer *layer;
    struct model_receiver model[8];
    uint64_t token[9];
};
static int model_call(void *user,const char *method,const dw4_script_value *a,
    size_t n,dw4_script_value *r,char *error,size_t cap)
{
    struct model_receiver *m=user;
    dw4_script_value args[5];
    if(n<4 || n>5)return -1;
    memcpy(args,a,n*sizeof(*a));
    args[1]=(dw4_script_value){DW4_SCRIPT_STRING,0,m->name,strlen(m->name)};
    args[2]=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
    int rc=dw4_title_host_script_service(m->host,method,args,n,r,error,cap);
    dw4_scriptservices_active(m->sd,m->token,dw4_title_host_model(m->host,m->target)->active);
    return rc;
}
void dw4_title_services_close(dw4_title_services *s)
{
    if(!s)return;
    for(unsigned i=0;i<9;i++)dw4_scriptservices_unregister(s->sd,s->token[i]);
    free(s);
}
static dw4_title_services *open_receivers(dw4_scriptservices *sd,uint64_t scope,
    dw4_title_host *host,dw4_frontlayer *layer,const dw4_stageobjects *objects)
{
    static const char *names[]={"j_startlogo","j_startmenu01","j_startmenu02",
        "j_optionwin02","j_optioncursor11","j_optioncursor12","j_startback","i_fadewn01"};
    static const int targets[]={T_j_startlogo,T_j_startmenu01,T_j_startmenu02,
        T_j_optionwin02,T_j_optioncursor11,T_j_optioncursor12,T_j_startback,T_i_fadewn01};
    if(!sd || !host || !layer)return NULL;
    dw4_title_services *s=calloc(1,sizeof(*s));if(!s)return NULL;
    s->sd=sd;s->layer=layer;
    for(unsigned i=0;i<8;i++) {
        const dw4_stageobject *native=objects?dw4_stageobjects_find(objects,"beModelCtrlInfo",names[i],0):NULL;
        if(objects && !native)goto fail;
        const char *name=native?dw4_stageobject_name(native):names[i];
        s->model[i]=(struct model_receiver){.host=host,.name=name,.target=targets[i],.sd=sd,.native=native};
        s->token[i]=dw4_scriptservices_register(sd,scope,"MODELCTRL",name,0,
            dw4_title_host_model(host,targets[i])->active,model_call,s->model+i);
        if(!s->token[i])goto fail;
        s->model[i].token=s->token[i];
    }
    s->token[8]=dw4_scriptservices_register(sd,scope,"CAMERA",NULL,-1,1,
        dw4_frontlayer_camera_service,layer);
    if(!s->token[8])goto fail;
    return s;
fail:
    dw4_title_services_close(s);return NULL;
}
void dw4_title_services_tick(dw4_title_services *s,uint64_t ns)
{
    if(!s)return;
    dw4_frontlayer_camera_tick(s->layer,ns);
    for(unsigned i=0;i<8;i++)dw4_scriptservices_active(s->sd,s->token[i],
        dw4_title_host_model(s->model[i].host,s->model[i].target)->active);
}

dw4_title_services *dw4_title_services_open(dw4_scriptservices *sd,uint64_t scope,
    dw4_title_host *host,dw4_frontlayer *layer)
{
    return open_receivers(sd,scope,host,layer,NULL);
}
dw4_title_services *dw4_title_services_open_prepared(dw4_scriptservices *sd,uint64_t scope,
    dw4_title_host *host,dw4_frontlayer *layer,const dw4_stageobjects *objects)
{
    if(!dw4_stageobjects_layers(objects) ||
       !dw4_stageobjects_find(objects,"beCameraCtrlInfo","entry",0))return NULL;
    return open_receivers(sd,scope,host,layer,objects);
}
