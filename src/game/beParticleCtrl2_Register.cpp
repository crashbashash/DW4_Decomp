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
extern igMetaObject *g_beParticleCtrl2_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beParticleCtrl2_GetMetaObject(void);
extern const char beParticleCtrl2_className[];
int beParticleCtrl2_GetVTable(void);
void *beParticleCtrl2_Register(void);
}

void *beParticleCtrl2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beParticleCtrl2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beParticleCtrl2_GetMetaObject,
        beParticleCtrl2_className,
        0x20, /* instance size */
        beParticleCtrl2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
