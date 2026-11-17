#ifndef DW4_IGMETAENUM_H
#define DW4_IGMETAENUM_H

struct igMetaEnum;

#ifdef __cplusplus
extern "C" {
#endif
int igMetaEnum_GetEmpty(void);
struct igMetaEnum *igMetaEnum_Create(const char *name, const char **names, int *values, int count);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "dw4/core/igResult.h"
struct igStringRef;
/* Looks a value up by its name; fails when the enum has no such name. */
extern "C" igResult igMetaEnum_GetValueByName(struct igMetaEnum *meta, const char *name, int *value);
extern "C" igStringRef igMetaEnum_GetNameByValue(const struct igMetaEnum *self, int value);
#endif

#endif
