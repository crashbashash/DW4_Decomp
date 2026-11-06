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
extern igMetaObject *g_beNDMWMdlPlayer_metaObject[];
void *beNDMWMdlPEBase_Register(void);
igMetaObject *beNDMWMdlPEBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlPlayer_GetMetaObject(void);
extern const char beNDMWMdlPlayer_className[];
int beNDMWMdlPlayer_GetVTable(void);
void beNDMWMdlPlayer_InitFields(void);
extern char g_beNDMWMdlPlayer_callbackList[];
void *beNDMWMdlPlayer_Register(void);
}

void *beNDMWMdlPlayer_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPlayer_metaObject,
        beNDMWMdlPEBase_Register,
        beNDMWMdlPEBase_GetPublishedMetaObject,
        beNDMWMdlPlayer_GetMetaObject,
        beNDMWMdlPlayer_className,
        0x38, /* instance size */
        beNDMWMdlPlayer_GetVTable,
        beNDMWMdlPlayer_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPlayer_callbackList /* callback list */
    );
}
