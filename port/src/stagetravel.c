#include "dw4/stagetravel.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
static int equal(dw4_script_value v,const char *s)
{return v.type==DW4_SCRIPT_STRING && v.string && v.length==strlen(s) && !memcmp(v.string,s,v.length);}
static int integer(dw4_script_value v,int32_t *out)
{
    if(v.type!=DW4_SCRIPT_STRING || !v.string || v.length<4 || v.length>=64)return -1;
    char text[64];memcpy(text,v.string,v.length);text[v.length]=0;
    if(text[0]!='I' || text[1]!='<')return -1;
    char *end;errno=0;long value=strtol(text+2,&end,10);
    if(errno || end==text+2 || *end!='>' || end[1] || value<INT32_MIN || value>INT32_MAX)return -1;
    *out=(int32_t)value;return 0;
}
int dw4_stagetravel_service(void *user,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    dw4_stagetravel *s=user;*r=(dw4_script_value){0};
    if(!s || (strcmp(method,"sd") && strcmp(method,"querySD")) || (n!=4 && n!=5))goto bad;
    if(equal(a[0],"STAGECTL")) {
        if(equal(a[3],"PADINPUT"))return dw4_stageinput_service(s->input,method,a,n,r,error,cap);
        if(!equal(a[3],"NEXTSTAGE") || n!=5 || a[4].type!=DW4_SCRIPT_STRING || !a[4].string ||
           !a[4].length || a[4].length>=sizeof s->destination || memchr(a[4].string,0,a[4].length))goto bad;
        /* 3cd868..3cd9b8 copies the stage value into owned storage. Filename
         * resolution and supported-destination policy belong to preparation. */
        memcpy(s->destination,a[4].string,a[4].length);s->destination[a[4].length]=0;s->pending=1;
        return 0;
    }
    if(equal(a[0],"PLAYERPOINT")) {
        if(equal(a[3],"SETGENERATEPOS") && n==5) {
            int32_t value;if(integer(a[4],&value))goto bad;
            /* 39c3c0..39c3cc stores the parsed signed word without clamping. */
            s->generate_pos=value;return 0;
        }
        if(equal(a[3],"GETGENERATEPOS") && n==4) {
            *r=(dw4_script_value){DW4_SCRIPT_NUMBER,s->generate_pos,NULL,0};return 0;
        }
    }
bad:snprintf(error,cap,"unsupported or malformed stage-travel command");return -1;
}
int dw4_stagetravel_pending(const dw4_stagetravel *s,char *stage,size_t cap,int32_t *point)
{
    if(!s || !s->pending)return 0;
    if(!stage || cap<=strlen(s->destination) || !point)return -1;
    memcpy(stage,s->destination,strlen(s->destination)+1);*point=s->generate_pos;return 1;
}
void dw4_stagetravel_ack(dw4_stagetravel *s){if(s){s->pending=0;s->destination[0]=0;}}

/* Host failed-load Back policy: retain source records/scene and replay recovered
 * control restoration with the original full-black arrival fade sequence. */
int dw4_stagetravel_restore(dw4_scriptservices *sd,uint64_t scope,dw4_stagetravel *travel,char *error,size_t cap)
{
    if(!sd || !travel || !travel->pending)return -1;
    dw4_scriptservices_scope(sd,scope);
    const char *category[]={"MODELCTRL","MODELCTRL","STAGECTL"};
    const char *command[]={"GENERATE","ONCTRL","PADINPUT"};
    const char *value[]={"SQ_BLIN60",NULL,"ENABLE"};
    for(unsigned i=0;i<3;i++) {
        dw4_script_value a[6]={{DW4_SCRIPT_STRING,0,category[i],strlen(category[i])},
            i?(dw4_script_value){0}:(dw4_script_value){DW4_SCRIPT_STRING,0,"i_fadewn01",10},
            {DW4_SCRIPT_NUMBER,i?-1:0,NULL,0},{DW4_SCRIPT_STRING,0,command[i],strlen(command[i])},
            value[i]?(dw4_script_value){DW4_SCRIPT_STRING,0,value[i],strlen(value[i])}:(dw4_script_value){0},
            {DW4_SCRIPT_NUMBER,i?30:0,NULL,0}},r;
        size_t count=6;
        if(!value[i]){a[4]=a[5];count=5;} /* fifth numeric overload: delay only */
        if(dw4_scriptservices_call(sd,"sd",a,count,&r,error,cap))return -1;
    }
    dw4_stagetravel_ack(travel);return 0;
}
