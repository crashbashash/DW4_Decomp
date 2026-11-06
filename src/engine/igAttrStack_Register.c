/* 0x001a5ba0 igAttrStack_Register: registers class igAttrStack with the object system, derived from igNonRefCountedObjectStack.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectStack_GetPublishedMetaObject[];
extern char igAttrStack_GetVTable[];
extern char thunk_igAttrStack_GetMetaObject[];
extern char igNonRefCountedObjectStack_Register[];
extern char g_igAttrStack_callbackList[];
extern char igAttrStack_className[];
extern char g_igAttrStack_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAttrStack_InitFields();

void igAttrStack_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrStack_metaObject,                          /* published MetaObject slot */
        igNonRefCountedObjectStack_Register,                        /* base class registrar */
        igNonRefCountedObjectStack_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAttrStack_GetMetaObject,                            /* own MetaObject accessor (stored at +0x54) */
        igAttrStack_className,                           /* class name */
        0x34,                                                       /* instance size */
        igAttrStack_GetVTable,                                      /* vtable getter */
        &igAttrStack_InitFields,                                    /* field adder */
        0,                                                          /* extra callback item */
        g_igAttrStack_callbackList                         /* callback list */
    );
}
