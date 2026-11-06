/* 0x001a60d0 igAppearanceList_Register: registers class igAppearanceList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAppearanceList_GetVTable[];
extern char thunk_igAppearanceList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAppearanceList_callbackList[];
extern char igAppearanceList_className[];
extern char g_igAppearanceList_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAppearanceList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAppearanceList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                  /* base class registrar */
        igObjectList_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igAppearanceList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAppearanceList_className,  /* class name */
        0x14,                                   /* instance size */
        igAppearanceList_GetVTable,             /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        g_igAppearanceList_callbackList  /* callback list */
    );
}
