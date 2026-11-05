/* 0x00188790 igMatrix44fMetaField_Register: registers class igMatrix44fMetaField with the object system, derived from igMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMetaField_GetPublishedMetaObject_00187180[];
extern char igMatrix44fMetaField_GetVTable[];
extern char thunk_igMatrix44fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igMatrix44fMetaField_callbackList_0048ae48[];
extern char s_igMatrix44fMetaField_className_004e0af0[];
extern char g_igMatrix44fMetaField_metaObject_00561000[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igMatrix44fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMatrix44fMetaField_metaObject_00561000,  /* published MetaObject slot */
        igMetaField_Register,                        /* base class registrar */
        igMetaField_GetPublishedMetaObject_00187180, /* base class MetaObject accessor */
        thunk_igMatrix44fMetaField_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igMatrix44fMetaField_className_004e0af0,   /* class name */
        0x34,                                        /* instance size */
        igMatrix44fMetaField_GetVTable,              /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        g_igMatrix44fMetaField_callbackList_0048ae48  /* callback list */
    );
}
