/* 0x00239920 igCollisionInfo_Register: registers class igCollisionInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject_00131c50[];
extern char igCollisionInfo_GetVTable[];
extern char thunk_igCollisionInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igCollisionInfo_callbackList_00498380[];
extern char s_igCollisionInfo_className_004e9f30[];
extern char g_igCollisionInfo_metaObject_0056dcc8[];
int GpFlag_SetOnce_002393f0();
int igMetaObject_RegisterClass();
int igCollisionInfo_InitFields();

void igCollisionInfo_Register(void) {
    GpFlag_SetOnce_002393f0();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCollisionInfo_metaObject_0056dcc8,  /* published MetaObject slot */
        igInfo_Register,                        /* base class registrar */
        igInfo_GetPublishedMetaObject_00131c50, /* base class MetaObject accessor */
        thunk_igCollisionInfo_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igCollisionInfo_className_004e9f30,   /* class name */
        0x18,                                   /* instance size */
        igCollisionInfo_GetVTable,              /* vtable getter */
        &igCollisionInfo_InitFields,            /* field adder */
        0,                                      /* extra callback item */
        g_igCollisionInfo_callbackList_00498380  /* callback list */
    );
}
