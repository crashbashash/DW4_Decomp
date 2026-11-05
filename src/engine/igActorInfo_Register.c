/* 0x001aa420 igActorInfo_Register: registers class igActorInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject_00131c50[];
extern char igActorInfo_GetVTable[];
extern char thunk_igActorInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igActorInfo_callbackList_0048d6b0[];
extern char s_igActorInfo_className_004e4308[];
extern char g_igActorInfo_metaObject_00562450[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igActorInfo_InitFields();

void igActorInfo_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igActorInfo_metaObject_00562450,      /* published MetaObject slot */
        igInfo_Register,                        /* base class registrar */
        igInfo_GetPublishedMetaObject_00131c50, /* base class MetaObject accessor */
        thunk_igActorInfo_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igActorInfo_className_004e4308,       /* class name */
        0x28,                                   /* instance size */
        igActorInfo_GetVTable,                  /* vtable getter */
        &igActorInfo_InitFields,                /* field adder */
        0,                                      /* extra callback item */
        g_igActorInfo_callbackList_0048d6b0     /* callback list */
    );
}
