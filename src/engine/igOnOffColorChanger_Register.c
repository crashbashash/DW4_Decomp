/* 0x00451f30 igOnOffColorChanger_Register: registers class igOnOffColorChanger with the object system, derived from igBasicColorChanger.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igOnOffColorChanger_GetVTable[];
extern char thunk_igOnOffColorChanger_GetMetaObject[];
extern char igBasicColorChanger_GetPublishedMetaObject[];
extern char igBasicColorChanger_Register[];
extern char igOnOffColorChanger_className[];
extern char g_igOnOffColorChanger_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igOnOffColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOnOffColorChanger_metaObject,           /* published MetaObject slot */
        igBasicColorChanger_Register,                        /* base class registrar */
        igBasicColorChanger_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igOnOffColorChanger_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        igOnOffColorChanger_className,            /* class name */
        0x58,                                                /* instance size */
        igOnOffColorChanger_GetVTable,                       /* vtable getter */
        0,                                                   /* field adder */
        0,                                                   /* extra callback item */
        0                                                    /* callback list */
    );
}
