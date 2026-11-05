/* 0x0014e4b0 igTrackedElementMetaField_Register: registers class igTrackedElementMetaField with the object system, derived from igCompoundMetaField.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igTrackedElementMetaField_GetVTable[];
extern char thunk_igTrackedElementMetaField_GetMetaObject[];
extern char igCompoundMetaField_GetPublishedMetaObject_0014e530[];
extern char igCompoundMetaField_Register[];
extern char g_igTrackedElementMetaField_callbackList_00489008[];
extern char s_igTrackedElementMetaField_className_004dcc10[];
extern char g_igTrackedElementMetaField_metaObject_0055fe38[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igTrackedElementMetaField_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTrackedElementMetaField_metaObject_0055fe38,     /* published MetaObject slot */
        igCompoundMetaField_Register,                        /* base class registrar */
        igCompoundMetaField_GetPublishedMetaObject_0014e530, /* base class MetaObject accessor */
        thunk_igTrackedElementMetaField_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igTrackedElementMetaField_className_004dcc10,      /* class name */
        0x38,                                                /* instance size */
        igTrackedElementMetaField_GetVTable,                 /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        g_igTrackedElementMetaField_callbackList_00489008    /* callback list */
    );
}
