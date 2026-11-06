/* 0x0019ae20 igSegment_Register: registers class igSegment with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igSegment_GetVTable[];
extern char thunk_igSegment_GetMetaObject[];
extern char igGroup_Register[];
extern char igSegment_className[];
extern char g_igSegment_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igSegment_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSegment_metaObject,         /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igSegment_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igSegment_className,          /* class name */
        0x20,                                    /* instance size */
        igSegment_GetVTable,                     /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
