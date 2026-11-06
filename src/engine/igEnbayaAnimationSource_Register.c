#include "dw4/reflected.h"
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igEnbayaAnimationSource_GetVTable[];
extern char thunk_igEnbayaAnimationSource_GetMetaObject[];
void FUN_001a24d0(void);
extern char igObject_Register[];
extern char igEnbayaAnimationSource_className[];
extern char g_igEnbayaAnimationSource_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igEnbayaAnimationSource_InitFields();

void igEnbayaAnimationSource_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEnbayaAnimationSource_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEnbayaAnimationSource_GetMetaObject,
        igEnbayaAnimationSource_className,
        sizeof(igEnbayaAnimationSource),               /* Instance size. */
        igEnbayaAnimationSource_GetVTable,
        &igEnbayaAnimationSource_InitFields,
        FUN_001a24d0, /* extra callback item */
        0 /* callback list */
    );
}
