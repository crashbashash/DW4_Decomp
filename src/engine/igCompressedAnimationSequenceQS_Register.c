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
        0, /* abstract */
        g_igCompressedAnimationSequenceQS_metaObject,
        igAnimationSequence_Register,
        igAnimationSequence_GetPublishedMetaObject,
        thunk_igCompressedAnimationSequenceQS_GetMetaObject,
        igCompressedAnimationSequenceQS_className,
        0x40, /* instance size */
        igCompressedAnimationSequenceQS_GetVTable,
        &igCompressedAnimationSequenceQS_InitFields,
        0, /* extra callback item */
        g_igCompressedAnimationSequenceQS_callbackList /* callback list */
    );
}
