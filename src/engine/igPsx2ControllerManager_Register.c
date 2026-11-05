/* 0x00146ef0 igPsx2ControllerManager_Register: registers class igPsx2ControllerManager with the object system, derived from igControllerManager.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igControllerManager_Register[];
extern char thunk_igPsx2ControllerManager_GetMetaObject[];
extern char igPsx2ControllerManager_GetVTable[];
extern char igControllerManager_GetPublishedMetaObject_00146f60[];
extern char s_igPsx2ControllerManager_className_004d6d00[];
extern char g_igPsx2ControllerManager_metaObject_0055f738[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();
int igPsx2ControllerManager_InitFields();

void igPsx2ControllerManager_Register(void) {
    GpFlag_SetOnce_00145ce0();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2ControllerManager_metaObject_0055f738,       /* published MetaObject slot */
        igControllerManager_Register,                        /* base class registrar */
        igControllerManager_GetPublishedMetaObject_00146f60, /* base class MetaObject accessor */
        thunk_igPsx2ControllerManager_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2ControllerManager_className_004d6d00,        /* class name */
        0x14,                                                /* instance size */
        igPsx2ControllerManager_GetVTable,                   /* vtable getter */
        &igPsx2ControllerManager_InitFields,                 /* field adder */
        0,                                                   /* extra callback item */
        0                                                    /* callback list */
    );
}
