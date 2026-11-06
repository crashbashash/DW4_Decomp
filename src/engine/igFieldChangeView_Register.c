/* 0x00450f10 igFieldChangeView_Register: registers class igFieldChangeView with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igFieldChangeView_GetVTable[];
extern char thunk_igFieldChangeView_GetMetaObject[];
extern char g_igFieldChangeView_callbackList[];
extern char igFieldChangeView_className[];
extern char g_igFieldChangeView_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igFieldChangeView_InitFields();

void igFieldChangeView_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFieldChangeView_metaObject, /* published MetaObject slot */
        igView_Register,                         /* base class registrar */
        igView_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igFieldChangeView_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igFieldChangeView_className,  /* class name */
        0x14,                                    /* instance size */
        igFieldChangeView_GetVTable,             /* vtable getter */
        &igFieldChangeView_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        g_igFieldChangeView_callbackList  /* callback list */
    );
}
