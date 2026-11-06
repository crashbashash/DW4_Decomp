/* 0x002cb7d0 igContextExtInfo_Register: registers class igContextExtInfo with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igContextExtInfo_GetVTable[];
extern char thunk_igContextExtInfo_GetMetaObject[];
extern char igObject_Register[];
extern char g_igContextExtInfo_callbackList[];
extern char igContextExtInfo_className[];
extern char g_igContextExtInfo_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igContextExtInfo_InitFields();

void igContextExtInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igContextExtInfo_metaObject, /* published MetaObject slot */
        igObject_Register,                      /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,  /* base class MetaObject accessor */
        thunk_igContextExtInfo_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igContextExtInfo_className,  /* class name */
        0x14,                                   /* instance size */
        igContextExtInfo_GetVTable,             /* vtable getter */
        &igContextExtInfo_InitFields,           /* field adder */
        0,                                      /* extra callback item */
        g_igContextExtInfo_callbackList  /* callback list */
    );
}
