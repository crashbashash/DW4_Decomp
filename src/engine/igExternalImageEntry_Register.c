/* 0x0014f6e0 igExternalImageEntry_Register: registers class igExternalImageEntry with the object system, derived from igExternalDirEntry.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igExternalImageEntry_GetVTable[];
extern char thunk_igExternalImageEntry_GetMetaObject_0014f750[];
extern char igExternalDirEntry_GetPublishedMetaObject[];
extern char igExternalDirEntry_Register[];
extern char igExternalImageEntry_className[];
extern char g_igExternalImageEntry_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igExternalImageEntry_Register(void) {
    /* Once-only static-init guard for this unit: the first call sets a gp-relative flag byte and
     * (in some units) chains the RunStaticInit thunks of related classes; per its asm, not a registrar. */
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                  /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igExternalImageEntry_metaObject,         /* published MetaObject slot */
        igExternalDirEntry_Register,                        /* base class registrar */
        igExternalDirEntry_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igExternalImageEntry_GetMetaObject_0014f750,  /* own MetaObject accessor (stored at +0x54) */
        igExternalImageEntry_className,          /* class name */
        0x2C,                                               /* instance size */
        igExternalImageEntry_GetVTable,                     /* vtable getter */
        0,                                                  /* field adder */
        0,                                                  /* extra callback item */
        0                                                   /* callback list */
    );
}
