/* 0x00452880 igCharMetricsList_Register: registers class igCharMetricsList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igCharMetricsList_GetVTable[];
extern char thunk_igCharMetricsList_GetMetaObject[];
extern char igCharMetricsList_className[];
extern char g_igCharMetricsList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
void FUN_00452900(void);
void igCharMetricsList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCharMetricsList_metaObject, /* published MetaObject slot */
        igDataList_Register,                     /* base class registrar */
        igDataList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igCharMetricsList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igCharMetricsList_className,  /* class name */
        0x14,                                    /* instance size */
        igCharMetricsList_GetVTable,             /* vtable getter */
        FUN_00452900,                        /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
