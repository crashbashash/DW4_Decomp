/* 0x00239ef0 igCollisionGridHelper_Register: registers class igCollisionGridHelper with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCollisionGridHelper_GetVTable[];
extern char thunk_igCollisionGridHelper_GetMetaObject[];
extern char igObject_Register[];
extern char g_igCollisionGridHelper_callbackList_00498440[];
extern char s_igCollisionGridHelper_className_004ea000[];
extern char g_igCollisionGridHelper_metaObject_0056dd28[];
int GpFlag_SetOnce_002393f0();
int igMetaObject_RegisterClass();
int igCollisionGridHelper_InitFields();

void igCollisionGridHelper_Register(void) {
    GpFlag_SetOnce_002393f0();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCollisionGridHelper_metaObject_0056dd28, /* published MetaObject slot */
        igObject_Register,                           /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,       /* base class MetaObject accessor */
        thunk_igCollisionGridHelper_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCollisionGridHelper_className_004ea000,  /* class name */
        0x10,                                        /* instance size */
        igCollisionGridHelper_GetVTable,             /* vtable getter */
        &igCollisionGridHelper_InitFields,           /* field adder */
        0,                                           /* extra callback item */
        g_igCollisionGridHelper_callbackList_00498440  /* callback list */
    );
}
