/* 0x001960d0 igTransformStack_Register: registers class igTransformStack with the object system, derived from igNonRefCountedObjectStack.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNonRefCountedObjectStack_GetPublishedMetaObject_001462f0[];
extern char igTransformStack_GetVTable[];
extern char thunk_igTransformStack_GetMetaObject[];
extern char igNonRefCountedObjectStack_Register[];
extern char g_igTransformStack_callbackList_0048b170[];
extern char s_igTransformStack_className_004e1580[];
extern char g_igTransformStack_metaObject_005612a8[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igTransformStack_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransformStack_metaObject_005612a8,                     /* published MetaObject slot */
        igNonRefCountedObjectStack_Register,                        /* base class registrar */
        igNonRefCountedObjectStack_GetPublishedMetaObject_001462f0, /* base class MetaObject accessor */
        thunk_igTransformStack_GetMetaObject,                       /* own MetaObject accessor (stored at +0x54) */
        s_igTransformStack_className_004e1580,                      /* class name */
        0x14,                                                       /* instance size */
        igTransformStack_GetVTable,                                 /* vtable getter */
        0,                                                          /* field adder */
        0,                                                          /* extra callback item */
        g_igTransformStack_callbackList_0048b170                    /* callback list */
    );
}
