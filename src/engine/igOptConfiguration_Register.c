/* 0x00225eb0 igOptConfiguration_Register: registers class igOptConfiguration with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igOptConfiguration_GetVTable[];
extern char thunk_igOptConfiguration_GetMetaObject[];
extern char igObject_Register[];
extern char s_igOptConfiguration_className_004e7a40[];
extern char g_igOptConfiguration_metaObject_0056d888[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igOptConfiguration_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOptConfiguration_metaObject_0056d888, /* published MetaObject slot */
        igObject_Register,                        /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,    /* base class MetaObject accessor */
        thunk_igOptConfiguration_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igOptConfiguration_className_004e7a40,  /* class name */
        8,                                        /* instance size */
        igOptConfiguration_GetVTable,             /* vtable getter */
        0,                                        /* field adder */
        0,                                        /* extra callback item */
        0                                         /* callback list */
    );
}
