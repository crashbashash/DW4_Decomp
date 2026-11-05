/* 0x0019c7c0 igOverrideAttrSet_Register: registers class igOverrideAttrSet with the object system, derived from igAttrSet.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAttrSet_GetPublishedMetaObject_0019c490[];
extern char igOverrideAttrSet_GetVTable[];
extern char thunk_igOverrideAttrSet_GetMetaObject[];
extern char igAttrSet_Register[];
extern char s_igOverrideAttrSet_className_004e2340[];
extern char g_igOverrideAttrSet_metaObject_00561818[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igOverrideAttrSet_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOverrideAttrSet_metaObject_00561818,   /* published MetaObject slot */
        igAttrSet_Register,                        /* base class registrar */
        igAttrSet_GetPublishedMetaObject_0019c490, /* base class MetaObject accessor */
        thunk_igOverrideAttrSet_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igOverrideAttrSet_className_004e2340,    /* class name */
        0x28,                                      /* instance size */
        igOverrideAttrSet_GetVTable,               /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}
