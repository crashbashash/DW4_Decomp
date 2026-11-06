/* 0x00186f80 igVectorBlending_Register: registers class igVectorBlending with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igVectorBlending_GetVTable[];
extern char thunk_igVectorBlending_GetMetaObject_00186ff0[];
void FUN_00187000(void);  /* code at 0x187000, passed by address (was DAT_187000; docs/engine/function-inventory.md) */
extern char igObject_Register[];
extern char igVectorBlending_className[];
extern char g_igVectorBlending_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVectorBlending_Register(void) {
    FUN_00186a40();  /* set-once guard (gp-relative byte flag) that chains to sibling registrars (asm/FUN_00186a40.s) */
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVectorBlending_metaObject,        /* published MetaObject slot */
        igObject_Register,                             /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,         /* base class MetaObject accessor */
        thunk_igVectorBlending_GetMetaObject_00186ff0, /* own MetaObject accessor (stored at +0x54) */
        igVectorBlending_className,         /* class name */
        8,                                             /* instance size */
        igVectorBlending_GetVTable,                    /* vtable getter */
        0,                                             /* field adder */
        FUN_00187000,                                  /* static-initializer callback item (appended on fresh configuration) */
        0                                              /* 0-terminated dependency-callback list */
    );
}
