/* 0x002281a0 igItemDataBaseList_Register: registers class igItemDataBaseList with the object system, derived from igCompoundList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCompoundList_Register[];
extern char igItemDataBaseList_GetVTable[];
extern char thunk_igItemDataBaseList_GetMetaObject[];
extern char igCompoundList_GetPublishedMetaObject[];
extern char igItemDataBaseList_className[];
extern char g_igItemDataBaseList_metaObject[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igItemDataBaseList_InitFields();

void igItemDataBaseList_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igItemDataBaseList_metaObject,       /* published MetaObject slot */
        igCompoundList_Register,                        /* base class registrar */
        igCompoundList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igItemDataBaseList_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igItemDataBaseList_className,        /* class name */
        0x14,                                           /* instance size */
        igItemDataBaseList_GetVTable,                   /* vtable getter */
        &igItemDataBaseList_InitFields,                 /* field adder */
        0,                                              /* extra callback item */
        0                                               /* callback list */
    );
}
