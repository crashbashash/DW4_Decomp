#ifndef DW4_IGOPTBASE_H
#define DW4_IGOPTBASE_H

struct CallbackArray;
struct igOptBase;

#ifdef __cplusplus
extern "C" {
#endif
struct CallbackArray *igOptBase_Register(void);
/* igOptBase's destructor: releases the configuration and the registry, then frees the object when deleteFlag > 0. */
void *FUN_00225790(struct igOptBase *self, short deleteFlag);

#ifdef __cplusplus
}
#endif

#endif
