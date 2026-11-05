/* 0x001aaa60 igActor_Register: registers class igActor with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igGroup_Register[];
extern char igActor_GetVTable[];
extern char thunk_igActor_GetMetaObject[];
extern char g_igActor_callbackList_0048d750[];
extern char s_igActor_className_004e4358[];
extern char g_igActor_metaObject_00562488[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igActor_InitFields();

void igActor_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igActor_metaObject_00562488,           /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0, /* base class MetaObject accessor */
        thunk_igActor_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igActor_className_004e4358,            /* class name */
        0x100,                                   /* instance size */
        igActor_GetVTable,                       /* vtable getter */
        &igActor_InitFields,                     /* field adder */
        0,                                       /* extra callback item */
        g_igActor_callbackList_0048d750          /* callback list */
    );
}
