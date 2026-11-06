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
extern igMetaObject *g_beNDMWPanelWazaInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWPanelWazaInfo_GetMetaObject(void);
extern const char beNDMWPanelWazaInfo_className[];
int beNDMWPanelWazaInfo_GetVTable(void);
void *beNDMWPanelWazaInfo_Register(void);
}

void *beNDMWPanelWazaInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelWazaInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWPanelWazaInfo_GetMetaObject,
        beNDMWPanelWazaInfo_className,
        0x1c, /* instance size */
        beNDMWPanelWazaInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
