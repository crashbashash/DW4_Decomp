#include "dw4/reflected.h"
extern char igAudioContext_Register[];
void thunk_FUN_00143150(void);
extern char igPsx2AudioContext_GetVTable[];
extern char igAudioContext_GetPublishedMetaObject[];
extern char g_igPsx2AudioContext_callbackList[];
extern char igPsx2AudioContext_className[];
extern char g_igPsx2AudioContext_metaObject[];
int AudioLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPsx2AudioContext_InitFields();

void igPsx2AudioContext_Register(void) {
    AudioLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2AudioContext_metaObject,
        igAudioContext_Register,
        igAudioContext_GetPublishedMetaObject,
        thunk_FUN_00143150,
        igPsx2AudioContext_className,
        sizeof(igPsx2AudioContext),                     /* Instance size. */
        igPsx2AudioContext_GetVTable,
        &igPsx2AudioContext_InitFields,
        0, /* extra callback item */
        g_igPsx2AudioContext_callbackList /* callback list */
    );
}
