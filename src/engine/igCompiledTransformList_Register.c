/* 0x001a3510 igCompiledTransformList_Register: registers class igCompiledTransformList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igCompiledTransformList_GetVTable[];
extern char thunk_igCompiledTransformList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCompiledTransformList_callbackList[];
extern char igCompiledTransformList_className[];
extern char g_igCompiledTransformList_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igCompiledTransformList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCompiledTransformList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                         /* base class registrar */
        igObjectList_GetPublishedMetaObject,           /* base class MetaObject accessor */
        thunk_igCompiledTransformList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igCompiledTransformList_className,  /* class name */
        0x14,                                          /* instance size */
        igCompiledTransformList_GetVTable,             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        g_igCompiledTransformList_callbackList  /* callback list */
    );
}
