/* 0x00146b90 igPsx2Window_Register: registers class igPsx2Window with the object system, derived from igWindow.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igWindow_Register[];
void thunk_FUN_00146a60(void);
extern char igPsx2Window_GetVTable[];
extern char igWindow_GetPublishedMetaObject[];
extern char g_igPsx2Window_callbackList[];
extern char igPsx2Window_className[];
extern char g_igPsx2Window_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPsx2Window_InitFields();

void igPsx2Window_Register(void) {
    WindowInputLibrary_MarkRegistered(); /* sets this module's one-shot guard byte at 0x00554b14 (.sbss) */
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2Window_metaObject,       /* published MetaObject slot */
        igWindow_Register,                        /* base class registrar */
        igWindow_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_FUN_00146a60,                             /* own MetaObject accessor (stored at +0x54) */
        igPsx2Window_className,        /* class name */
        sizeof(igPsx2Window),                     /* instance size (reflected struct, include/dw4/reflected.h) */
        igPsx2Window_GetVTable,                   /* vtable getter */
        &igPsx2Window_InitFields,                 /* field adder */
        0,                                        /* extra callback item */
        g_igPsx2Window_callbackList      /* callback list */
    );
}
