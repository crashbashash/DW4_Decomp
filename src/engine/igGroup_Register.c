/* 0x0019f340 igGroup_Register: registers class igGroup with the object system, derived from igNode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNode_Register[];
extern char igNode_GetPublishedMetaObject_0019dd70[];
extern char igGroup_GetVTable[];
extern char thunk_igGroup_GetMetaObject[];
extern char g_igGroup_callbackList_0048bfd8[];
extern char s_igGroup_className_004e2690[];
extern char g_igGroup_metaObject_005619f8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igGroup_InitFields();

void igGroup_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGroup_metaObject_005619f8,          /* published MetaObject slot */
        igNode_Register,                        /* base class registrar */
        igNode_GetPublishedMetaObject_0019dd70, /* base class MetaObject accessor */
        thunk_igGroup_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igGroup_className_004e2690,           /* class name */
        0x20,                                   /* instance size */
        igGroup_GetVTable,                      /* vtable getter */
        &igGroup_InitFields,                    /* field adder */
        0,                                      /* extra callback item */
        g_igGroup_callbackList_0048bfd8         /* callback list */
    );
}
