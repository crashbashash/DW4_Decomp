#include "dw4/statusui.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
static dw4_script_value str(const char *s)
{return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
int dw4_statusui_call(const dw4_statusview_context *c,int query,const char *cat,
    const char *name,int32_t slot,const char *key,const char *value,char *error,size_t cap)
{
    if(!c || !c->sd || !cat || !key)return -2;
    dw4_script_value a[]={str(cat),name?str(name):(dw4_script_value){0},
        {DW4_SCRIPT_NUMBER,slot,NULL,0},str(key),{0}},r={0};
    if(value)a[4]=str(value);
    if(dw4_scriptservices_call(c->sd,query?"querySD":"sd",a,value?5:4,&r,error,cap))return -2;
    if(!query)return 0;
    if(r.type!=DW4_SCRIPT_NUMBER || !isfinite(r.number) || r.number<INT32_MIN || r.number>INT32_MAX || floor(r.number)!=r.number){
        snprintf(error,cap,"STATUS %s/%s numeric result unavailable",cat,key);return -2;
    }
    return (int32_t)r.number;
}
int dw4_statusui_positioned(const dw4_statusview_context *c,const char *name,int32_t slot,
    const char *sequence,float x,float y,float z,char *error,size_t cap)
{
    if(!name || !sequence || !isfinite(x) || !isfinite(y) || !isfinite(z))return -1;
    int active=dw4_statusui_call(c,1,"MODELCTRL",name,slot,"ISRUN",NULL,error,cap);
    if(active<0)return -1;
    if(active)return dw4_statusui_call(c,0,"MODELCTRL",name,slot,sequence,NULL,error,cap);
    char encoded[256];int n=snprintf(encoded,sizeof encoded,"%s/V<%.9g,%.9g,%.9g>",sequence,x,y,z);
    if(n<0 || (size_t)n>=sizeof encoded)return -1;
    return dw4_statusui_call(c,0,"MODELCTRL",name,slot,"GENERATE",encoded,error,cap);
}
int dw4_statusui_emit(void *w,int op,const char *group,const char *name,const char *key,const char *value,int32_t slot)
{dw4_statusview_command c={op,group,name,key,value,slot};return dw4_statusview_window_emit(w,&c);}
int dw4_statusui_open(const dw4_statusview_context *context,int (*initialize)(void *,dw4_statusview_io,void *),
    void *u,dw4_menu_window **out,char *error,size_t cap)
{
    if(!context || !initialize || !out || *out)return -1;
    dw4_statusview_context c=*context;c.initialize=initialize;c.user=u;
    *out=dw4_statusview_window_open(DW4_STATUS_CONTENT,&c);
    return *out?dw4_menu_window_tick(*out,error,cap):-1;
}
int dw4_statusui_close(dw4_menu_window *w,char *error,size_t cap)
{
    if(!w || dw4_menu_window_data(w)->_st0>=2)return 0;
    dw4_menu_window_remove(w);return dw4_menu_window_tick(w,error,cap);
}
int dw4_statusui_drain(dw4_menu_window **out,char *error,size_t cap)
{
    if(!out)return -1;
    dw4_menu_window *w=*out;if(!w)return 0;
    if(dw4_menu_window_data(w)->_st0>=2 && dw4_menu_window_tick(w,error,cap))return -1;
    if(!dw4_menu_window_data(w)->_isRun){dw4_menu_window_close(w);*out=NULL;}return 0;
}
dw4_menu_window *dw4_statusui_selector(const dw4_statusview_context *context,dw4_statusctrl *parent,
    int kind,int call,int rows,int selected,float x,float y,const uint8_t *enabled)
{
    if(!context)return NULL;
    dw4_statusview_context c=*context;c.parent=parent;c.callno=call;c.rows=rows;c.selected=selected;
    c.position[0]=x;c.position[1]=y;c.position[2]=0;c.enabled=enabled;c.selection_initialize=NULL;
    return dw4_statusview_window_open(kind,&c);
}
dw4_menu_window *dw4_statusui_selector_window(const dw4_statusview_context *context,dw4_menu_window *parent,
    int kind,int call,int rows,int selected,float x,float y,const uint8_t *enabled)
{
    if(!context || !parent)return NULL;
    dw4_statusview_context c=*context;c.parent=NULL;c.parent_window=parent;c.callno=call;c.rows=rows;c.selected=selected;
    c.position[0]=x;c.position[1]=y;c.position[2]=0;c.enabled=enabled;c.selection_initialize=NULL;
    return dw4_statusview_window_open(kind,&c);
}
