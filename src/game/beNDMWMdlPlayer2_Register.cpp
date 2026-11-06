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
extern igMetaObject *g_beNDMWMdlPlayer2_metaObject[];
void *beModelCtrl_Register(void);
igMetaObject *beModelCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlPlayer2_GetMetaObject(void);
extern const char beNDMWMdlPlayer2_className[];
int beNDMWMdlPlayer2_GetVTable(void);
void beNDMWMdlPlayer2_InitFields(void);
extern char g_beNDMWMdlPlayer2_callbackList[];
void *beNDMWMdlPlayer2_Register(void);
}

void *beNDMWMdlPlayer2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPlayer2_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPlayer2_GetMetaObject,
        beNDMWMdlPlayer2_className,
        0x30, /* instance size */
        beNDMWMdlPlayer2_GetVTable,
        beNDMWMdlPlayer2_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPlayer2_callbackList /* callback list */
    );
}
