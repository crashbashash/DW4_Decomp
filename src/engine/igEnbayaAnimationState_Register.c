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
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEnbayaAnimationState_metaObject,
        igAnimationState_Register,
        igAnimationState_GetPublishedMetaObject,
        thunk_igEnbayaAnimationState_GetMetaObject,
        igEnbayaAnimationState_className,
        sizeof(igEnbayaAnimationState),                   /* Instance size. */
        igEnbayaAnimationState_GetVTable,
        &igEnbayaAnimationState_InitFields,
        FUN_001a2190, /* extra callback item */
        0 /* callback list */
    );
}
