struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWMdlEBullet_metaObject[];
void *beModelCtrl_Register(void);
igMetaObject *beModelCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlEBullet_GetMetaObject(void);
extern const char beNDMWMdlEBullet_className[];
int beNDMWMdlEBullet_GetVTable(void);
void *beNDMWMdlEBullet_Register(void);
}

void *beNDMWMdlEBullet_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlEBullet_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlEBullet_GetMetaObject,
        beNDMWMdlEBullet_className,
        0x2c, /* instance size */
        beNDMWMdlEBullet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
