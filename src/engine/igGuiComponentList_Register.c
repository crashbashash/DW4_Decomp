/* 0x0044fec0 igGuiComponentList_Register: registers class igGuiComponentList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igGuiComponentList_GetVTable[];
extern char thunk_igGuiComponentList_GetMetaObject[];
extern char g_igGuiComponentList_callbackList[];
extern char igGuiComponentList_className[];
extern char g_igGuiComponentList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igGuiComponentList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGuiComponentList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                    /* base class registrar */
        igObjectList_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igGuiComponentList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igGuiComponentList_className,  /* class name */
        0x14,                                     /* instance size */
        igGuiComponentList_GetVTable,             /* vtable getter */
        0,                                        /* field adder */
        0,                                        /* extra callback item */
        g_igGuiComponentList_callbackList  /* callback list */
    );
}
