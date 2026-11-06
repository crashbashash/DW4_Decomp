/* 0x0014d1a0 igParticleFormat_Register: registers class igParticleFormat with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igParticleFormat_GetVTable[];
extern char thunk_igParticleFormat_GetMetaObject[];
extern char igObject_Register[];
extern char igParticleFormat_className[];
extern char g_igParticleFormat_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igParticleFormat_InitFields();

void igParticleFormat_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igParticleFormat_metaObject, /* published MetaObject slot */
        igObject_Register,                      /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,  /* base class MetaObject accessor */
        thunk_igParticleFormat_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igParticleFormat_className,  /* class name */
        0x30,                                   /* instance size */
        igParticleFormat_GetVTable,             /* vtable getter */
        &igParticleFormat_InitFields,           /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
