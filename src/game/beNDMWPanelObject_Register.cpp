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
extern igMetaObject *g_beNDMWPanelObject_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWPanelObject_GetMetaObject(void);
extern const char beNDMWPanelObject_className[];
void beNDMWPanelObject_InitFields(void);
extern char g_beNDMWPanelObject_callbackList[];
void *beNDMWPanelObject_Register(void);
}

void *beNDMWPanelObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWPanelObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWPanelObject_GetMetaObject,
        beNDMWPanelObject_className,
        0x3c, /* instance size */
        0,
        beNDMWPanelObject_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObject_callbackList /* callback list */
    );
}
