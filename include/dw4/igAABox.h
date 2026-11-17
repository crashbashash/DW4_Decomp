#ifndef DW4_IGAABOX_H
#define DW4_IGAABOX_H

struct igAABox;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
struct igMetaObject *igAABox_GetOrCreateMetaObject(void);
struct igAABox *igAABox_CreateInstance(int allocator);
void igAABox_Transform(struct igAABox *box, const float *matrix);
extern struct igMetaObject *g_igAABox_metaObject;
#ifdef __cplusplus
}
#endif

#endif
