/* 0x002c49e0 igFloatArrayMetaField_Register: registers class igFloatArrayMetaField with the object system, derived from igFloatMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igFloatMetaField_Register[];
extern char igFloatArrayMetaField_GetVTable[];
extern char thunk_igFloatArrayMetaField_GetMetaObject[];
extern char igFloatMetaField_GetPublishedMetaObject_002c4a70[];
extern char g_igFloatArrayMetaField_callbackList_004c0ac0[];
extern char s_igFloatArrayMetaField_className_004f7600[];
extern char g_igFloatArrayMetaField_metaObject_00586388[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igFloatArrayMetaField_InitFields();

void igFloatArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFloatArrayMetaField_metaObject_00586388,      /* published MetaObject slot */
        igFloatMetaField_Register,                        /* base class registrar */
        igFloatMetaField_GetPublishedMetaObject_002c4a70, /* base class MetaObject accessor */
        thunk_igFloatArrayMetaField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igFloatArrayMetaField_className_004f7600,       /* class name */
        0x38,                                             /* instance size */
        igFloatArrayMetaField_GetVTable,                  /* vtable getter */
        &igFloatArrayMetaField_InitFields,                /* field adder */
        0,                                                /* extra callback item */
        g_igFloatArrayMetaField_callbackList_004c0ac0     /* callback list */
    );
}
