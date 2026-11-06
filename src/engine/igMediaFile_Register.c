/* 0x002c1440 igMediaFile_Register: registers class igMediaFile with the object system, derived from igFile.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igFile_GetPublishedMetaObject[];
extern char igMediaFile_GetVTable[];
extern char thunk_igMediaFile_GetMetaObject[];
extern char igFile_Register[];
extern char g_igMediaFile_callbackList[];
extern char igMediaFile_className[];
extern char g_igMediaFile_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMediaFile_InitFields();

void igMediaFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMediaFile_metaObject,      /* published MetaObject slot */
        igFile_Register,                        /* base class registrar */
        igFile_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMediaFile_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igMediaFile_className,       /* class name */
        0x44,                                   /* instance size */
        igMediaFile_GetVTable,                  /* vtable getter */
        &igMediaFile_InitFields,                /* field adder */
        0,                                      /* extra callback item */
        g_igMediaFile_callbackList     /* callback list */
    );
}
