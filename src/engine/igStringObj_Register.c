/* 0x002b9630 igStringObj_Register: registers class igStringObj with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igStringObj_GetVTable[];
extern char thunk_igStringObj_GetMetaObject[];
extern char igObject_Register[];
extern char igStringObj_className[];
extern char g_igStringObj_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStringObj_InitFields();

void igStringObj_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStringObj_metaObject,     /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igStringObj_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igStringObj_className,      /* class name */
        0x10,                                  /* instance size */
        igStringObj_GetVTable,                 /* vtable getter */
        &igStringObj_InitFields,               /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
