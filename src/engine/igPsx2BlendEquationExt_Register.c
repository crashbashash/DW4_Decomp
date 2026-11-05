/* 0x00154720 igPsx2BlendEquationExt_Register: registers class igPsx2BlendEquationExt with the object system, derived from igBlendEquationExt.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igBlendEquationExt_Register[];
extern char thunk_igPsx2BlendEquationExt_GetMetaObject[];
extern char igPsx2BlendEquationExt_GetVTable[];
extern char igBlendEquationExt_GetPublishedMetaObject_001547a0[];
extern char g_igPsx2BlendEquationExt_callbackList_0048a0f8[];
extern char s_igPsx2BlendEquationExt_className_004de680[];
extern char g_igPsx2BlendEquationExt_metaObject_00560628[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2BlendEquationExt_InitFields();

void igPsx2BlendEquationExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2BlendEquationExt_metaObject_00560628,       /* published MetaObject slot */
        igBlendEquationExt_Register,                        /* base class registrar */
        igBlendEquationExt_GetPublishedMetaObject_001547a0, /* base class MetaObject accessor */
        thunk_igPsx2BlendEquationExt_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2BlendEquationExt_className_004de680,        /* class name */
        0x30,                                               /* instance size */
        igPsx2BlendEquationExt_GetVTable,                   /* vtable getter */
        &igPsx2BlendEquationExt_InitFields,                 /* field adder */
        0,                                                  /* extra callback item */
        g_igPsx2BlendEquationExt_callbackList_0048a0f8      /* callback list */
    );
}
