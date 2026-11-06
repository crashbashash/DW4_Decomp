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
extern igMetaObject *g_beNDMWMdlEnemyInfoWork_metaObject[];
void *beNDMWMdlPEBaseInfoWork_Register(void);
igMetaObject *beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlEnemyInfoWork_GetMetaObject(void);
extern const char beNDMWMdlEnemyInfoWork_className[];
int beNDMWMdlEnemyInfoWork_GetVTable(void);
void *beNDMWMdlEnemyInfoWork_Register(void);
}

void *beNDMWMdlEnemyInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlEnemyInfoWork_metaObject,
        beNDMWMdlPEBaseInfoWork_Register,
        beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject,
        beNDMWMdlEnemyInfoWork_GetMetaObject,
        beNDMWMdlEnemyInfoWork_className,
        0x114, /* instance size */
        beNDMWMdlEnemyInfoWork_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
