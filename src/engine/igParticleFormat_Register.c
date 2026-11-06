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
        0, /* abstract */
        g_igParticleFormat_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igParticleFormat_GetMetaObject,
        igParticleFormat_className,
        0x30, /* instance size */
        igParticleFormat_GetVTable,
        &igParticleFormat_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
