/* Shared authored menu-resource operations; no query-time clock advancement. */
#ifndef DW4_STATUSUI_H
#define DW4_STATUSUI_H
#include "dw4/statusview.h"
int dw4_statusui_call(const dw4_statusview_context *,int query,const char *category,
    const char *name,int32_t slot,const char *key,const char *value,char *,size_t);
/* 3f5c90: active models receive the direct sequence; inactive models generate
 * with the position. No close-key tracking is added by this helper. */
int dw4_statusui_positioned(const dw4_statusview_context *,const char *name,
    int32_t slot,const char *sequence,float x,float y,float z,char *,size_t);
int dw4_statusui_emit(void *,int op,const char *group,const char *name,
    const char *key,const char *value,int32_t slot);
int dw4_statusui_open(const dw4_statusview_context *,int (*initialize)(void *,dw4_statusview_io,void *),
    void *,dw4_menu_window **,char *,size_t);
int dw4_statusui_close(dw4_menu_window *,char *,size_t);
int dw4_statusui_drain(dw4_menu_window **,char *,size_t);
dw4_menu_window *dw4_statusui_selector(const dw4_statusview_context *,dw4_statusctrl *,
    int kind,int call,int rows,int selected,float x,float y,const uint8_t *enabled);
/* The parent window outlives the selector; results publish into its arena _retCode. */
dw4_menu_window *dw4_statusui_selector_window(const dw4_statusview_context *,dw4_menu_window *,
    int kind,int call,int rows,int selected,float x,float y,const uint8_t *enabled);
#endif
