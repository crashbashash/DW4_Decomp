#ifndef DW4_IGCHARARRAYMETAFIELD_H
#define DW4_IGCHARARRAYMETAFIELD_H

struct igMemoryPoolView;
struct igMetaField;

#ifdef __cplusplus
extern "C" {
#endif
void igCharArrayMetaField_SetDefaultElement(void *self, int index, char value);
struct igMetaField *igCharArrayMetaField_Create(struct igMemoryPoolView *pool);

#ifdef __cplusplus
}
#endif

#endif
