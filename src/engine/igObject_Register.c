/* 0x002ff4f0 igObject_Register: registers class igObject with the object system.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_CreateEmptyInitCallbacks[];
extern char igObject_GetNoParentMetaObject[];
extern char igObject_GetVTable[];
extern char igObject_GetMetaObject[];
extern char s_igObject_className_004faf30[];
extern char g_igObject_metaObject_00587198[];
void *igMetaObject_RegisterClass();
int igObject_InitFields();

void *igObject_Register(void) {
    return igMetaObject_RegisterClass(
        0,                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObject_metaObject_00587198,    /* published MetaObject slot */
        igObject_CreateEmptyInitCallbacks, /* base class registrar */
        igObject_GetNoParentMetaObject,    /* base class MetaObject accessor */
        igObject_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igObject_className_004faf30,     /* class name */
        8,                                 /* instance size */
        igObject_GetVTable,                /* vtable getter */
        &igObject_InitFields,              /* field adder */
        0,                                 /* extra callback item */
        0                                  /* callback list */
    );
}
