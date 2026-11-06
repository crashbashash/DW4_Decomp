/* 0x00154050 igPsx2DisableExt_Register: registers class igPsx2DisableExt with the object system, derived from igDisableExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDisableExt_Register[];
extern char thunk_igPsx2DisableExt_GetMetaObject[];
extern char igPsx2DisableExt_GetVTable[];
extern char igDisableExt_GetPublishedMetaObject[];
extern char g_igPsx2DisableExt_callbackList[];
extern char igPsx2DisableExt_className[];
extern char g_igPsx2DisableExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2DisableExt_InitFields();

void igPsx2DisableExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2DisableExt_metaObject,       /* published MetaObject slot */
        igDisableExt_Register,                        /* base class registrar */
        igDisableExt_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2DisableExt_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2DisableExt_className,        /* class name */
        0x18,                                         /* instance size */
        igPsx2DisableExt_GetVTable,                   /* vtable getter */
        &igPsx2DisableExt_InitFields,                 /* field adder */
        0,                                            /* extra callback item */
        g_igPsx2DisableExt_callbackList      /* callback list */
    );
}
