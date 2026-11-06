/* 0x00153470 igPsx2ParticleArray_Register: registers class igPsx2ParticleArray with the object system, derived from igParticleArray.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igParticleArray_Register[];
extern char thunk_igPsx2ParticleArray_GetMetaObject[];
extern char igPsx2ParticleArray_GetVTable[];
extern char igParticleArray_GetPublishedMetaObject[];
extern char igPsx2ParticleArray_className[];
extern char g_igPsx2ParticleArray_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2ParticleArray_InitFields();

void igPsx2ParticleArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                               /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPsx2ParticleArray_metaObject,       /* published MetaObject slot */
        igParticleArray_Register,                        /* base class registrar */
        igParticleArray_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPsx2ParticleArray_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        igPsx2ParticleArray_className,        /* class name */
        0x78,                                            /* instance size */
        igPsx2ParticleArray_GetVTable,                   /* vtable getter */
        &igPsx2ParticleArray_InitFields,                 /* field adder */
        0,                                               /* extra callback item */
        0                                                /* callback list */
    );
}
