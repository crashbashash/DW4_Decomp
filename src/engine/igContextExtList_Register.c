/* 0x002cb430 igContextExtList_Register: registers class igContextExtList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igContextExtList_GetVTable[];
extern char thunk_igContextExtList_GetMetaObject[];
extern char g_igContextExtList_callbackList_004c1408[];
extern char s_igContextExtList_className_004f8680[];
extern char g_igContextExtList_metaObject_005868b8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextExtList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igContextExtList_metaObject_005868b8, /* published MetaObject slot */
        igObjectList_Register,                  /* base class registrar */
        igObjectList_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igContextExtList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igContextExtList_className_004f8680,  /* class name */
        0x14,                                   /* instance size */
        igContextExtList_GetVTable,             /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        g_igContextExtList_callbackList_004c1408  /* callback list */
    );
}
