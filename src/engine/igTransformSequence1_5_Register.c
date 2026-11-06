/* 0x001952a0 igTransformSequence1_5_Register: registers class igTransformSequence1_5 with the object system, derived from igTransformSequence.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igTransformSequence1_5_GetVTable[];
void thunk_FUN_00194ef0(void);
extern char igTransformSequence_GetPublishedMetaObject[];
extern char igTransformSequence_Register[];
extern char g_igTransformSequence1_5_callbackList[];
extern char igTransformSequence1_5_className[];
extern char g_igTransformSequence1_5_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int thunk_FUN_001ddfd0[4];
int igTransformSequence1_5_InitFields();

void igTransformSequence1_5_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* shared set-once latch run before every registration of this family (asm/SceneGraphLibrary_MarkRegistered.s) */
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTransformSequence1_5_metaObject,        /* published MetaObject slot */
        igTransformSequence_Register,                        /* base class registrar */
        igTransformSequence_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_FUN_00194ef0,                                        /* own MetaObject accessor (stored at +0x54) */
        igTransformSequence1_5_className,         /* class name */
        sizeof(igTransformSequence1_5),                      /* instance size (reflected struct, include/dw4/reflected.h) */
        igTransformSequence1_5_GetVTable,                    /* vtable getter */
        &igTransformSequence1_5_InitFields,                  /* field adder */
        thunk_FUN_001ddfd0,                                  /* extra callback item */
        g_igTransformSequence1_5_callbackList       /* callback list */
    );
}
