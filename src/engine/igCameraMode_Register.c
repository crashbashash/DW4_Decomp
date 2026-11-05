/* 0x0045cdd0 igCameraMode_Register: registers class igCameraMode with the object system, derived from igViewMode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igViewMode_GetPublishedMetaObject_00368c80[];
extern char igCameraMode_GetVTable[];
extern char thunk_igCameraMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char g_igCameraMode_callbackList_004d1650[];
extern char s_igCameraMode_className_0051f7c8[];
extern char g_igCameraMode_metaObject_0058cce0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igCameraMode_InitFields();

void igCameraMode_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCameraMode_metaObject_0058cce0,         /* published MetaObject slot */
        igViewMode_Register,                        /* base class registrar */
        igViewMode_GetPublishedMetaObject_00368c80, /* base class MetaObject accessor */
        thunk_igCameraMode_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igCameraMode_className_0051f7c8,          /* class name */
        0x54,                                       /* instance size */
        igCameraMode_GetVTable,                     /* vtable getter */
        &igCameraMode_InitFields,                   /* field adder */
        0,                                          /* extra callback item */
        g_igCameraMode_callbackList_004d1650        /* callback list */
    );
}
