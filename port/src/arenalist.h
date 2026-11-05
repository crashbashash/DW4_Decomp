/* Internal typed arena lists. Strings are owned NUL-terminated arena blocks,
 * using the same four-byte string handles as the property/pack owners. */
#ifndef DW4_ARENALIST_H
#define DW4_ARENALIST_H
#include "dw4/arena.h"
#include "dw4/object.h"
#include "dw4/reflected.h"
#include <string.h>
#include <stdint.h>
static inline dw4_handle al_handle(int32_t h){return (dw4_handle){(uint32_t)h};}
static inline igDataList *al_list(dw4_arena *a,int32_t h)
{return h?DW4_ARENA_OBJ(a,igDataList,al_handle(h)):NULL;}
static inline int al_count(dw4_arena *a,int32_t h)
{const igDataList *l=al_list(a,h);return l?l->_count:0;}
static inline void *al_data(dw4_arena *a,int32_t h,uint32_t width)
{igDataList *l=al_list(a,h);return l && l->_count?dw4_arena_at(a,al_handle(l->_data),(uint32_t)l->_count*width):NULL;}
static inline int32_t *al_words(dw4_arena *a,int32_t h){return al_data(a,h,4);}
static inline const char *al_text(dw4_arena *a,int32_t h)
{return h?dw4_arena_at(a,al_handle(h),1):NULL;}
static inline void al_free(dw4_arena *a,int32_t h){if(h)dw4_arena_free(a,al_handle(h));}
static inline int32_t al_string(dw4_arena *a,const char *s)
{
    if(!s || strlen(s)>=UINT32_MAX)return 0;
    uint32_t n=(uint32_t)strlen(s)+1;dw4_handle h=dw4_arena_alloc(a,DW4_REGION_PERSISTENT,n);
    if(h.off)memcpy(dw4_arena_at(a,h,n),s,n);
    return (int32_t)h.off;
}
static inline void al_drop(dw4_arena *a,int32_t *field)
{
    igDataList *l=al_list(a,*field);if(!l)return;
    al_free(a,l->_data);dw4_arena_object_release(a,al_handle(*field));*field=0;
}
static inline int32_t al_new(dw4_arena *a,const char *name,uint32_t width,int n,const void *data)
{
    const dw4_metaobject *mo=dw4_metaobject_find(name);
    if(!mo || !width || n<0 || (uint32_t)n>INT32_MAX/width)return 0;
    dw4_handle h=dw4_arena_object_new(a,DW4_REGION_PERSISTENT,mo->vtable);if(!h.off)return 0;
    igDataList *l=DW4_ARENA_OBJ(a,igDataList,h);
    if(n){dw4_handle b=dw4_arena_alloc(a,DW4_REGION_PERSISTENT,(uint32_t)n*width);
        if(!b.off){dw4_arena_object_release(a,h);return 0;}
        l->_data=(int32_t)b.off;if(data)memcpy(dw4_arena_at(a,b,(uint32_t)n*width),data,(size_t)n*width);}
    l->_capacity=l->_count=n;return (int32_t)h.off;
}
static inline int al_reserve(dw4_arena *a,int32_t h,uint32_t width,int want)
{
    igDataList *l=al_list(a,h);if(!l || !width || want<0 || (uint32_t)want>INT32_MAX/width)return -1;
    if(want<=l->_capacity)return 0;
    int cap=l->_capacity<4?4:l->_capacity;
    while(cap<want){if(cap>INT32_MAX/2){cap=want;break;}cap*=2;}
    if((uint32_t)cap>INT32_MAX/width)return -1;
    dw4_handle b=dw4_arena_alloc(a,DW4_REGION_PERSISTENT,(uint32_t)cap*width);if(!b.off)return -1;
    if(l->_count)memcpy(dw4_arena_at(a,b,(uint32_t)cap*width),al_data(a,h,width),(size_t)l->_count*width);
    al_free(a,l->_data);l->_data=(int32_t)b.off;l->_capacity=cap;return 0;
}
static inline void al_strings_drop(dw4_arena *a,int32_t *field)
{
    int n=al_count(a,*field);int32_t *s=al_words(a,*field);
    for(int i=0;i<n;i++)al_free(a,s[i]);
    al_drop(a,field);
}
static inline int32_t al_strings_new(dw4_arena *a,const char *const *s,int n)
{
    int32_t h=al_new(a,"igStringRefList",4,n,NULL);if(!h)return 0;
    int32_t *v=al_words(a,h);
    for(int i=0;i<n;i++)if(s[i] && !(v[i]=al_string(a,s[i]))){al_strings_drop(a,&h);return 0;}
    return h;
}
static inline void al_nested_ints_drop(dw4_arena *a,int32_t *field)
{
    int n=al_count(a,*field);int32_t *v=al_words(a,*field);
    for(int i=0;i<n;i++)al_drop(a,v+i);
    al_drop(a,field);
}
#endif
