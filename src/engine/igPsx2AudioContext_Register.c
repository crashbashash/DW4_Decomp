/* 0x001433e0 igPsx2AudioContext_Register: registers class igPsx2AudioContext with the object system, derived from igAudioContext.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igAudioContext_Register[];
void thunk_FUN_00143150(void);  /* code at 0x143140, passed by address (was DAT_143140; docs/engine/function-inventory.md) */
extern char igPsx2AudioContext_GetVTable[];
extern char igAudioContext_GetPublishedMetaObject_00143460[];
extern char g_igPsx2AudioContext_callbackList_00486d00[];
extern char s_igPsx2AudioContext_className_004d5e90[];
extern char g_igPsx2AudioContext_metaObject_0055f550[];
int GpFlag_SetOnce_00142f10();
int igMetaObject_RegisterClass();
int igPsx2AudioContext_InitFields();

void igPsx2AudioContext_Register(void) {
    GpFlag_SetOnce_00142f10(); /* sets this module's one-shot guard byte at 0x00554b10 (.sbss) */
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2AudioContext_metaObject_0055f550,       /* published MetaObject slot */
        igAudioContext_Register,                        /* base class registrar */
        igAudioContext_GetPublishedMetaObject_00143460, /* base class MetaObject accessor */
        thunk_FUN_00143150,                                   /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2AudioContext_className_004d5e90,        /* class name */
        sizeof(igPsx2AudioContext),                     /* instance size (reflected struct, include/dw4/reflected.h) */
        igPsx2AudioContext_GetVTable,                   /* vtable getter */
        &igPsx2AudioContext_InitFields,                 /* field adder */
        0,                                              /* extra callback item */
        g_igPsx2AudioContext_callbackList_00486d00      /* callback list */
    );
}
