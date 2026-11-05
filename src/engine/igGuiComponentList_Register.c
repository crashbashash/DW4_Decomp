/* 0x0044fec0 igGuiComponentList_Register: registers class igGuiComponentList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igGuiComponentList_GetVTable[];
extern char thunk_igGuiComponentList_GetMetaObject[];
extern char g_igGuiComponentList_callbackList_004d0578[];
extern char s_igGuiComponentList_className_0051e400[];
extern char g_igGuiComponentList_metaObject_0058c4a0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igGuiComponentList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentList_metaObject_0058c4a0, /* published MetaObject slot */
        igObjectList_Register,                    /* base class registrar */
        igObjectList_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igGuiComponentList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igGuiComponentList_className_0051e400,  /* class name */
        0x14,                                     /* instance size */
        igGuiComponentList_GetVTable,             /* vtable getter */
        0,                                        /* field adder */
        0,                                        /* extra callback item */
        g_igGuiComponentList_callbackList_004d0578  /* callback list */
    );
}
