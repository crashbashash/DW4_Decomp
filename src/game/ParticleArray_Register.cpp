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
extern igMetaObject *g_ParticleArray_metaObject[];
void *igParticleArray_Register(void);
igMetaObject *igParticleArray_GetPublishedMetaObject(void);
igMetaObject *ParticleArray_GetMetaObject(void);
extern const char ParticleArray_className[];
int ParticleArray_GetVTable(void);
void ParticleArray_InitFields(void);
extern char g_ParticleArray_callbackList[];
void *ParticleArray_Register(void);
}

void *ParticleArray_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_ParticleArray_metaObject,
        igParticleArray_Register,
        igParticleArray_GetPublishedMetaObject,
        ParticleArray_GetMetaObject,
        ParticleArray_className,
        0x7c, /* instance size */
        ParticleArray_GetVTable,
        ParticleArray_InitFields,
        0, /* extra callback item */
        g_ParticleArray_callbackList /* callback list */
    );
}
