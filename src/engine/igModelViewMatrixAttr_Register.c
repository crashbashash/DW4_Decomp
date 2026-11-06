/* 0x001357f0 igModelViewMatrixAttr_Register: registers class igModelViewMatrixAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igModelViewMatrixAttr_GetVTable[];
extern char thunk_igModelViewMatrixAttr_GetMetaObject[];
void FUN_00135980(void);
extern char igModelViewMatrixAttr_className[];
extern char g_igModelViewMatrixAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igModelViewMatrixAttr_InitFields();

void igModelViewMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();  /* set-once latch run before every registration of this family (asm/AttrsLibrary_MarkRegistered.s) */
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igModelViewMatrixAttr_metaObject,       /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igModelViewMatrixAttr_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igModelViewMatrixAttr_className,        /* class name */
        0x4C,                                              /* instance size (the reflected struct is shorter: igMatrix44f is reflected as one int) */
        igModelViewMatrixAttr_GetVTable,                   /* vtable getter */
        &igModelViewMatrixAttr_InitFields,                 /* field adder */
        FUN_00135980,                                      /* static-initializer callback item (appended on fresh configuration) */
        0                                                  /* 0-terminated dependency-callback list */
    );
}
