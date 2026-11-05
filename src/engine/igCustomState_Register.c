/* 0x0014f250 igCustomState_Register: registers class igCustomState with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char thunk_igCustomState_GetMetaObject[];
extern char igNamedObject_Register[];
extern char s_igCustomState_className_004dcd08[];
extern char g_igCustomState_metaObject_0055fe88[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igCustomState_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCustomState_metaObject_0055fe88,           /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igCustomState_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igCustomState_className_004dcd08,            /* class name */
        0xC,                                           /* instance size */
        0,                                             /* vtable getter */
        0,                                             /* field adder */
        0,                                             /* extra callback item */
        0                                              /* callback list */
    );
}
