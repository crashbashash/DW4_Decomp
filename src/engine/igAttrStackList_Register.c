/* 0x001a59f0 igAttrStackList_Register: registers class igAttrStackList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAttrStackList_GetVTable[];
extern char thunk_igAttrStackList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAttrStackList_callbackList_0048cd78[];
extern char s_igAttrStackList_className_004e3640[];
extern char g_igAttrStackList_metaObject_00562028[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAttrStackList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrStackList_metaObject_00562028, /* published MetaObject slot */
        igObjectList_Register,                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igAttrStackList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAttrStackList_className_004e3640,  /* class name */
        0x14,                                  /* instance size */
        igAttrStackList_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        g_igAttrStackList_callbackList_0048cd78  /* callback list */
    );
}
