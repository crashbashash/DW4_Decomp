/* 0x001436a0 igPsx2AudioSourceList_Register: registers class igPsx2AudioSourceList with the object system, derived from igDataList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igPsx2AudioSourceList_GetVTable[];
extern char thunk_igPsx2AudioSourceList_GetMetaObject[];
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char s_igPsx2AudioSourceList_className_004d5f60[];
extern char g_igPsx2AudioSourceList_metaObject_0055f5a8[];
int GpFlag_SetOnce_00142f10();
int igMetaObject_RegisterClass();

void igPsx2AudioSourceList_Register(void) {
    GpFlag_SetOnce_00142f10();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2AudioSourceList_metaObject_0055f5a8, /* published MetaObject slot */
        igDataList_Register,                         /* base class registrar */
        igDataList_GetPublishedMetaObject,           /* base class MetaObject accessor */
        thunk_igPsx2AudioSourceList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2AudioSourceList_className_004d5f60,  /* class name */
        0x14,                                        /* instance size */
        igPsx2AudioSourceList_GetVTable,             /* vtable getter */
        0,                                           /* field adder */
        0,                                           /* extra callback item */
        0                                            /* callback list */
    );
}
