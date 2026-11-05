/* 0x001463f0 igControllerList_Register: registers class igControllerList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igControllerList_GetVTable[];
extern char thunk_igControllerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igControllerList_callbackList_00487158[];
extern char s_igControllerList_className_004d6550[];
extern char g_igControllerList_metaObject_0055f608[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();

void igControllerList_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igControllerList_metaObject_0055f608, /* published MetaObject slot */
        igObjectList_Register,                  /* base class registrar */
        igObjectList_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igControllerList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igControllerList_className_004d6550,  /* class name */
        0x14,                                   /* instance size */
        igControllerList_GetVTable,             /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        g_igControllerList_callbackList_00487158  /* callback list */
    );
}
