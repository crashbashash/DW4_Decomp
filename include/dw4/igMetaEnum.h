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

#endif
