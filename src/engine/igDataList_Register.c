/* 0x002c8580 igDataList_Register: registers class igDataList with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDataList_GetVTable[];
extern char thunk_igDataList_GetMetaObject[];
extern char igObject_Register[];
extern char igDataList_className[];
extern char g_igDataList_metaObject[];
int FUN_002b5d50();
void *igMetaObject_RegisterClass();
int igDataList_InitFields();

void *igDataList_Register(void) {
    FUN_002b5d50();
    return igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDataList_metaObject,      /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igDataList_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igDataList_className,       /* class name */
        0x14,                                  /* instance size */
        igDataList_GetVTable,                  /* vtable getter */
        &igDataList_InitFields,                /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
