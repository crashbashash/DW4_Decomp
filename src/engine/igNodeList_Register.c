/* 0x0019ccd0 igNodeList_Register: registers class igNodeList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igNodeList_GetVTable[];
extern char thunk_igNodeList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igNodeList_callbackList[];
extern char igNodeList_className[];
extern char g_igNodeList_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igNodeList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNodeList_metaObject,    /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igNodeList_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        igNodeList_className,     /* class name */
        0x14,                                /* instance size */
        igNodeList_GetVTable,                /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igNodeList_callbackList   /* callback list */
    );
}
