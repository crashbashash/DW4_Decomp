/* 0x0014e060 igImage_Register: registers class igImage with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igImage_GetMetaObject[];
extern char igObject_Register[];
extern char g_igImage_callbackList_00488dc0[];
extern char s_igImage_className_004dc898[];
extern char g_igImage_metaObject_0055fd80[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int thunk_FUN_00156300[4];
int igImage_InitFields();

void igImage_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igImage_metaObject_0055fd80,         /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igImage_GetMetaObject,           /* own MetaObject accessor (stored at +0x54) */
        s_igImage_className_004dc898,          /* class name */
        0x5C,                                  /* instance size */
        0,                                     /* vtable getter */
        &igImage_InitFields,                   /* field adder */
        thunk_FUN_00156300,                    /* extra callback item */
        g_igImage_callbackList_00488dc0        /* callback list */
    );
}
