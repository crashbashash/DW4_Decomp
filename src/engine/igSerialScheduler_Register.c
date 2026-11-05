/* 0x002312a0 igSerialScheduler_Register: registers class igSerialScheduler with the object system, derived from igInsightScheduler.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igSerialScheduler_GetVTable[];
extern char thunk_igSerialScheduler_GetMetaObject[];
extern char igInsightScheduler_GetPublishedMetaObject_00231330[];
extern char igInsightScheduler_Register[];
extern char g_igSerialScheduler_callbackList_00497f80[];
extern char s_igSerialScheduler_className_004e83c0[];
extern char g_igSerialScheduler_metaObject_0056dab0[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
int igSerialScheduler_InitFields();

void igSerialScheduler_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSerialScheduler_metaObject_0056dab0,            /* published MetaObject slot */
        igInsightScheduler_Register,                        /* base class registrar */
        igInsightScheduler_GetPublishedMetaObject_00231330, /* base class MetaObject accessor */
        thunk_igSerialScheduler_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igSerialScheduler_className_004e83c0,             /* class name */
        0x10,                                               /* instance size */
        igSerialScheduler_GetVTable,                        /* vtable getter */
        &igSerialScheduler_InitFields,                      /* field adder */
        0,                                                  /* extra callback item */
        g_igSerialScheduler_callbackList_00497f80           /* callback list */
    );
}
