/* 0x001511b0 igPsx2VisualContext_Register: registers class igPsx2VisualContext with the object system, derived from igVisualContext.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualContext_Register[];
extern char thunk_igPsx2VisualContext_GetMetaObject[];
extern char igPsx2VisualContext_GetVTable[];
extern char igVisualContext_GetPublishedMetaObject_00151230[];
extern char g_igPsx2VisualContext_callbackList_00489250[];
extern char s_igPsx2VisualContext_className_004dd270[];
extern char g_igPsx2VisualContext_metaObject_0055ff88[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2VisualContext_InitFields();

void igPsx2VisualContext_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2VisualContext_metaObject_0055ff88,       /* published MetaObject slot */
        igVisualContext_Register,                        /* base class registrar */
        igVisualContext_GetPublishedMetaObject_00151230, /* base class MetaObject accessor */
        thunk_igPsx2VisualContext_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2VisualContext_className_004dd270,        /* class name */
        0x618,                                           /* instance size */
        igPsx2VisualContext_GetVTable,                   /* vtable getter */
        &igPsx2VisualContext_InitFields,                 /* field adder */
        0,                                               /* extra callback item */
        g_igPsx2VisualContext_callbackList_00489250      /* callback list */
    );
}
