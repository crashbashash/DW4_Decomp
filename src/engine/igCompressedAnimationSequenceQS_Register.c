/* 0x001a2950 igCompressedAnimationSequenceQS_Register: registers class igCompressedAnimationSequenceQS with the object system, derived from igAnimationSequence.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAnimationSequence_GetPublishedMetaObject[];
extern char igCompressedAnimationSequenceQS_GetVTable[];
extern char thunk_igCompressedAnimationSequenceQS_GetMetaObject[];
extern char igAnimationSequence_Register[];
extern char g_igCompressedAnimationSequenceQS_callbackList[];
extern char igCompressedAnimationSequenceQS_className[];
extern char g_igCompressedAnimationSequenceQS_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCompressedAnimationSequenceQS_InitFields();

void igCompressedAnimationSequenceQS_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCompressedAnimationSequenceQS_metaObject, /* published MetaObject slot */
        igAnimationSequence_Register,                          /* base class registrar */
        igAnimationSequence_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igCompressedAnimationSequenceQS_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igCompressedAnimationSequenceQS_className,  /* class name */
        0x40,                                                  /* instance size */
        igCompressedAnimationSequenceQS_GetVTable,             /* vtable getter */
        &igCompressedAnimationSequenceQS_InitFields,           /* field adder */
        0,                                                     /* extra callback item */
        g_igCompressedAnimationSequenceQS_callbackList  /* callback list */
    );
}
