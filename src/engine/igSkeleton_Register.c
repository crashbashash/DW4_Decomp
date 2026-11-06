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
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSkeleton_metaObject,
        igAnimationHierarchy_Register,
        igAnimationHierarchy_GetPublishedMetaObject,
        thunk_FUN_00198550,
        igSkeleton_className,
        sizeof(igSkeleton),                                   /* Instance size. */
        igSkeleton_GetVTable,
        &igSkeleton_InitFields,
        0, /* extra callback item */
        g_igSkeleton_callbackList /* callback list */
    );
}
