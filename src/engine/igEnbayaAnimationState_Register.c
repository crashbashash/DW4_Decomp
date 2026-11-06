/* 0x001a2040 igEnbayaAnimationState_Register: registers class igEnbayaAnimationState with the object system, derived from igAnimationState.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igEnbayaAnimationState_GetVTable[];
extern char thunk_igEnbayaAnimationState_GetMetaObject[];
extern char igAnimationState_GetPublishedMetaObject[];
void FUN_001a2190(void);
extern char igAnimationState_Register[];
extern char igEnbayaAnimationState_className[];
extern char g_igEnbayaAnimationState_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igEnbayaAnimationState_InitFields();

void igEnbayaAnimationState_Register(void) {
    SceneGraphLibrary_MarkRegistered(); /* sets this module's one-shot guard byte at 0x00554b80 (.sbss) */
    igMetaObject_RegisterClass(
        0,                                                /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEnbayaAnimationState_metaObject,     /* published MetaObject slot */
        igAnimationState_Register,                        /* base class registrar */
        igAnimationState_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igEnbayaAnimationState_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        igEnbayaAnimationState_className,      /* class name */
        sizeof(igEnbayaAnimationState),                   /* instance size (reflected struct, include/dw4/reflected.h) */
        igEnbayaAnimationState_GetVTable,                 /* vtable getter */
        &igEnbayaAnimationState_InitFields,               /* field adder */
        FUN_001a2190,                                     /* extra callback item */
        0                                                 /* callback list */
    );
}
