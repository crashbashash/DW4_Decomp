/* 0x002c8790 igStringRefListList_Register: registers class igStringRefListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igStringRefListList_GetVTable[];
extern char thunk_igStringRefListList_GetMetaObject[];
extern char g_igStringRefListList_callbackList_004c13c0[];
extern char s_igStringRefListList_className_004f8460[];
extern char g_igStringRefListList_metaObject_005867a8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igStringRefListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igStringRefListList_metaObject_005867a8, /* published MetaObject slot */
        igObjectList_Register,                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igStringRefListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igStringRefListList_className_004f8460,  /* class name */
        0x14,                                      /* instance size */
        igStringRefListList_GetVTable,             /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        g_igStringRefListList_callbackList_004c13c0  /* callback list */
    );
}
