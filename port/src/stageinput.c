#include "dw4/stageinput.h"
#include <string.h>
#include <stdio.h>
static int equal(dw4_script_value v,const char *s)
{return v.type==DW4_SCRIPT_STRING && v.string && v.length==strlen(s) && !memcmp(v.string,s,v.length);}
int dw4_stageinput_slot(const dw4_stageinput *s,int32_t player)
{return !s || s->disabled || player<0 || player>=4?4:player;}
int dw4_stageinput_service(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_stageinput *s=user;*r=(dw4_script_value){0};
    if(!s || (strcmp(method,"sd") && strcmp(method,"querySD")) || (n!=4 && n!=5) || !equal(a[3],"PADINPUT")){
        snprintf(error,cap,"STAGECTL input owner requires PADINPUT");return -1;
    }
    if(n==4)return 0;
    if(equal(a[4],"ENABLE"))s->disabled=0;
    else if(equal(a[4],"DISABLE"))s->disabled=1;
    else if(equal(a[4],"STATUS"))*r=(dw4_script_value){DW4_SCRIPT_NUMBER,s->disabled,NULL,0};
    return 0; /* Unrecognized/missing optional values leave the flag unchanged. */
}
