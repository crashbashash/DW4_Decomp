/* 0x00138170 igDisplayListAttr_Register: registers class igDisplayListAttr with the object system, derived from igAttr.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAttr_GetPublishedMetaObject[];
extern char igDisplayListAttr_GetVTable[];
extern char thunk_igDisplayListAttr_GetMetaObject[];
extern char igAttr_Register[];
extern char g_igDisplayListAttr_callbackList[];
extern char igDisplayListAttr_className[];
extern char g_igDisplayListAttr_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igDisplayListAttr_InitFields();

void igDisplayListAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDisplayListAttr_metaObject, /* published MetaObject slot */
        igAttr_Register,                         /* base class registrar */
        igAttr_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igDisplayListAttr_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igDisplayListAttr_className,  /* class name */
        0x10,                                    /* instance size */
        igDisplayListAttr_GetVTable,             /* vtable getter */
        &igDisplayListAttr_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        g_igDisplayListAttr_callbackList  /* callback list */
    );
}
