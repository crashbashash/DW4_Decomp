/* 0x0019ccd0 igNodeList_Register: registers class igNodeList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igNodeList_GetVTable[];
extern char thunk_igNodeList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igNodeList_callbackList_0048bc78[];
extern char s_igNodeList_className_004e2388[];
extern char g_igNodeList_metaObject_00561830[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igNodeList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNodeList_metaObject_00561830,    /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNodeList_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igNodeList_className_004e2388,     /* class name */
        0x14,                                /* instance size */
        igNodeList_GetVTable,                /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igNodeList_callbackList_0048bc78   /* callback list */
    );
}
