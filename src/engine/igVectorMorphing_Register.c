/* 0x00186e50 igVectorMorphing_Register: registers class igVectorMorphing with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igVectorMorphing_GetVTable[];
extern char thunk_igVectorMorphing_GetMetaObject_00186ec0[];
void FUN_00186ed0(void);
extern char igObject_Register[];
extern char igVectorMorphing_className[];
extern char g_igVectorMorphing_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVectorMorphing_Register(void) {
    FUN_00186a40();  /* set-once guard (gp-relative byte flag) that chains to sibling registrars (asm/FUN_00186a40.s) */
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVectorMorphing_metaObject,        /* published MetaObject slot */
        igObject_Register,                             /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,         /* base class MetaObject accessor */
        thunk_igVectorMorphing_GetMetaObject_00186ec0, /* own MetaObject accessor (stored at +0x54) */
        igVectorMorphing_className,         /* class name */
        8,                                             /* instance size */
        igVectorMorphing_GetVTable,                    /* vtable getter */
        0,                                             /* field adder */
        FUN_00186ed0,                                  /* static-initializer callback item (appended on fresh configuration) */
        0                                              /* 0-terminated dependency-callback list */
    );
}
