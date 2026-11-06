#include "dw4/reflected.h"
extern char igIGBFile_GetVTable[];
extern char thunk_igIGBFile_GetMetaObject[];
extern char igDirectory_GetPublishedMetaObject[];
extern char igDirectory_Register[];
extern char g_igIGBFile_callbackList[];
extern char igIGBFile_className[];
extern char g_igIGBFile_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c43a0(void);
int igIGBFile_InitFields();

void igIGBFile_Register(void) {
    FUN_002b5d50();  /* First-use initializer: sets a gp byte flag, then runs five one-time init calls. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIGBFile_metaObject,
        igDirectory_Register,
        igDirectory_GetPublishedMetaObject,
        thunk_igIGBFile_GetMetaObject,
        igIGBFile_className,
        sizeof(igIGBFile),                           /* Instance size. */
        igIGBFile_GetVTable,
        &igIGBFile_InitFields,
        FUN_002c43a0, /* extra callback item */
        g_igIGBFile_callbackList /* callback list */
    );
}
