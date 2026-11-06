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
extern igMetaObject *g_beNDMWMdlPBullet_metaObject[];
void *beModelCtrl_Register(void);
igMetaObject *beModelCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlPBullet_GetMetaObject(void);
extern const char beNDMWMdlPBullet_className[];
int beNDMWMdlPBullet_GetVTable(void);
void *beNDMWMdlPBullet_Register(void);
}

void *beNDMWMdlPBullet_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPBullet_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPBullet_GetMetaObject,
        beNDMWMdlPBullet_className,
        0x2c, /* instance size */
        beNDMWMdlPBullet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
