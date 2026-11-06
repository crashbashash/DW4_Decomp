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
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureFunctionAttr_GetMetaObject,
        igTextureFunctionAttr_className,
        sizeof(igTextureFunctionAttr),                     /* Instance size. */
        igTextureFunctionAttr_GetVTable,
        &igTextureFunctionAttr_InitFields,
        FUN_00131f70, /* extra callback item */
        0 /* callback list */
    );
}
