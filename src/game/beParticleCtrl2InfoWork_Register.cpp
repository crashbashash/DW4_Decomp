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
extern igMetaObject *g_beParticleCtrl2InfoWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beParticleCtrl2InfoWork_GetMetaObject(void);
extern const char beParticleCtrl2InfoWork_className[];
int beParticleCtrl2InfoWork_GetVTable(void);
void beParticleCtrl2InfoWork_InitFields(void);
extern char g_beParticleCtrl2InfoWork_callbackList[];
void *beParticleCtrl2InfoWork_Register(void);
}

void *beParticleCtrl2InfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beParticleCtrl2InfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beParticleCtrl2InfoWork_GetMetaObject,
        beParticleCtrl2InfoWork_className,
        0x18, /* instance size */
        beParticleCtrl2InfoWork_GetVTable,
        beParticleCtrl2InfoWork_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2InfoWork_callbackList /* callback list */
    );
}
