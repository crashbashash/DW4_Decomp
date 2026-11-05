/* 0x00451f30 igOnOffColorChanger_Register: registers class igOnOffColorChanger with the object system, derived from igBasicColorChanger.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igOnOffColorChanger_GetVTable[];
extern char thunk_igOnOffColorChanger_GetMetaObject[];
extern char igBasicColorChanger_GetPublishedMetaObject_00451fb0[];
extern char igBasicColorChanger_Register[];
extern char s_igOnOffColorChanger_className_0051e6d0[];
extern char g_igOnOffColorChanger_metaObject_0058c5e8[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igOnOffColorChanger_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOnOffColorChanger_metaObject_0058c5e8,           /* published MetaObject slot */
        igBasicColorChanger_Register,                        /* base class registrar */
        igBasicColorChanger_GetPublishedMetaObject_00451fb0, /* base class MetaObject accessor */
        thunk_igOnOffColorChanger_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igOnOffColorChanger_className_0051e6d0,            /* class name */
        0x58,                                                /* instance size */
        igOnOffColorChanger_GetVTable,                       /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        0                                                    /* callback list */
    );
}
