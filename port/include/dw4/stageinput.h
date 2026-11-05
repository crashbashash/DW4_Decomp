#ifndef DW4_STAGEINPUT_H
#define DW4_STAGEINPUT_H
#include "dw4/script.h"
/* bePadManager _isPadDisable. Raw pad updates continue; getters select neutral. */
typedef struct {uint8_t disabled;} dw4_stageinput;
int dw4_stageinput_slot(const dw4_stageinput *,int32_t player);
int dw4_stageinput_service(void *,const char *,const dw4_script_value *,size_t,dw4_script_value *,char *,size_t);
#endif
