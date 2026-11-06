struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
void *igMetaObject_RegisterClass(
        int abstractState,
        igMetaObject **slot,
        void *(*baseRegister)(void),
        igMetaObject *(*baseMetaObject)(void),
        igMetaObject *(*getMetaObject)(void),
        const char *className,
        int instanceSize,
        int (*getVTable)(void),
        void (*initFields)(void),
        void (*callbackItem)(void),
        void *callbackList);
extern igMetaObject *g_ParticleInfo_metaObject[];
void *igSceneInfo_Register(void);
igMetaObject *igSceneInfo_GetPublishedMetaObject(void);
igMetaObject *ParticleInfo_GetMetaObject(void);
extern const char ParticleInfo_className[];
int ParticleInfo_GetVTable(void);
void ParticleInfo_InitFields(void);
extern char g_ParticleInfo_callbackList[];
void *ParticleInfo_Register(void);
}

void *ParticleInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_ParticleInfo_metaObject,
        igSceneInfo_Register,
        igSceneInfo_GetPublishedMetaObject,
        ParticleInfo_GetMetaObject,
        ParticleInfo_className,
        0x400, /* instance size */
        ParticleInfo_GetVTable,
        ParticleInfo_InitFields,
        0, /* extra callback item */
        g_ParticleInfo_callbackList /* callback list */
    );
}
