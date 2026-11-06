/* 0x00188350 igRay_Register: registers class igRay with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igRay_GetVTable[];
extern char thunk_igRay_GetMetaObject[];
extern char igObject_Register[];
extern char igRay_className[];
extern char g_igRay_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igRay_InitFields();

void igRay_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRay_metaObject,           /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igRay_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        igRay_className,            /* class name */
        0x24,                                  /* instance size */
        igRay_GetVTable,                       /* vtable getter */
        &igRay_InitFields,                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
