/* 0x00452460 igBoxComponent_Register: registers class igBoxComponent with the object system, derived from igGuiComponent.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGuiComponent_Register[];
extern char igBoxComponent_GetVTable[];
extern char thunk_igBoxComponent_GetMetaObject[];
extern char igGuiComponent_GetPublishedMetaObject_004524e0[];
extern char s_igBoxComponent_className_0051e730[];
extern char g_igBoxComponent_metaObject_0058c610[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igBoxComponent_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBoxComponent_metaObject_0058c610,           /* published MetaObject slot */
        igGuiComponent_Register,                        /* base class registrar */
        igGuiComponent_GetPublishedMetaObject_004524e0, /* base class MetaObject accessor */
        thunk_igBoxComponent_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igBoxComponent_className_0051e730,            /* class name */
        0x24,                                           /* instance size */
        igBoxComponent_GetVTable,                       /* vtable getter */
        0,                                              /* field adder */
        0,                                              /* extra callback item */
        0                                               /* callback list */
    );
}
