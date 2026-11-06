/* 0x001e4bd0 igMatrixObjectList_Register: registers class igMatrixObjectList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igMatrixObjectList_GetVTable[];
extern char thunk_igMatrixObjectList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igMatrixObjectList_callbackList[];
extern char igMatrixObjectList_className[];
extern char g_igMatrixObjectList_metaObject[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();

void igMatrixObjectList_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMatrixObjectList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                    /* base class registrar */
        igObjectList_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igMatrixObjectList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMatrixObjectList_className,  /* class name */
        0x14,                                     /* instance size */
        igMatrixObjectList_GetVTable,             /* vtable getter */
        0,                                        /* field adder */
        0,                                        /* extra callback item */
        g_igMatrixObjectList_callbackList  /* callback list */
    );
}
