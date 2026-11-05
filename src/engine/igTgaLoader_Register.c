/* 0x00150210 igTgaLoader_Register: registers class igTgaLoader with the object system, derived from igImageLoader.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igImageLoader_Register[];
extern char igTgaLoader_GetVTable[];
extern char thunk_igTgaLoader_GetMetaObject[];
extern char igImageLoader_GetPublishedMetaObject_001502a0[];
extern char g_igTgaLoader_callbackList_00489140[];
extern char s_igTgaLoader_className_004dce38[];
extern char g_igTgaLoader_metaObject_0055ff10[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igTgaLoader_InitFields();

void igTgaLoader_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTgaLoader_metaObject_0055ff10,             /* published MetaObject slot */
        igImageLoader_Register,                        /* base class registrar */
        igImageLoader_GetPublishedMetaObject_001502a0, /* base class MetaObject accessor */
        thunk_igTgaLoader_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        s_igTgaLoader_className_004dce38,              /* class name */
        0x30,                                          /* instance size */
        igTgaLoader_GetVTable,                         /* vtable getter */
        &igTgaLoader_InitFields,                       /* field adder */
        0,                                             /* extra callback item */
        g_igTgaLoader_callbackList_00489140            /* callback list */
    );
}
