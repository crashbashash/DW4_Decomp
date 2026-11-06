/* 0x001a19a0 igEnbayaTransformSource_Register: registers class igEnbayaTransformSource with the object system, derived from igTransformSource.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igTransformSource_Register[];
extern char igTransformSource_GetPublishedMetaObject[];
extern char igEnbayaTransformSource_GetVTable[];
void thunk_FUN_001a18b0(void);
extern char g_igEnbayaTransformSource_callbackList[];
extern char igEnbayaTransformSource_className[];
extern char g_igEnbayaTransformSource_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igEnbayaTransformSource_InitFields();

void igEnbayaTransformSource_Register(void) {
    GpFlag_SetOnce_00194380(); /* sets this module's one-shot guard byte at 0x00554b80 (.sbss) */
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igEnbayaTransformSource_metaObject,     /* published MetaObject slot */
        igTransformSource_Register,                        /* base class registrar */
        igTransformSource_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_FUN_001a18b0,                                      /* own MetaObject accessor (stored at +0x54) */
        igEnbayaTransformSource_className,      /* class name */
        sizeof(igEnbayaTransformSource),                   /* instance size (reflected struct, include/dw4/reflected.h) */
        igEnbayaTransformSource_GetVTable,                 /* vtable getter */
        &igEnbayaTransformSource_InitFields,               /* field adder */
        0,                                                 /* extra callback item */
        g_igEnbayaTransformSource_callbackList    /* callback list */
    );
}
