/* 0x0013a910 igAttrPool_Register: registers class igAttrPool with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAttrPool_GetVTable[];
extern char thunk_igAttrPool_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAttrPool_callbackList[];
extern char igAttrPool_className[];
extern char g_igAttrPool_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
void FUN_0013aa90(void);  /* code at 0x13aa90, passed by address (was DAT_13aa90; docs/engine/function-inventory.md) */
int igAttrPool_InitFields();

void igAttrPool_Register(void) {
    GpFlag_SetOnce_00130000();  /* set-once latch: writes a gp-relative byte flag only if it is clear (asm/GpFlag_SetOnce_00130000.s) */
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAttrPool_metaObject,      /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igAttrPool_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igAttrPool_className,       /* class name */
        0x14,                                  /* instance size */
        igAttrPool_GetVTable,                  /* vtable getter */
        &igAttrPool_InitFields,                /* field adder */
        FUN_0013aa90,                      /* static-initializer callback item (appended on fresh configuration) */
        g_igAttrPool_callbackList     /* 0-terminated dependency-callback list */
    );
}
