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
extern igMetaObject *g_beNDMWPanelObjectItem_metaObject[];
void *beNDMWPanelObject_Register(void);
igMetaObject *beNDMWPanelObject_GetPublishedMetaObject(void);
igMetaObject *beNDMWPanelObjectItem_GetMetaObject(void);
extern const char beNDMWPanelObjectItem_className[];
int beNDMWPanelObjectItem_GetVTable(void);
void beNDMWPanelObjectItem_InitFields(void);
extern char g_beNDMWPanelObjectItem_callbackList[];
void *beNDMWPanelObjectItem_Register(void);
}

void *beNDMWPanelObjectItem_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelObjectItem_metaObject,
        beNDMWPanelObject_Register,
        beNDMWPanelObject_GetPublishedMetaObject,
        beNDMWPanelObjectItem_GetMetaObject,
        beNDMWPanelObjectItem_className,
        0x44, /* instance size */
        beNDMWPanelObjectItem_GetVTable,
        beNDMWPanelObjectItem_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObjectItem_callbackList /* callback list */
    );
}
