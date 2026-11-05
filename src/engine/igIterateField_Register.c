/* 0x002278b0 igIterateField_Register: registers class igIterateField with the object system, derived from igIterator.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igIterator_Register[];
extern char igIterator_GetPublishedMetaObject_00227450[];
extern char igIterateField_GetVTable[];
extern char thunk_igIterateField_GetMetaObject[];
extern char g_igIterateField_callbackList_00497d80[];
extern char s_igIterateField_className_004e7c60[];
extern char g_igIterateField_metaObject_0056d968[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igIterateField_InitFields();

void igIterateField_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIterateField_metaObject_0056d968,       /* published MetaObject slot */
        igIterator_Register,                        /* base class registrar */
        igIterator_GetPublishedMetaObject_00227450, /* base class MetaObject accessor */
        thunk_igIterateField_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igIterateField_className_004e7c60,        /* class name */
        0x10,                                       /* instance size */
        igIterateField_GetVTable,                   /* vtable getter */
        &igIterateField_InitFields,                 /* field adder */
        0,                                          /* extra callback item */
        g_igIterateField_callbackList_00497d80      /* callback list */
    );
}
