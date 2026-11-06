/* 0x001aa040 igAnimationTrack_Register: registers class igAnimationTrack with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject[];
extern char igAnimationTrack_GetVTable[];
extern char thunk_igAnimationTrack_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igAnimationTrack_callbackList[];
extern char igAnimationTrack_className[];
extern char g_igAnimationTrack_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationTrack_InitFields();

void igAnimationTrack_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationTrack_metaObject,        /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAnimationTrack_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igAnimationTrack_className,         /* class name */
        0x2C,                                          /* instance size */
        igAnimationTrack_GetVTable,                    /* vtable getter */
        &igAnimationTrack_InitFields,                  /* field adder */
        0,                                             /* extra callback item */
        g_igAnimationTrack_callbackList       /* callback list */
    );
}
