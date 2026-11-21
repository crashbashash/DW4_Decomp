#ifndef DW4_IGMETAENUM_H
#define DW4_IGMETAENUM_H

struct igMetaEnum;

#ifdef __cplusplus
extern "C" {
#endif
int igMetaEnum_GetEmpty(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "dw4/core/igResult.h"
struct igStringRef;
/* Looks a value up by its name; fails when the enum has no such name. */
#endif

#endif
