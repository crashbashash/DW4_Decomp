/* 0x001a7090 igAnimationSequence_Register: registers class igAnimationSequence with the object system, derived from igTransformSource.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTransformSource_Register[];
extern char igTransformSource_GetPublishedMetaObject[];
extern char thunk_igAnimationSequence_GetMetaObject[];
extern char igAnimationSequence_className[];
extern char g_igAnimationSequence_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationSequence_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        1,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationSequence_metaObject,         /* published MetaObject slot */
        igTransformSource_Register,                        /* base class registrar */
        igTransformSource_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAnimationSequence_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igAnimationSequence_className,          /* class name */
        8,                                                 /* instance size */
        0,                                                 /* vtable getter */
        0,                                                 /* field adder */
        0,                                                 /* extra callback item */
        0                                                  /* callback list */
    );
}
