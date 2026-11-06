/* 0x00150210 igTgaLoader_Register: registers class igTgaLoader with the object system, derived from igImageLoader.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igImageLoader_Register[];
extern char igTgaLoader_GetVTable[];
extern char thunk_igTgaLoader_GetMetaObject[];
extern char igImageLoader_GetPublishedMetaObject[];
extern char g_igTgaLoader_callbackList[];
extern char igTgaLoader_className[];
extern char g_igTgaLoader_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igTgaLoader_InitFields();

void igTgaLoader_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTgaLoader_metaObject,             /* published MetaObject slot */
        igImageLoader_Register,                        /* base class registrar */
        igImageLoader_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTgaLoader_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igTgaLoader_className,              /* class name */
        0x30,                                          /* instance size */
        igTgaLoader_GetVTable,                         /* vtable getter */
        &igTgaLoader_InitFields,                       /* field adder */
        0,                                             /* extra callback item */
        g_igTgaLoader_callbackList            /* callback list */
    );
}
