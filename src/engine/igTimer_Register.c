/* 0x002b7ac0 igTimer_Register: registers class igTimer with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igTimer_GetMetaObject[];
extern char igObject_Register[];
extern char s_igTimer_className_004f5bd0[];
extern char g_igTimer_metaObject_00585788[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002b7b40(void);  /* code at 0x2b7b40, passed by address (was DAT_2b7b40; docs/engine/function-inventory.md) */
void igTimer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTimer_metaObject_00585788,         /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igTimer_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igTimer_className_004f5bd0,          /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        FUN_002b7b40,                      /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
