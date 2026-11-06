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
extern igMetaObject *g_beNDMWPanelWazaInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beNDMWPanelWazaInfoRam_GetMetaObject(void);
extern const char beNDMWPanelWazaInfoRam_className[];
int beNDMWPanelWazaInfoRam_GetVTable(void);
void beNDMWPanelWazaInfoRam_InitFields(void);
extern char g_beNDMWPanelWazaInfoRam_callbackList[];
void *beNDMWPanelWazaInfoRam_Register(void);
}

void *beNDMWPanelWazaInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelWazaInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWPanelWazaInfoRam_GetMetaObject,
        beNDMWPanelWazaInfoRam_className,
        0x30, /* instance size */
        beNDMWPanelWazaInfoRam_GetVTable,
        beNDMWPanelWazaInfoRam_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelWazaInfoRam_callbackList /* callback list */
    );
}
