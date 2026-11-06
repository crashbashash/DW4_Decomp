/* 0x001e42f0 igRandomNumber_Register: registers class igRandomNumber with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igRandomNumber_GetMetaObject[];
extern char igObject_Register[];
extern char igRandomNumber_className[];
extern char g_igRandomNumber_metaObject[];
/* Run-once guard shared by the registrars: sets a gp-relative flag byte (asm/GpFlag_SetOnce_001e3ff0.s). */
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();
/* Code in the gap after this function: the class's no-argument field adder (10th registration argument). */
extern int igRandomNumber_InitFields_001e4370[4];
void igRandomNumber_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        1,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRandomNumber_metaObject,   /* published MetaObject slot */
        igObject_Register,                      /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,  /* base class MetaObject accessor */
        thunk_igRandomNumber_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        igRandomNumber_className,    /* class name */
        8,                                      /* instance size */
        0,                                      /* vtable getter */
        &igRandomNumber_InitFields_001e4370[0], /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
