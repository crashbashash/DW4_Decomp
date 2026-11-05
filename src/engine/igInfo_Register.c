/* 0x002c36a0 igInfo_Register: registers class igInfo with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igNamedObject_Register[];
extern char igInfo_GetVTable[];
extern char thunk_igInfo_GetMetaObject[];
extern char g_igInfo_callbackList_004c0618[];
extern char s_igInfo_className_004f7018[];
extern char g_igInfo_metaObject_00586128[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igInfo_InitFields();

void igInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInfo_metaObject_00586128,                  /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igInfo_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        s_igInfo_className_004f7018,                   /* class name */
        0x14,                                          /* instance size */
        igInfo_GetVTable,                              /* vtable getter */
        &igInfo_InitFields,                            /* field adder */
        0,                                             /* extra callback item */
        g_igInfo_callbackList_004c0618                 /* callback list */
    );
}
