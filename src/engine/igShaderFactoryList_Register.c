/* 0x00199090 igShaderFactoryList_Register: registers class igShaderFactoryList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igShaderFactoryList_GetVTable[];
extern char thunk_igShaderFactoryList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igShaderFactoryList_callbackList_0048b640[];
extern char s_igShaderFactoryList_className_004e1b80[];
extern char g_igShaderFactoryList_metaObject_00561518[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igShaderFactoryList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShaderFactoryList_metaObject_00561518, /* published MetaObject slot */
        igObjectList_Register,                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igShaderFactoryList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igShaderFactoryList_className_004e1b80,  /* class name */
        0x14,                                      /* instance size */
        igShaderFactoryList_GetVTable,             /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        g_igShaderFactoryList_callbackList_0048b640  /* callback list */
    );
}
