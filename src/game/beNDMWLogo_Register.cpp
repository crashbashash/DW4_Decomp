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
extern igMetaObject *g_beNDMWLogo_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWLogo_GetMetaObject(void);
extern const char beNDMWLogo_className[];
int beNDMWLogo_GetVTable(void);
void beNDMWLogo_InitFields(void);
extern char g_beNDMWLogo_callbackList[];
void *beNDMWLogo_Register(void);
}

void *beNDMWLogo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLogo_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWLogo_GetMetaObject,
        beNDMWLogo_className,
        0x5c, /* instance size */
        beNDMWLogo_GetVTable,
        beNDMWLogo_InitFields,
        0, /* extra callback item */
        g_beNDMWLogo_callbackList /* callback list */
    );
}
