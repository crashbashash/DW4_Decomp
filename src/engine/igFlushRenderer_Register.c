/* 0x00233b90 igFlushRenderer_Register: registers class igFlushRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject[];
extern char igFlushRenderer_GetVTable[];
extern char thunk_igFlushRenderer_GetMetaObject[];
extern char igRenderer_Register[];
extern char igFlushRenderer_className[];
extern char g_igFlushRenderer_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igFlushRenderer_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFlushRenderer_metaObject,      /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igFlushRenderer_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igFlushRenderer_className,       /* class name */
        0xC,                                        /* instance size */
        igFlushRenderer_GetVTable,                  /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
