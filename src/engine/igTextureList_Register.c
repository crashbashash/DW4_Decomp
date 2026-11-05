/* 0x0013a450 igTextureList_Register: registers class igTextureList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igTextureList_GetVTable[];
extern char thunk_igTextureList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igTextureList_callbackList_00486bd8[];
extern char s_igTextureList_className_004d5c88[];
extern char g_igTextureList_metaObject_0055f418[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igTextureList_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureList_metaObject_0055f418, /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTextureList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igTextureList_className_004d5c88,  /* class name */
        0x14,                                /* instance size */
        igTextureList_GetVTable,             /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igTextureList_callbackList_00486bd8  /* callback list */
    );
}
