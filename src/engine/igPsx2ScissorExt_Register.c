/* 0x00153010 igPsx2ScissorExt_Register: registers class igPsx2ScissorExt with the object system, derived from igScissorExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igScissorExt_Register[];
extern char thunk_igPsx2ScissorExt_GetMetaObject[];
extern char igPsx2ScissorExt_GetVTable[];
extern char igScissorExt_GetPublishedMetaObject_00153090[];
extern char g_igPsx2ScissorExt_callbackList_00489e00[];
extern char s_igPsx2ScissorExt_className_004de040[];
extern char g_igPsx2ScissorExt_metaObject_005604f8[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2ScissorExt_InitFields();

void igPsx2ScissorExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2ScissorExt_metaObject_005604f8,       /* published MetaObject slot */
        igScissorExt_Register,                        /* base class registrar */
        igScissorExt_GetPublishedMetaObject_00153090, /* base class MetaObject accessor */
        thunk_igPsx2ScissorExt_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2ScissorExt_className_004de040,        /* class name */
        0x2C,                                         /* instance size */
        igPsx2ScissorExt_GetVTable,                   /* vtable getter */
        &igPsx2ScissorExt_InitFields,                 /* field adder */
        0,                                            /* extra callback item */
        g_igPsx2ScissorExt_callbackList_00489e00      /* callback list */
    );
}
