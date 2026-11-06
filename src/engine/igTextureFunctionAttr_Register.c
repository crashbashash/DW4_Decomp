/* 0x00131d90 igTextureFunctionAttr_Register: registers class igTextureFunctionAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTextureFunctionAttr_GetVTable[];
extern char thunk_igTextureFunctionAttr_GetMetaObject[];
void FUN_00131f70(void);
extern char igTextureFunctionAttr_className[];
extern char g_igTextureFunctionAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTextureFunctionAttr_InitFields();

void igTextureFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered(); /* sets this module's one-shot guard byte at 0x00554b00 (.sbss) */
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureFunctionAttr_metaObject,       /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igTextureFunctionAttr_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igTextureFunctionAttr_className,        /* class name */
        sizeof(igTextureFunctionAttr),                     /* instance size (reflected struct, include/dw4/reflected.h) */
        igTextureFunctionAttr_GetVTable,                   /* vtable getter */
        &igTextureFunctionAttr_InitFields,                 /* field adder */
        FUN_00131f70,                                      /* extra callback item */
        0                                                  /* callback list */
    );
}
