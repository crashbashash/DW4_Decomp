/* 0x00195f60 igTransformList_Register: registers class igTransformList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igTransformList_GetVTable[];
extern char thunk_igTransformList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igTransformList_callbackList[];
extern char igTransformList_className[];
extern char g_igTransformList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransformList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igTransformList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igTransformList_className,  /* class name */
        0x14,                                  /* instance size */
        igTransformList_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        g_igTransformList_callbackList  /* callback list */
    );
}
