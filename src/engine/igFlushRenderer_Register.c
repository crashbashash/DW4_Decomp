/* 0x00233b90 igFlushRenderer_Register: registers class igFlushRenderer with the object system, derived from igRenderer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRenderer_GetPublishedMetaObject_00231010[];
extern char igFlushRenderer_GetVTable[];
extern char thunk_igFlushRenderer_GetMetaObject[];
extern char igRenderer_Register[];
extern char s_igFlushRenderer_className_004e87b0[];
extern char g_igFlushRenderer_metaObject_0056dc48[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();

void igFlushRenderer_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFlushRenderer_metaObject_0056dc48,      /* published MetaObject slot */
        igRenderer_Register,                        /* base class registrar */
        igRenderer_GetPublishedMetaObject_00231010, /* base class MetaObject accessor */
        thunk_igFlushRenderer_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igFlushRenderer_className_004e87b0,       /* class name */
        0xC,                                        /* instance size */
        igFlushRenderer_GetVTable,                  /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
