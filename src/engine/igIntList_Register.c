/* 0x002caba0 igIntList_Register: registers class igIntList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igIntList_GetVTable[];
extern char thunk_igIntList_GetMetaObject[];
extern char s_igIntList_className_004f8628[];
extern char g_igIntList_metaObject_00586880[];
int FUN_002b5d50();
void *igMetaObject_RegisterClass();
extern int igIntList_InitFields[4];
void *igIntList_Register(void) {
    FUN_002b5d50();
    return igMetaObject_RegisterClass(
        0,                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIntList_metaObject_00586880,   /* published MetaObject slot */
        igDataList_Register,               /* base class registrar */
        igDataList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIntList_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igIntList_className_004f8628,    /* class name */
        0x14,                              /* instance size */
        igIntList_GetVTable,               /* vtable getter */
        igIntList_InitFields,              /* field adder */
        0,                                 /* extra callback item */
        0                                  /* callback list */
    );
}
