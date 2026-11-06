/* 0x002c5560 igExternalDirEntry_Register: registers class igExternalDirEntry with the object system, derived from igDirEntry.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igDirEntry_GetPublishedMetaObject[];
extern char igExternalDirEntry_GetVTable[];
extern char thunk_igExternalDirEntry_GetMetaObject[];
extern char igDirEntry_Register[];
extern char g_igExternalDirEntry_callbackList[];
extern char igExternalDirEntry_className[];
extern char g_igExternalDirEntry_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c55f0(void);
void igExternalDirEntry_Register(void) {
    FUN_002b5d50();  /* set-once guard that first runs the sibling registrars it chains to (asm/FUN_002b5d50.s) */
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igExternalDirEntry_metaObject,   /* published MetaObject slot */
        igDirEntry_Register,                        /* base class registrar */
        igDirEntry_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igExternalDirEntry_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igExternalDirEntry_className,    /* class name */
        0x2C,                                       /* instance size */
        igExternalDirEntry_GetVTable,               /* vtable getter */
        FUN_002c55f0,                           /* field adder */
        0,                                          /* static-initializer callback item (appended on fresh configuration) */
        g_igExternalDirEntry_callbackList  /* 0-terminated dependency-callback list */
    );
}
