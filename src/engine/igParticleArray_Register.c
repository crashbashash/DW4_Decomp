/* 0x0014cda0 igParticleArray_Register: registers class igParticleArray with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igParticleArray_GetVTable[];
extern char thunk_igParticleArray_GetMetaObject[];
extern char igObject_Register[];
extern char g_igParticleArray_callbackList_004889e0[];
extern char s_igParticleArray_className_004dc240[];
extern char g_igParticleArray_metaObject_0055fbe0[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igParticleArray_InitFields();

void igParticleArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igParticleArray_metaObject_0055fbe0, /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igParticleArray_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igParticleArray_className_004dc240,  /* class name */
        0x5C,                                  /* instance size */
        igParticleArray_GetVTable,             /* vtable getter */
        &igParticleArray_InitFields,           /* field adder */
        0,                                     /* extra callback item */
        g_igParticleArray_callbackList_004889e0  /* callback list */
    );
}
