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
    SceneGraphLibrary_MarkRegistered();  /* Shared set-once latch run before every registration of this family. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTransformSequence1_5_metaObject,
        igTransformSequence_Register,
        igTransformSequence_GetPublishedMetaObject,
        thunk_FUN_00194ef0,
        igTransformSequence1_5_className,
        sizeof(igTransformSequence1_5),                      /* Instance size. */
        igTransformSequence1_5_GetVTable,
        &igTransformSequence1_5_InitFields,
        thunk_FUN_001ddfd0, /* extra callback item */
        g_igTransformSequence1_5_callbackList /* callback list */
    );
}
