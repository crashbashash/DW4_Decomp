/* 0x00194e80 igTransformSource_Register: registers class igTransformSource with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igTransformSource_GetMetaObject[];
extern char igObject_Register[];
extern char s_igTransformSource_className_004e12e0[];
extern char g_igTransformSource_metaObject_005611d0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igTransformSource_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        1,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransformSource_metaObject_005611d0, /* published MetaObject slot */
        igObject_Register,                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,   /* base class MetaObject accessor */
        thunk_igTransformSource_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igTransformSource_className_004e12e0,  /* class name */
        8,                                       /* instance size */
        0,                                       /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        0                                        /* callback list */
    );
}
