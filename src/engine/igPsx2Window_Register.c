/* 0x00146b90 igPsx2Window_Register: registers class igPsx2Window with the object system, derived from igWindow.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igWindow_Register[];
void thunk_FUN_00146a60(void);  /* code at 0x145ea0, passed by address (was DAT_145ea0; docs/engine/function-inventory.md) */
extern char igPsx2Window_GetVTable[];
extern char igWindow_GetPublishedMetaObject_00146c10[];
extern char g_igPsx2Window_callbackList_00487448[];
extern char s_igPsx2Window_className_004d6c00[];
extern char g_igPsx2Window_metaObject_0055f6c8[];
int GpFlag_SetOnce_00145ce0();
int igMetaObject_RegisterClass();
int igPsx2Window_InitFields();

void igPsx2Window_Register(void) {
    GpFlag_SetOnce_00145ce0(); /* sets this module's one-shot guard byte at 0x00554b14 (.sbss) */
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Window_metaObject_0055f6c8,       /* published MetaObject slot */
        igWindow_Register,                        /* base class registrar */
        igWindow_GetPublishedMetaObject_00146c10, /* base class MetaObject accessor */
        thunk_FUN_00146a60,                             /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2Window_className_004d6c00,        /* class name */
        sizeof(igPsx2Window),                     /* instance size (reflected struct, include/dw4/reflected.h) */
        igPsx2Window_GetVTable,                   /* vtable getter */
        &igPsx2Window_InitFields,                 /* field adder */
        0,                                        /* extra callback item */
        g_igPsx2Window_callbackList_00487448      /* callback list */
    );
}
