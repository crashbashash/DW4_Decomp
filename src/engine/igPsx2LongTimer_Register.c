/* 0x002cfd80 igPsx2LongTimer_Register: registers class igPsx2LongTimer with the object system, derived from igLongTimer.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igLongTimer_Register[];
extern char thunk_igPsx2LongTimer_GetMetaObject[];
extern char igPsx2LongTimer_GetVTable[];
extern char igLongTimer_GetPublishedMetaObject_002cfdf0[];
void FUN_002cfe00(void);  /* code at 0x2cfe00, passed by address (was DAT_2cfe00; docs/engine/function-inventory.md) */
extern char s_igPsx2LongTimer_className_004f8fb0[];
extern char g_igPsx2LongTimer_metaObject_00586d40[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igPsx2LongTimer_Register(void) {
    FUN_002b5d50();  /* set-once guard that first runs the sibling registrars it chains to (asm/FUN_002b5d50.s) */
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2LongTimer_metaObject_00586d40,       /* published MetaObject slot */
        igLongTimer_Register,                        /* base class registrar */
        igLongTimer_GetPublishedMetaObject_002cfdf0, /* base class MetaObject accessor */
        thunk_igPsx2LongTimer_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igPsx2LongTimer_className_004f8fb0,        /* class name */
        0x28,                                        /* instance size */
        igPsx2LongTimer_GetVTable,                   /* vtable getter */
        0,                                           /* field adder */
        FUN_002cfe00,                                /* static-initializer callback item (appended on fresh configuration) */
        0                                            /* 0-terminated dependency-callback list */
    );
}
