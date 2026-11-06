/* 0x001433e0 igPsx2AudioContext_Register: registers class igPsx2AudioContext with the object system, derived from igAudioContext.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igAudioContext_Register[];
void thunk_FUN_00143150(void);
extern char igPsx2AudioContext_GetVTable[];
extern char igAudioContext_GetPublishedMetaObject[];
extern char g_igPsx2AudioContext_callbackList[];
extern char igPsx2AudioContext_className[];
extern char g_igPsx2AudioContext_metaObject[];
int GpFlag_SetOnce_00142f10();
int igMetaObject_RegisterClass();
int igPsx2AudioContext_InitFields();

void igPsx2AudioContext_Register(void) {
    GpFlag_SetOnce_00142f10(); /* sets this module's one-shot guard byte at 0x00554b10 (.sbss) */
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2AudioContext_metaObject,       /* published MetaObject slot */
        igAudioContext_Register,                        /* base class registrar */
        igAudioContext_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_FUN_00143150,                                   /* own MetaObject accessor (stored at +0x54) */
        igPsx2AudioContext_className,        /* class name */
        sizeof(igPsx2AudioContext),                     /* instance size (reflected struct, include/dw4/reflected.h) */
        igPsx2AudioContext_GetVTable,                   /* vtable getter */
        &igPsx2AudioContext_InitFields,                 /* field adder */
        0,                                              /* extra callback item */
        g_igPsx2AudioContext_callbackList      /* callback list */
    );
}
