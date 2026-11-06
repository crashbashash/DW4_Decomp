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
extern igMetaObject *g_beNDMWMdlPEBase_metaObject[];
void *beModelCtrl_Register(void);
igMetaObject *beModelCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlPEBase_GetMetaObject(void);
extern const char beNDMWMdlPEBase_className[];
void *beNDMWMdlPEBase_Register(void);
}

void *beNDMWMdlPEBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWMdlPEBase_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPEBase_GetMetaObject,
        beNDMWMdlPEBase_className,
        0x2c, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
