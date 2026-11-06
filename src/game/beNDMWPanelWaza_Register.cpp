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
extern igMetaObject *g_beNDMWPanelWaza_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWPanelWaza_GetMetaObject(void);
extern const char beNDMWPanelWaza_className[];
int beNDMWPanelWaza_GetVTable(void);
void beNDMWPanelWaza_InitFields(void);
extern char g_beNDMWPanelWaza_callbackList[];
void *beNDMWPanelWaza_Register(void);
}

void *beNDMWPanelWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelWaza_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWPanelWaza_GetMetaObject,
        beNDMWPanelWaza_className,
        0x24, /* instance size */
        beNDMWPanelWaza_GetVTable,
        beNDMWPanelWaza_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelWaza_callbackList /* callback list */
    );
}
