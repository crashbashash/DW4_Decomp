/* 0x002c5560 igExternalDirEntry_Register: registers class igExternalDirEntry with the object system, derived from igDirEntry.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDirEntry_GetPublishedMetaObject_002bdab0[];
extern char igExternalDirEntry_GetVTable[];
extern char thunk_igExternalDirEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char g_igExternalDirEntry_callbackList_004c0cc8[];
extern char s_igExternalDirEntry_className_004f78a0[];
extern char g_igExternalDirEntry_metaObject_00586450[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c55f0(void);  /* code at 0x2c55f0, passed by address (was DAT_2c55f0; docs/engine/function-inventory.md) */
void igExternalDirEntry_Register(void) {
    FUN_002b5d50();  /* set-once guard that first runs the sibling registrars it chains to (asm/FUN_002b5d50.s) */
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igExternalDirEntry_metaObject_00586450,   /* published MetaObject slot */
        igDirEntry_Register,                        /* base class registrar */
        igDirEntry_GetPublishedMetaObject_002bdab0, /* base class MetaObject accessor */
        thunk_igExternalDirEntry_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igExternalDirEntry_className_004f78a0,    /* class name */
        0x2C,                                       /* instance size */
        igExternalDirEntry_GetVTable,               /* vtable getter */
        FUN_002c55f0,                           /* field adder */
        0,                                          /* static-initializer callback item (appended on fresh configuration) */
        g_igExternalDirEntry_callbackList_004c0cc8  /* 0-terminated dependency-callback list */
    );
}
