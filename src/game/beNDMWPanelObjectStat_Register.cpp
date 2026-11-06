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
extern igMetaObject *g_beNDMWPanelObjectStat_metaObject[];
void *beNDMWPanelObject_Register(void);
igMetaObject *beNDMWPanelObject_GetPublishedMetaObject(void);
igMetaObject *beNDMWPanelObjectStat_GetMetaObject(void);
extern const char beNDMWPanelObjectStat_className[];
int beNDMWPanelObjectStat_GetVTable(void);
void beNDMWPanelObjectStat_InitFields(void);
extern char g_beNDMWPanelObjectStat_callbackList[];
void *beNDMWPanelObjectStat_Register(void);
}

void *beNDMWPanelObjectStat_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelObjectStat_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectStat_GetMetaObject,
        beNDMWPanelObjectStat_className,
        0x48, /* instance size */
        beNDMWPanelObjectStat_GetVTable,
        beNDMWPanelObjectStat_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectStat_callbackList /* callback list */
    );
}
