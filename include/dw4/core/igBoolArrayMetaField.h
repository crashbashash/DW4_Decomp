#ifndef DW4_IGBOOLARRAYMETAFIELD_H
#define DW4_IGBOOLARRAYMETAFIELD_H

/* igBoolArrayMetaField: the metafield class's factory and default setter. */
struct igBoolArrayMetaField;
struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaField *igBoolArrayMetaField_Create(struct igMemoryPoolView *pool);
void igBoolArrayMetaField_SetDefaultAll(struct igBoolArrayMetaField *self, int value);

#ifdef __cplusplus
}
#endif

#endif
