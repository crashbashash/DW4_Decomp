/* 0x0019fc10 igGeometry_Register: registers class igGeometry with the object system, derived from igAttrSet.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igAttrSet_GetPublishedMetaObject_0019c490[];
extern char igGeometry_GetVTable[];
extern char thunk_igGeometry_GetMetaObject[];
extern char igAttrSet_Register[];
extern char g_igGeometry_callbackList_0048c058[];
extern char s_igGeometry_className_004e26f0[];
extern char g_igGeometry_metaObject_00561a38[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
/* Code in the gap after this function; the 9th and 10th registration
 * arguments, as igXxx_InitFields and the thunk are for sibling classes. */
extern int igGeometry_InitFields_0019fca0[4];
extern int igGeometry_PostInit_0019fdd0[4];
void igGeometry_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGeometry_metaObject_00561a38,          /* published MetaObject slot */
        igAttrSet_Register,                        /* base class registrar */
        igAttrSet_GetPublishedMetaObject_0019c490, /* base class MetaObject accessor */
        thunk_igGeometry_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igGeometry_className_004e26f0,           /* class name */
        0x2C,                                      /* instance size */
        igGeometry_GetVTable,                      /* vtable getter */
        &igGeometry_InitFields_0019fca0[0],        /* field adder */
        &igGeometry_PostInit_0019fdd0[0],          /* extra callback item */
        g_igGeometry_callbackList_0048c058         /* callback list */
    );
}
