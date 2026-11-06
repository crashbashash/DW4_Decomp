/* 0x002d04b0 igPsx2CallStackTracer_Register: registers class igPsx2CallStackTracer with the object system, derived from igCallStackTracer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igCallStackTracer_Register[];
extern char thunk_igPsx2CallStackTracer_GetMetaObject[];
extern char igPsx2CallStackTracer_GetVTable[];
extern char igCallStackTracer_GetPublishedMetaObject[];
extern char igPsx2CallStackTracer_className[];
extern char g_igPsx2CallStackTracer_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igPsx2CallStackTracer_InitFields_002d0530[4];
void igPsx2CallStackTracer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2CallStackTracer_metaObject,       /* published MetaObject slot */
        igCallStackTracer_Register,                        /* base class registrar */
        igCallStackTracer_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2CallStackTracer_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2CallStackTracer_className,        /* class name */
        0x14,                                              /* instance size */
        igPsx2CallStackTracer_GetVTable,                   /* vtable getter */
        &igPsx2CallStackTracer_InitFields_002d0530[0],     /* field adder (post_init in data/reflection.json) */
        0,                                                 /* extra callback-vector item (none) */
        0                                                  /* zero-terminated callback-vector item list (none) */
    );
}
