/* 0x001a8e00 igAnimationBinding_Register: registers class igAnimationBinding with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationBinding_GetVTable[];
extern char thunk_igAnimationBinding_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationBinding_callbackList_0048d460[];
extern char s_igAnimationBinding_className_004e4080[];
extern char g_igAnimationBinding_metaObject_00562338[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimationBinding_InitFields();

void igAnimationBinding_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimationBinding_metaObject_00562338, /* published MetaObject slot */
        igObject_Register,                        /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,    /* base class MetaObject accessor */
        thunk_igAnimationBinding_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAnimationBinding_className_004e4080,  /* class name */
        0x1C,                                     /* instance size */
        igAnimationBinding_GetVTable,             /* vtable getter */
        &igAnimationBinding_InitFields,           /* field adder */
        0,                                        /* extra callback item */
        g_igAnimationBinding_callbackList_0048d460  /* callback list */
    );
}
