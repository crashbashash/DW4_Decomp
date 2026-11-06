/* 0x00239920 igCollisionInfo_Register: registers class igCollisionInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject[];
extern char igCollisionInfo_GetVTable[];
extern char thunk_igCollisionInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igCollisionInfo_callbackList[];
extern char igCollisionInfo_className[];
extern char g_igCollisionInfo_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCollisionInfo_InitFields();

void igCollisionInfo_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCollisionInfo_metaObject,  /* published MetaObject slot */
        igInfo_Register,                        /* base class registrar */
        igInfo_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCollisionInfo_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igCollisionInfo_className,   /* class name */
        0x18,                                   /* instance size */
        igCollisionInfo_GetVTable,              /* vtable getter */
        &igCollisionInfo_InitFields,            /* field adder */
        0,                                      /* extra callback item */
        g_igCollisionInfo_callbackList  /* callback list */
    );
}
