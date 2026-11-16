#ifndef DW4_BEFONT_H
#define DW4_BEFONT_H

struct beFont;
struct beUnicodeObj;
struct igMetaEnum;
struct igMetaObject;
struct igNamedObjectInfo;
#ifdef __cplusplus
template <class T> struct igSmartPointer;
#endif

#ifdef __cplusplus
extern "C" {
#endif

void beFont_AddFontImages(struct beFont *self, struct igNamedObjectInfo *info);
igSmartPointer<struct beUnicodeObj> beFont_ConvertToUnicode(struct beFont *self, const char *text);
struct beFont *beFont_CreateInstance(int allocator);
struct igMetaEnum *beFont_GetAlignEnum(void);
struct igMetaEnum *beFont_GetMessageEnum(void);
struct igMetaEnum *beFont_GetSwitchEnum(void);
void beFont_Prepare(struct beFont *self);

extern struct igMetaObject *g_beFont_metaObject;

#ifdef __cplusplus
}
#endif

#endif
