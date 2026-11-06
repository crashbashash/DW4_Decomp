extern char igObject_GetMetaObject_ParentAccessor[];
extern char igParticleArray_GetVTable[];
extern char thunk_igParticleArray_GetMetaObject[];
extern char igObject_Register[];
extern char g_igParticleArray_callbackList[];
extern char igParticleArray_className[];
extern char g_igParticleArray_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igParticleArray_InitFields();

void igParticleArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igParticleArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igParticleArray_GetMetaObject,
        igParticleArray_className,
        0x5C, /* instance size */
        igParticleArray_GetVTable,
        &igParticleArray_InitFields,
        0, /* extra callback item */
        g_igParticleArray_callbackList /* callback list */
    );
}
