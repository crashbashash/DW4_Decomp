/* 0x001a9e80 igAnimationTrackList_Register: registers class igAnimationTrackList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationTrackList_GetVTable[];
extern char thunk_igAnimationTrackList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationTrackList_callbackList_0048d660[];
extern char s_igAnimationTrackList_className_004e42d0[];
extern char g_igAnimationTrackList_metaObject_00562428[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igAnimationTrackList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationTrackList_metaObject_00562428, /* published MetaObject slot */
        igObjectList_Register,                      /* base class registrar */
        igObjectList_GetPublishedMetaObject,        /* base class MetaObject accessor */
        thunk_igAnimationTrackList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationTrackList_className_004e42d0,  /* class name */
        0x14,                                       /* instance size */
        igAnimationTrackList_GetVTable,             /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        g_igAnimationTrackList_callbackList_0048d660  /* callback list */
    );
}
