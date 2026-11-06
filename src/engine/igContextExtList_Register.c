/* 0x002cb430 igContextExtList_Register: registers class igContextExtList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igContextExtList_GetVTable[];
extern char thunk_igContextExtList_GetMetaObject[];
extern char g_igContextExtList_callbackList[];
extern char igContextExtList_className[];
extern char g_igContextExtList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextExtList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igContextExtList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                  /* base class registrar */
        igObjectList_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igContextExtList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igContextExtList_className,  /* class name */
        0x14,                                   /* instance size */
        igContextExtList_GetVTable,             /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        g_igContextExtList_callbackList  /* callback list */
    );
}
