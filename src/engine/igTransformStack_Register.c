/* 0x001960d0 igTransformStack_Register: registers class igTransformStack with the object system, derived from igNonRefCountedObjectStack.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectStack_GetPublishedMetaObject[];
extern char igTransformStack_GetVTable[];
extern char thunk_igTransformStack_GetMetaObject[];
extern char igNonRefCountedObjectStack_Register[];
extern char g_igTransformStack_callbackList[];
extern char igTransformStack_className[];
extern char g_igTransformStack_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTransformStack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransformStack_metaObject,                     /* published MetaObject slot */
        igNonRefCountedObjectStack_Register,                        /* base class registrar */
        igNonRefCountedObjectStack_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTransformStack_GetMetaObject,                       /* own MetaObject accessor (stored at +0x54) */
        igTransformStack_className,                      /* class name */
        0x14,                                                       /* instance size */
        igTransformStack_GetVTable,                                 /* vtable getter */
        0,                                                          /* field adder */
        0,                                                          /* extra callback item */
        g_igTransformStack_callbackList                    /* callback list */
    );
}
