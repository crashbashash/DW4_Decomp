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
extern igMetaObject *g_beNDMWMdlEnemy_metaObject[];
void *beNDMWMdlPEBase_Register(void);
igMetaObject *beNDMWMdlPEBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlEnemy_GetMetaObject(void);
extern const char beNDMWMdlEnemy_className[];
int beNDMWMdlEnemy_GetVTable(void);
void *beNDMWMdlEnemy_Register(void);
}

void *beNDMWMdlEnemy_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlEnemy_metaObject,
        beNDMWMdlPEBase_Register,
        beNDMWMdlPEBase_GetPublishedMetaObject,
        beNDMWMdlEnemy_GetMetaObject,
        beNDMWMdlEnemy_className,
        0x2c, /* instance size */
        beNDMWMdlEnemy_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
