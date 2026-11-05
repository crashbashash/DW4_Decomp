/* 0x001a7b10 igAnimationDatabase_Register: registers class igAnimationDatabase with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject_00131c50[];
extern char igAnimationDatabase_GetVTable[];
extern char thunk_igAnimationDatabase_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igAnimationDatabase_callbackList_0048d200[];
extern char s_igAnimationDatabase_className_004e3cc0[];
extern char g_igAnimationDatabase_metaObject_00562220[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationDatabase_InitFields();

void igAnimationDatabase_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationDatabase_metaObject_00562220, /* published MetaObject slot */
        igInfo_Register,                           /* base class registrar */
        igInfo_GetPublishedMetaObject_00131c50,    /* base class MetaObject accessor */
        thunk_igAnimationDatabase_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationDatabase_className_004e3cc0,  /* class name */
        0x28,                                      /* instance size */
        igAnimationDatabase_GetVTable,             /* vtable getter */
        &igAnimationDatabase_InitFields,           /* field adder */
        0,                                         /* extra callback item */
        g_igAnimationDatabase_callbackList_0048d200  /* callback list */
    );
}
