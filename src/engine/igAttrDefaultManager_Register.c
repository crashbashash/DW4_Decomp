/* 0x0013ab60 igAttrDefaultManager_Register: registers class igAttrDefaultManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igAttrDefaultManager_GetMetaObject[];
extern char igObject_Register[];
extern char s_igAttrDefaultManager_className_004d5d10[];
extern char g_igAttrDefaultManager_metaObject_0055f448[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igAttrDefaultManager_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        1,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrDefaultManager_metaObject_0055f448, /* published MetaObject slot */
        igObject_Register,                          /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,      /* base class MetaObject accessor */
        thunk_igAttrDefaultManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igAttrDefaultManager_className_004d5d10,  /* class name */
        8,                                          /* instance size */
        0,                                          /* vtable getter */
        0,                                          /* field adder */
        0,                                          /* extra callback item */
        0                                           /* callback list */
    );
}
