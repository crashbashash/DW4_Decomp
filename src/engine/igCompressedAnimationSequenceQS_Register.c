/* 0x001a2950 igCompressedAnimationSequenceQS_Register: registers class igCompressedAnimationSequenceQS with the object system, derived from igAnimationSequence.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAnimationSequence_GetPublishedMetaObject_0019de40[];
extern char igCompressedAnimationSequenceQS_GetVTable[];
extern char thunk_igCompressedAnimationSequenceQS_GetMetaObject[];
extern char igAnimationSequence_Register[];
extern char g_igCompressedAnimationSequenceQS_callbackList_0048c4d8[];
extern char s_igCompressedAnimationSequenceQS_className_004e2ca0[];
extern char g_igCompressedAnimationSequenceQS_metaObject_00561c38[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igCompressedAnimationSequenceQS_InitFields();

void igCompressedAnimationSequenceQS_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCompressedAnimationSequenceQS_metaObject_00561c38, /* published MetaObject slot */
        igAnimationSequence_Register,                          /* base class registrar */
        igAnimationSequence_GetPublishedMetaObject_0019de40,   /* base class MetaObject accessor */
        thunk_igCompressedAnimationSequenceQS_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCompressedAnimationSequenceQS_className_004e2ca0,  /* class name */
        0x40,                                                  /* instance size */
        igCompressedAnimationSequenceQS_GetVTable,             /* vtable getter */
        &igCompressedAnimationSequenceQS_InitFields,           /* field adder */
        0,                                                     /* extra callback item */
        g_igCompressedAnimationSequenceQS_callbackList_0048c4d8  /* callback list */
    );
}
