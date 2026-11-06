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
extern igMetaObject *g_beNDMWMdlMapBase_metaObject[];
void *beModelCtrl_Register(void);
igMetaObject *beModelCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlMapBase_GetMetaObject(void);
extern const char beNDMWMdlMapBase_className[];
int beNDMWMdlMapBase_GetVTable(void);
void *beNDMWMdlMapBase_Register(void);
}

void *beNDMWMdlMapBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlMapBase_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlMapBase_GetMetaObject,
        beNDMWMdlMapBase_className,
        0x2c, /* instance size */
        beNDMWMdlMapBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
