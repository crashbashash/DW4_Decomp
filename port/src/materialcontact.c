#include "dw4/materialcontact.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
void dw4_material_contact_begin(dw4_material_contact *c,uint32_t index,
    uint32_t current,uint32_t previous,const uint8_t exists[4])
{
    *c=(dw4_material_contact){.active=1,.current=current,.previous=previous,
        .index=index,.request_index=UINT32_MAX,.request_value=1};
    memcpy(c->exists,exists,4);
}
int dw4_material_contact_call(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    static const char *names[]={"MATisPlayer","MATisAllPlayer","MATgetPlayerNo",
        "MATisRidePlayer","MATisRideOffPlayer","MATsetRun","MATgetPlayerMatStat"};
    unsigned op=0;while(op<7 && strcmp(method,names[op]))op++;
    if(op==7)return 1;
    dw4_material_contact *c=user;*r=(dw4_script_value){0};int32_t arg=0;
    if(!c || !c->active || n!=(op>=3?1u:0u))goto bad;
    if(op>=3) {
        if(a[0].type!=DW4_SCRIPT_NUMBER || !isfinite(a[0].number) || a[0].number<INT32_MIN ||
            a[0].number>INT32_MAX || floor(a[0].number)!=a[0].number)goto bad;
        arg=(int32_t)a[0].number;
    }
    int value=0;
    if(op==0)value=c->current!=0;
    else if(op==1) {
        value=1;
        for(unsigned i=0;i<4;i++)if(c->exists[i] && !(c->current&(1u<<i))){value=0;break;}
    } else if(op==2) {
        for(unsigned i=0;i<4;i++)if(c->exists[i] && (c->current&(1u<<i)) && !(c->previous&(1u<<i))){value=(int)i;break;}
    } else if(op==5) {
        c->request_index=c->index;c->request_value=(uint8_t)arg;return 0;
    } else {
        uint32_t bit=1u<<((uint32_t)arg&31u);int now=!!(c->current&bit),old=!!(c->previous&bit);
        value=op==3?now && !old:op==4?!now && old:now?old?3:2:old?1:0;
    }
    *r=(dw4_script_value){DW4_SCRIPT_NUMBER,value,NULL,0};return 0;
bad:snprintf(error,cap,"%s requires an active material callback and valid scalar arguments",method);return -1;
}
