/* 0x001e5820 igDataPumpInfo_Register: registers class igDataPumpInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject[];
extern char igDataPumpInfo_GetVTable[];
extern char thunk_igDataPumpInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igDataPumpInfo_callbackList[];
extern char igDataPumpInfo_className[];
extern char g_igDataPumpInfo_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDataPumpInfo_InitFields();

void igDataPumpInfo_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDataPumpInfo_metaObject,   /* published MetaObject slot */
        igInfo_Register,                        /* base class registrar */
        igInfo_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igDataPumpInfo_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igDataPumpInfo_className,    /* class name */
        0x18,                                   /* instance size */
        igDataPumpInfo_GetVTable,               /* vtable getter */
        &igDataPumpInfo_InitFields,             /* field adder */
        0,                                      /* extra callback item */
        g_igDataPumpInfo_callbackList  /* callback list */
    );
}
