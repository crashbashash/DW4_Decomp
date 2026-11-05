/* 0x001a5ba0 igAttrStack_Register: registers class igAttrStack with the object system, derived from igNonRefCountedObjectStack.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectStack_GetPublishedMetaObject_001462f0[];
extern char igAttrStack_GetVTable[];
extern char thunk_igAttrStack_GetMetaObject[];
extern char igNonRefCountedObjectStack_Register[];
extern char g_igAttrStack_callbackList_0048cd80[];
extern char s_igAttrStack_className_004e3650[];
extern char g_igAttrStack_metaObject_00562030[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAttrStack_InitFields();

void igAttrStack_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrStack_metaObject_00562030,                          /* published MetaObject slot */
        igNonRefCountedObjectStack_Register,                        /* base class registrar */
        igNonRefCountedObjectStack_GetPublishedMetaObject_001462f0, /* base class MetaObject accessor */
        thunk_igAttrStack_GetMetaObject,                            /* own MetaObject accessor (stored at +0x54) */
        s_igAttrStack_className_004e3650,                           /* class name */
        0x34,                                                       /* instance size */
        igAttrStack_GetVTable,                                      /* vtable getter */
        &igAttrStack_InitFields,                                    /* field adder */
        0,                                                          /* extra callback item */
        g_igAttrStack_callbackList_0048cd80                         /* callback list */
    );
}
