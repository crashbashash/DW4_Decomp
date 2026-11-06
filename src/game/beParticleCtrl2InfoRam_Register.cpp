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
extern igMetaObject *g_beParticleCtrl2InfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beParticleCtrl2InfoRam_GetMetaObject(void);
extern const char beParticleCtrl2InfoRam_className[];
int beParticleCtrl2InfoRam_GetVTable(void);
void beParticleCtrl2InfoRam_InitFields(void);
extern char g_beParticleCtrl2InfoRam_callbackList[];
void *beParticleCtrl2InfoRam_Register(void);
}

void *beParticleCtrl2InfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beParticleCtrl2InfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beParticleCtrl2InfoRam_GetMetaObject,
        beParticleCtrl2InfoRam_className,
        0x38, /* instance size */
        beParticleCtrl2InfoRam_GetVTable,
        beParticleCtrl2InfoRam_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2InfoRam_callbackList /* callback list */
    );
}
