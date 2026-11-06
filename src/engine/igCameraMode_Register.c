/* 0x0045cdd0 igCameraMode_Register: registers class igCameraMode with the object system, derived from igViewMode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igViewMode_GetPublishedMetaObject[];
extern char igCameraMode_GetVTable[];
extern char thunk_igCameraMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char g_igCameraMode_callbackList[];
extern char igCameraMode_className[];
extern char g_igCameraMode_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igCameraMode_InitFields();

void igCameraMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCameraMode_metaObject,         /* published MetaObject slot */
        igViewMode_Register,                        /* base class registrar */
        igViewMode_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igCameraMode_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        igCameraMode_className,          /* class name */
        0x54,                                       /* instance size */
        igCameraMode_GetVTable,                     /* vtable getter */
        &igCameraMode_InitFields,                   /* field adder */
        0,                                          /* extra callback item */
        g_igCameraMode_callbackList        /* callback list */
    );
}
