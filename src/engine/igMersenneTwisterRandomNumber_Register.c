/* 0x001e4630 igMersenneTwisterRandomNumber_Register: registers class igMersenneTwisterRandomNumber with the object system, derived from igRandomNumber.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igRandomNumber_Register[];
extern char thunk_igMersenneTwisterRandomNumber_GetMetaObject[];
extern char igMersenneTwisterRandomNumber_GetVTable[];
extern char igRandomNumber_GetPublishedMetaObject[];
extern char igMersenneTwisterRandomNumber_className[];
extern char g_igMersenneTwisterRandomNumber_metaObject[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();
int igMersenneTwisterRandomNumber_InitFields();

void igMersenneTwisterRandomNumber_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMersenneTwisterRandomNumber_metaObject, /* published MetaObject slot */
        igRandomNumber_Register,                             /* base class registrar */
        igRandomNumber_GetPublishedMetaObject,      /* base class MetaObject accessor */
        thunk_igMersenneTwisterRandomNumber_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igMersenneTwisterRandomNumber_className,  /* class name */
        0x9CC,                                               /* instance size */
        igMersenneTwisterRandomNumber_GetVTable,             /* vtable getter */
        &igMersenneTwisterRandomNumber_InitFields,           /* field adder */
        0,                                                   /* extra callback item */
        0                                                    /* callback list */
    );
}
