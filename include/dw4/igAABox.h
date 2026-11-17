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
void thunk_igAABox_Transform(struct igAABox *box, const float *matrix);
/* Nonzero when the two boxes overlap. */
int igAABox_IntersectBox(const struct igAABox *box, const struct igAABox *other);
/* 2 when the point is inside the box, else 0. */
int igAABox_IntersectPoint(const struct igAABox *box, const float *point);
void igAABox_GetCenter(const struct igAABox *box, float *center);
/* Corner 0-7; bit 2 picks x, bit 1 y and bit 0 z from the minimum when set, else the maximum. */
void igAABox_GetCorner(const struct igAABox *box, unsigned int index, float *corner);
extern struct igMetaObject *g_igAABox_metaObject;
#ifdef __cplusplus
}
#endif

#endif
