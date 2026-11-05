/* 0x00137b90 igGenericAttrDefaultManager_Register: registers class igGenericAttrDefaultManager with the object system, derived from igAttrDefaultManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAttrDefaultManager_GetPublishedMetaObject_00130260[];
extern char igGenericAttrDefaultManager_GetVTable[];
extern char thunk_igGenericAttrDefaultManager_GetMetaObject[];
extern char igAttrDefaultManager_Register[];
extern char s_igGenericAttrDefaultManager_className_004d5700[];
extern char g_igGenericAttrDefaultManager_metaObject_0055f1c0[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igGenericAttrDefaultManager_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGenericAttrDefaultManager_metaObject_0055f1c0,    /* published MetaObject slot */
        igAttrDefaultManager_Register,                        /* base class registrar */
        igAttrDefaultManager_GetPublishedMetaObject_00130260, /* base class MetaObject accessor */
        thunk_igGenericAttrDefaultManager_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igGenericAttrDefaultManager_className_004d5700,     /* class name */
        8,                                                    /* instance size */
        igGenericAttrDefaultManager_GetVTable,                /* vtable getter */
        0,                                                    /* field adder */
        0,                                                    /* extra callback item */
        0                                                     /* callback list */
    );
}
