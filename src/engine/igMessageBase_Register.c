/* 0x00226550 igMessageBase_Register: registers class igMessageBase with the object system, derived from igBase.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igBase_GetPublishedMetaObject_00226010[];
extern char igMessageBase_GetVTable[];
extern char thunk_igMessageBase_GetMetaObject[];
extern char igBase_Register[];
extern char s_igMessageBase_className_004e7aa8[];
extern char g_igMessageBase_metaObject_0056d8c0[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igMessageBase_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessageBase_metaObject_0056d8c0,    /* published MetaObject slot */
        igBase_Register,                        /* base class registrar */
        igBase_GetPublishedMetaObject_00226010, /* base class MetaObject accessor */
        thunk_igMessageBase_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igMessageBase_className_004e7aa8,     /* class name */
        0x20,                                   /* instance size */
        igMessageBase_GetVTable,                /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
