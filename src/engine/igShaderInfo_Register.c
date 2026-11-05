/* 0x00198e40 igShaderInfo_Register: registers class igShaderInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject_00131c50[];
extern char igShaderInfo_GetVTable[];
extern char thunk_igShaderInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igShaderInfo_callbackList_0048b618[];
extern char s_igShaderInfo_className_004e1b58[];
extern char g_igShaderInfo_metaObject_00561500[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
extern int thunk_FUN_001d8ab0[4];
int igShaderInfo_InitFields();

void igShaderInfo_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igShaderInfo_metaObject_00561500,     /* published MetaObject slot */
        igInfo_Register,                        /* base class registrar */
        igInfo_GetPublishedMetaObject_00131c50, /* base class MetaObject accessor */
        thunk_igShaderInfo_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igShaderInfo_className_004e1b58,      /* class name */
        0x18,                                   /* instance size */
        igShaderInfo_GetVTable,                 /* vtable getter */
        &igShaderInfo_InitFields,               /* field adder */
        thunk_FUN_001d8ab0,                     /* extra callback item */
        g_igShaderInfo_callbackList_0048b618    /* callback list */
    );
}
