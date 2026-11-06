/* 0x00239c90 igCollisionGroup_Register: registers class igCollisionGroup with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char igCollisionGroup_GetVTable[];
extern char thunk_igCollisionGroup_GetMetaObject[];
extern char g_igCollisionGroup_callbackList[];
extern char igCollisionGroup_className[];
extern char g_igCollisionGroup_metaObject[];
int GpFlag_SetOnce_002393f0();
int igMetaObject_RegisterClass();
int igCollisionGroup_InitFields();

void igCollisionGroup_Register(void) {
    GpFlag_SetOnce_002393f0();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCollisionGroup_metaObject,  /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCollisionGroup_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igCollisionGroup_className,   /* class name */
        0x60,                                    /* instance size */
        igCollisionGroup_GetVTable,              /* vtable getter */
        &igCollisionGroup_InitFields,            /* field adder */
        0,                                       /* extra callback item */
        g_igCollisionGroup_callbackList  /* callback list */
    );
}
