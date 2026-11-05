/* 0x001a2300 igEnbayaAnimationSource_Register: registers class igEnbayaAnimationSource with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igEnbayaAnimationSource_GetVTable[];
extern char thunk_igEnbayaAnimationSource_GetMetaObject[];
void FUN_001a24d0(void);  /* code at 0x1a24d0, passed by address (was DAT_1a24d0; docs/engine/function-inventory.md) */
extern char igObject_Register[];
extern char s_igEnbayaAnimationSource_className_004e2b00[];
extern char g_igEnbayaAnimationSource_metaObject_00561ba0[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igEnbayaAnimationSource_InitFields();

void igEnbayaAnimationSource_Register(void) {
    GpFlag_SetOnce_00194380(); /* sets this module's one-shot guard byte at 0x00554b80 (.sbss) */
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEnbayaAnimationSource_metaObject_00561ba0, /* published MetaObject slot */
        igObject_Register,                             /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,         /* base class MetaObject accessor */
        thunk_igEnbayaAnimationSource_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igEnbayaAnimationSource_className_004e2b00,  /* class name */
        sizeof(igEnbayaAnimationSource),               /* instance size (reflected struct, include/dw4/reflected.h) */
        igEnbayaAnimationSource_GetVTable,             /* vtable getter */
        &igEnbayaAnimationSource_InitFields,           /* field adder */
        FUN_001a24d0,                                  /* extra callback item */
        0                                              /* callback list */
    );
}
