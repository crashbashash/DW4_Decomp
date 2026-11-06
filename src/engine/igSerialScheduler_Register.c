/* 0x002312a0 igSerialScheduler_Register: registers class igSerialScheduler with the object system, derived from igInsightScheduler.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igSerialScheduler_GetVTable[];
extern char thunk_igSerialScheduler_GetMetaObject[];
extern char igInsightScheduler_GetPublishedMetaObject[];
extern char igInsightScheduler_Register[];
extern char g_igSerialScheduler_callbackList[];
extern char igSerialScheduler_className[];
extern char g_igSerialScheduler_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSerialScheduler_InitFields();

void igSerialScheduler_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSerialScheduler_metaObject,            /* published MetaObject slot */
        igInsightScheduler_Register,                        /* base class registrar */
        igInsightScheduler_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igSerialScheduler_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igSerialScheduler_className,             /* class name */
        0x10,                                               /* instance size */
        igSerialScheduler_GetVTable,                        /* vtable getter */
        &igSerialScheduler_InitFields,                      /* field adder */
        0,                                                  /* extra callback item */
        g_igSerialScheduler_callbackList           /* callback list */
    );
}
