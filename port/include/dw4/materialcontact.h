#ifndef DW4_MATERIALCONTACT_H
#define DW4_MATERIALCONTACT_H
#include "dw4/script.h"
/* Typed projection of the current beMatCtrl callback's published mask cells.
 * Geometry/search and callback scheduling belong to the world owner. */
typedef struct {
    int active;
    uint8_t exists[4];
    uint32_t current,previous,index,request_index;
    uint8_t request_value;
} dw4_material_contact;
/* Begin resets the deferred change to index -1/value 1, as38b1f0 does before
 * each callback. End by clearing active; consume an in-range deferred request
 * after Lua returns, before dispatching the next material. */
void dw4_material_contact_begin(dw4_material_contact *,uint32_t index,
    uint32_t current,uint32_t previous,const uint8_t exists[4]);
/* Seven original MAT helpers. 1 means unrelated method, -1 invalid context or
 * arguments, 0 handled. Player shifts retain EE low-five-bit behavior. */
int dw4_material_contact_call(void *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
#endif
