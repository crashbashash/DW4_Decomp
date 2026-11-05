/* 0x0045c690 igRotateMode_Register: registers class igRotateMode with the object system, derived from igViewMode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igViewMode_GetPublishedMetaObject_00368c80[];
extern char igRotateMode_GetVTable[];
extern char thunk_igRotateMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char s_igRotateMode_className_0051f640[];
extern char g_igRotateMode_metaObject_0058cbf8[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igRotateMode_InitFields();

void igRotateMode_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRotateMode_metaObject_0058cbf8,         /* published MetaObject slot */
        igViewMode_Register,                        /* base class registrar */
        igViewMode_GetPublishedMetaObject_00368c80, /* base class MetaObject accessor */
        thunk_igRotateMode_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igRotateMode_className_0051f640,          /* class name */
        0x94,                                       /* instance size */
        igRotateMode_GetVTable,                     /* vtable getter */
        &igRotateMode_InitFields,                   /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
