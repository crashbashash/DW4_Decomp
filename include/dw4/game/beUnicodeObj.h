#ifndef DW4_BEUNICODEOBJ_H
#define DW4_BEUNICODEOBJ_H

struct beUnicodeObj;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void beUnicodeObj_AllocateBuffer(struct beUnicodeObj *self, int length);
struct beUnicodeObj *beUnicodeObj_Create(int allocator);

extern struct igMetaObject *g_beUnicodeObj_metaObject;

#ifdef __cplusplus
}
#endif

#endif
