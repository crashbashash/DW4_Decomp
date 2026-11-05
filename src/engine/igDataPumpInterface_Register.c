/* 0x001e55e0 igDataPumpInterface_Register: registers class igDataPumpInterface with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igDataPumpInterface_GetMetaObject[];
extern char igObject_Register[];
extern char s_igDataPumpInterface_className_004e49f0[];
extern char g_igDataPumpInterface_metaObject_00562c08[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();

void igDataPumpInterface_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        1,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDataPumpInterface_metaObject_00562c08, /* published MetaObject slot */
        igObject_Register,                         /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,     /* base class MetaObject accessor */
        thunk_igDataPumpInterface_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igDataPumpInterface_className_004e49f0,  /* class name */
        8,                                         /* instance size */
        0,                                         /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}
