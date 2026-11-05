/* 0x0019cf20 igNode_Register: registers class igNode with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igNode_GetVTable[];
extern char thunk_igNode_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igNode_callbackList_0048bc80[];
extern char s_igNode_className_004e2398[];
extern char g_igNode_metaObject_00561838[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igNode_InitFields();

void igNode_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igNode_metaObject_00561838,                  /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igNode_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        s_igNode_className_004e2398,                   /* class name */
        0x1C,                                          /* instance size */
        igNode_GetVTable,                              /* vtable getter */
        &igNode_InitFields,                            /* field adder */
        0,                                             /* extra callback item */
        g_igNode_callbackList_0048bc80                 /* callback list */
    );
}
