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
extern igMetaObject *g_beNDMWPanelObjectWaza_metaObject[];
void *beNDMWPanelObject_Register(void);
igMetaObject *beNDMWPanelObject_GetPublishedMetaObject(void);
igMetaObject *beNDMWPanelObjectWaza_GetMetaObject(void);
extern const char beNDMWPanelObjectWaza_className[];
int beNDMWPanelObjectWaza_GetVTable(void);
void beNDMWPanelObjectWaza_InitFields(void);
extern char g_beNDMWPanelObjectWaza_callbackList[];
void *beNDMWPanelObjectWaza_Register(void);
}

void *beNDMWPanelObjectWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelObjectWaza_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectWaza_GetMetaObject,
        beNDMWPanelObjectWaza_className,
        0x44, /* instance size */
        beNDMWPanelObjectWaza_GetVTable,
        beNDMWPanelObjectWaza_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectWaza_callbackList /* callback list */
    );
}
