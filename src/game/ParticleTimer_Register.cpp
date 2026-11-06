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
extern igMetaObject *g_ParticleTimer_metaObject[];
void *igGeometry_Register(void);
igMetaObject *igGeometry_GetPublishedMetaObject(void);
igMetaObject *ParticleTimer_GetMetaObject(void);
extern const char ParticleTimer_className[];
int ParticleTimer_GetVTable(void);
void ParticleTimer_InitFields(void);
void FUN_0036e860(void);
void *ParticleTimer_Register(void);
}

void *ParticleTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_ParticleTimer_metaObject,
        igGeometry_Register,
        igGeometry_GetPublishedMetaObject,
        ParticleTimer_GetMetaObject,
        ParticleTimer_className,
        0x40, /* instance size */
        ParticleTimer_GetVTable,
        ParticleTimer_InitFields,
        FUN_0036e860, /* extra callback item */
        0 /* callback list */
    );
}
