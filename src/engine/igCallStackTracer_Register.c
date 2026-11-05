/* 0x002cc720 igCallStackTracer_Register: registers class igCallStackTracer with the object system, derived from igUnsignedIntListNoClean.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igUnsignedIntListNoClean_Register[];
extern char igCallStackTracer_GetVTable[];
extern char thunk_igCallStackTracer_GetMetaObject[];
extern char igUnsignedIntListNoClean_GetPublishedMetaObject_002cc7a0[];
extern char s_igCallStackTracer_className_004f87c0[];
extern char g_igCallStackTracer_metaObject_00586958[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002cc7b0(void);  /* code at 0x2cc7b0, passed by address (was DAT_2cc7b0; docs/engine/function-inventory.md) */
void igCallStackTracer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCallStackTracer_metaObject_00586958,                  /* published MetaObject slot */
        igUnsignedIntListNoClean_Register,                        /* base class registrar */
        igUnsignedIntListNoClean_GetPublishedMetaObject_002cc7a0, /* base class MetaObject accessor */
        thunk_igCallStackTracer_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        s_igCallStackTracer_className_004f87c0,                   /* class name */
        0x14,                                                     /* instance size */
        igCallStackTracer_GetVTable,                              /* vtable getter */
        FUN_002cc7b0,                                         /* field adder */
        0,                                                        /* extra callback item */
        0                                                         /* callback list */
    );
}
