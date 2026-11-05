/* 0x002c0550 igMemoryPool_Register: registers class igMemoryPool with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igMemoryPool_GetMetaObject[];
extern char igObject_Register[];
extern char s_igMemoryPool_className_004f6b40[];
extern char g_igMemoryPool_metaObject_00585ea0[];
int igMetaObject_RegisterClass();
int igMemoryPool_InitFields();

void igMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMemoryPool_metaObject_00585ea0,    /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igMemoryPool_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igMemoryPool_className_004f6b40,     /* class name */
        0x70,                                  /* instance size */
        0,                                     /* vtable getter */
        &igMemoryPool_InitFields,              /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
