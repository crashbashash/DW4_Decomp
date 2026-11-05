/* 0x001a5ea0 igAttrSet_Register: registers class igAttrSet with the object system, derived from igGroup.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igGroup_GetPublishedMetaObject_001943a0[];
extern char igGroup_Register[];
extern char igAttrSet_GetVTable[];
extern char thunk_igAttrSet_GetMetaObject[];
extern char g_igAttrSet_callbackList_0048ce10[];
extern char s_igAttrSet_className_004e3738[];
extern char g_igAttrSet_metaObject_00562078[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAttrSet_InitFields();

void igAttrSet_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrSet_metaObject_00562078,         /* published MetaObject slot */
        igGroup_Register,                        /* base class registrar */
        igGroup_GetPublishedMetaObject_001943a0, /* base class MetaObject accessor */
        thunk_igAttrSet_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igAttrSet_className_004e3738,          /* class name */
        0x28,                                    /* instance size */
        igAttrSet_GetVTable,                     /* vtable getter */
        &igAttrSet_InitFields,                   /* field adder */
        0,                                       /* extra callback item */
        g_igAttrSet_callbackList_0048ce10        /* callback list */
    );
}
