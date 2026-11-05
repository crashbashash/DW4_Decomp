/* 0x00450f10 igFieldChangeView_Register: registers class igFieldChangeView with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char igFieldChangeView_GetVTable[];
extern char thunk_igFieldChangeView_GetMetaObject[];
extern char g_igFieldChangeView_callbackList_004d06f0[];
extern char s_igFieldChangeView_className_0051e520[];
extern char g_igFieldChangeView_metaObject_0058c550[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igFieldChangeView_InitFields();

void igFieldChangeView_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFieldChangeView_metaObject_0058c550, /* published MetaObject slot */
        igView_Register,                         /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20,  /* base class MetaObject accessor */
        thunk_igFieldChangeView_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igFieldChangeView_className_0051e520,  /* class name */
        0x14,                                    /* instance size */
        igFieldChangeView_GetVTable,             /* vtable getter */
        &igFieldChangeView_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        g_igFieldChangeView_callbackList_004d06f0  /* callback list */
    );
}
