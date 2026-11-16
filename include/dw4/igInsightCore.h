#ifndef DW4_IGINSIGHTCORE_H
#define DW4_IGINSIGHTCORE_H

struct igInsightCore;
struct igMetaObject;
struct igObject;

#ifdef __cplusplus
extern "C" {
#endif

/* The core's manager whose meta object is `kind`, or null. */
struct igObject *igInsightCore_FindManager(struct igInsightCore *core, struct igMetaObject *kind);

#ifdef __cplusplus
}
#endif

#endif
