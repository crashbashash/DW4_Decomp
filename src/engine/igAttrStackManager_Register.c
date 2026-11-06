/* 0x001a5650 igAttrStackManager_Register: registers class igAttrStackManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAttrStackManager_GetVTable[];
extern char thunk_igAttrStackManager_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAttrStackManager_callbackList[];
extern char igAttrStackManager_className[];
extern char g_igAttrStackManager_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
void FUN_001a58e0(void);
int igAttrStackManager_InitFields();

void igAttrStackManager_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* shared set-once latch run before every registration of this family (asm/SceneGraphLibrary_MarkRegistered.s) */
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrStackManager_metaObject, /* published MetaObject slot */
        igObject_Register,                        /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,    /* base class MetaObject accessor */
        thunk_igAttrStackManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igAttrStackManager_className,  /* class name */
        0x4C,                                     /* instance size */
        igAttrStackManager_GetVTable,             /* vtable getter */
        &igAttrStackManager_InitFields,           /* field adder */
        FUN_001a58e0,                         /* static-initializer callback item (appended on fresh configuration) */
        g_igAttrStackManager_callbackList  /* 0-terminated dependency-callback list */
    );
}
