#include "dw4/reflected.h"
extern char igTransformSource_Register[];
extern char igTransformSource_GetPublishedMetaObject[];
extern char igEnbayaTransformSource_GetVTable[];
void thunk_FUN_001a18b0(void);
extern char g_igEnbayaTransformSource_callbackList[];
extern char igEnbayaTransformSource_className[];
extern char g_igEnbayaTransformSource_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igEnbayaTransformSource_InitFields();

void igEnbayaTransformSource_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEnbayaTransformSource_metaObject,
        igTransformSource_Register,
        igTransformSource_GetPublishedMetaObject,
        thunk_FUN_001a18b0,
        igEnbayaTransformSource_className,
        sizeof(igEnbayaTransformSource),                   /* Instance size. */
        igEnbayaTransformSource_GetVTable,
        &igEnbayaTransformSource_InitFields,
        0, /* extra callback item */
        g_igEnbayaTransformSource_callbackList /* callback list */
    );
}
