/* 0x00197f50 igSkinList_Register: registers class igSkinList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igSkinList_GetVTable[];
extern char thunk_igSkinList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igSkinList_callbackList_0048b548[];
extern char s_igSkinList_className_004e1a58[];
extern char g_igSkinList_metaObject_00561488[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igSkinList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSkinList_metaObject_00561488,    /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igSkinList_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igSkinList_className_004e1a58,     /* class name */
        0x14,                                /* instance size */
        igSkinList_GetVTable,                /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igSkinList_callbackList_0048b548   /* callback list */
    );
}
