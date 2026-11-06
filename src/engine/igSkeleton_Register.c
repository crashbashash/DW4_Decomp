/* 0x00198690 igSkeleton_Register: registers class igSkeleton with the object system, derived from igAnimationHierarchy.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
#include "dw4/reflected.h"
extern char igSkeleton_GetVTable[];
void thunk_FUN_00198550(void);
extern char igAnimationHierarchy_GetPublishedMetaObject[];
extern char igAnimationHierarchy_Register[];
extern char g_igSkeleton_callbackList[];
extern char igSkeleton_className[];
extern char g_igSkeleton_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSkeleton_InitFields();

void igSkeleton_Register(void) {
    SceneGraphLibrary_MarkRegistered(); /* sets this module's one-shot guard byte at 0x00554b80 (.sbss) */
    igMetaObject_RegisterClass(
        0,                                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSkeleton_metaObject,                     /* published MetaObject slot */
        igAnimationHierarchy_Register,                        /* base class registrar */
        igAnimationHierarchy_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_FUN_00198550,                                         /* own MetaObject accessor (stored at +0x54) */
        igSkeleton_className,                      /* class name */
        sizeof(igSkeleton),                                   /* instance size (reflected struct, include/dw4/reflected.h) */
        igSkeleton_GetVTable,                                 /* vtable getter */
        &igSkeleton_InitFields,                               /* field adder */
        0,                                                    /* extra callback item */
        g_igSkeleton_callbackList                    /* callback list */
    );
}
