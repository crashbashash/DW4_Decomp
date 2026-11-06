/* 0x002c3df0 igIGBFile_Register: registers class igIGBFile with the object system, derived from igDirectory.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igIGBFile_GetVTable[];
extern char thunk_igIGBFile_GetMetaObject[];
extern char igDirectory_GetPublishedMetaObject[];
extern char igDirectory_Register[];
extern char g_igIGBFile_callbackList[];
extern char igIGBFile_className[];
extern char g_igIGBFile_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c43a0(void);  /* code at 0x2c43a0, passed by address (was DAT_2c43a0; docs/engine/function-inventory.md) */
int igIGBFile_InitFields();

void igIGBFile_Register(void) {
    FUN_002b5d50();  /* first-use initializer: sets a gp byte flag, then runs five one-time init calls (asm/FUN_002b5d50.s) */
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igIGBFile_metaObject,             /* published MetaObject slot */
        igDirectory_Register,                        /* base class registrar */
        igDirectory_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igIGBFile_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        igIGBFile_className,              /* class name */
        sizeof(igIGBFile),                           /* instance size (reflected struct, include/dw4/reflected.h) */
        igIGBFile_GetVTable,                         /* vtable getter */
        &igIGBFile_InitFields,                       /* field adder */
        FUN_002c43a0,                            /* extra callback item */
        g_igIGBFile_callbackList            /* callback list */
    );
}
