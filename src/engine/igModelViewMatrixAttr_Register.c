/* 0x001357f0 igModelViewMatrixAttr_Register: registers class igModelViewMatrixAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igModelViewMatrixAttr_GetVTable[];
extern char thunk_igModelViewMatrixAttr_GetMetaObject[];
void FUN_00135980(void);  /* code at 0x135980, passed by address (was DAT_135980; docs/engine/function-inventory.md) */
extern char s_igModelViewMatrixAttr_className_004d5390[];
extern char g_igModelViewMatrixAttr_metaObject_0055efe8[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
int igModelViewMatrixAttr_InitFields();

void igModelViewMatrixAttr_Register(void) {
    GpFlag_SetOnce_00130000();  /* set-once latch run before every registration of this family (asm/GpFlag_SetOnce_00130000.s) */
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igModelViewMatrixAttr_metaObject_0055efe8,       /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igModelViewMatrixAttr_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igModelViewMatrixAttr_className_004d5390,        /* class name */
        0x4C,                                              /* instance size (the reflected struct is shorter: igMatrix44f is reflected as one int) */
        igModelViewMatrixAttr_GetVTable,                   /* vtable getter */
        &igModelViewMatrixAttr_InitFields,                 /* field adder */
        FUN_00135980,                                      /* static-initializer callback item (appended on fresh configuration) */
        0                                                  /* 0-terminated dependency-callback list */
    );
}
