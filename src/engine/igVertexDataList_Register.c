/* 0x0014b2b0 igVertexDataList_Register: registers class igVertexDataList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igVertexDataList_GetVTable[];
extern char thunk_igVertexDataList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igVertexDataList_callbackList_00488640[];
extern char s_igVertexDataList_className_004dbbc0[];
extern char g_igVertexDataList_metaObject_0055fa48[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igVertexDataList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVertexDataList_metaObject_0055fa48, /* published MetaObject slot */
        igObjectList_Register,                  /* base class registrar */
        igObjectList_GetPublishedMetaObject,    /* base class MetaObject accessor */
        thunk_igVertexDataList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igVertexDataList_className_004dbbc0,  /* class name */
        0x14,                                   /* instance size */
        igVertexDataList_GetVTable,             /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        g_igVertexDataList_callbackList_00488640  /* callback list */
    );
}
