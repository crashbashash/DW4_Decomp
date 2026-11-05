/* 0x002d04b0 igPsx2CallStackTracer_Register: registers class igPsx2CallStackTracer with the object system, derived from igCallStackTracer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCallStackTracer_Register[];
extern char thunk_igPsx2CallStackTracer_GetMetaObject[];
extern char igPsx2CallStackTracer_GetVTable[];
extern char igCallStackTracer_GetPublishedMetaObject_002d0520[];
extern char s_igPsx2CallStackTracer_className_004f9030[];
extern char g_igPsx2CallStackTracer_metaObject_00586db8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igPsx2CallStackTracer_InitFields_002d0530[4];
void igPsx2CallStackTracer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2CallStackTracer_metaObject_00586db8,       /* published MetaObject slot */
        igCallStackTracer_Register,                        /* base class registrar */
        igCallStackTracer_GetPublishedMetaObject_002d0520, /* base class MetaObject accessor */
        thunk_igPsx2CallStackTracer_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2CallStackTracer_className_004f9030,        /* class name */
        0x14,                                              /* instance size */
        igPsx2CallStackTracer_GetVTable,                   /* vtable getter */
        &igPsx2CallStackTracer_InitFields_002d0530[0],     /* field adder (post_init in data/reflection.json) */
        0,                                                 /* extra callback-vector item (none; docs/engine/reflection-registration.md) */
        0                                                  /* zero-terminated callback-vector item list (none) */
    );
}
