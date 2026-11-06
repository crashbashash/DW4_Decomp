#include "dw4/reflected.h"
extern char igWindow_Register[];
void thunk_FUN_00146a60(void);
extern char igPsx2Window_GetVTable[];
extern char igWindow_GetPublishedMetaObject[];
extern char g_igPsx2Window_callbackList[];
extern char igPsx2Window_className[];
extern char g_igPsx2Window_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPsx2Window_InitFields();

void igPsx2Window_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Window_metaObject,
        igWindow_Register,
        igWindow_GetPublishedMetaObject,
        thunk_FUN_00146a60,
        igPsx2Window_className,
        sizeof(igPsx2Window),                     /* Instance size. */
        igPsx2Window_GetVTable,
        &igPsx2Window_InitFields,
        0, /* extra callback item */
        g_igPsx2Window_callbackList /* callback list */
    );
}
