/* 0x00228420 igItemDataBaseField_Register: registers class igItemDataBaseField with the object system, derived from igCompoundMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igItemDataBaseField_GetVTable[];
extern char thunk_igItemDataBaseField_GetMetaObject[];
extern char igCompoundMetaField_Register[];
extern char g_igItemDataBaseField_callbackList[];
extern char igItemDataBaseField_className[];
extern char g_igItemDataBaseField_metaObject[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igItemDataBaseField_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igItemDataBaseField_metaObject,           /* published MetaObject slot */
        igCompoundMetaField_Register,                        /* base class registrar */
        igCompoundMetaField_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igItemDataBaseField_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        igItemDataBaseField_className,            /* class name */
        0x38,                                                /* instance size */
        igItemDataBaseField_GetVTable,                       /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        g_igItemDataBaseField_callbackList          /* callback list */
    );
}
