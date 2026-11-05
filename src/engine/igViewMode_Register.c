/* 0x0045d010 igViewMode_Register: registers class igViewMode with the object system, derived from igView.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igView_Register[];
extern char igView_GetPublishedMetaObject_0044cb20[];
extern char igViewMode_GetVTable[];
extern char thunk_igViewMode_GetMetaObject[];
extern char s_igViewMode_className_0051f7f0[];
extern char g_igViewMode_metaObject_0058ccf8[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igViewMode_InitFields();

void igViewMode_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewMode_metaObject_0058ccf8,       /* published MetaObject slot */
        igView_Register,                        /* base class registrar */
        igView_GetPublishedMetaObject_0044cb20, /* base class MetaObject accessor */
        thunk_igViewMode_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igViewMode_className_0051f7f0,        /* class name */
        0x4C,                                   /* instance size */
        igViewMode_GetVTable,                   /* vtable getter */
        &igViewMode_InitFields,                 /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
