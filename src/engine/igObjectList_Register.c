/* 0x002bd7b0 igObjectList_Register: registers class igObjectList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igObjectList_GetVTable[];
extern char thunk_igObjectList_GetMetaObject[];
extern char igDataList_Register[];
extern char igObjectList_className[];
extern char g_igObjectList_metaObject[];
int FUN_002b5d50();
void *igMetaObject_RegisterClass();
extern int igObjectList_InitFields[4];
void *igObjectList_Register(void) {
    FUN_002b5d50();
    return igMetaObject_RegisterClass(
        0,                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObjectList_metaObject, /* published MetaObject slot */
        igDataList_Register,                /* base class registrar */
        igDataList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igObjectList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igObjectList_className,  /* class name */
        0x14,                               /* instance size */
        igObjectList_GetVTable,             /* vtable getter */
        igObjectList_InitFields,            /* field adder */
        0,                                  /* extra callback item */
        0                                   /* callback list */
    );
}
