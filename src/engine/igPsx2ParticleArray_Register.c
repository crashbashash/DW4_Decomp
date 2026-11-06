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
        0, /* abstract */
        g_igPsx2ParticleArray_metaObject,
        igParticleArray_Register,
        igParticleArray_GetPublishedMetaObject,
        thunk_igPsx2ParticleArray_GetMetaObject,
        igPsx2ParticleArray_className,
        0x78, /* instance size */
        igPsx2ParticleArray_GetVTable,
        &igPsx2ParticleArray_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
