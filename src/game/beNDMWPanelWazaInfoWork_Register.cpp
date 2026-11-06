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
extern igMetaObject *g_beNDMWPanelWazaInfoWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWPanelWazaInfoWork_GetMetaObject(void);
extern const char beNDMWPanelWazaInfoWork_className[];
int beNDMWPanelWazaInfoWork_GetVTable(void);
void beNDMWPanelWazaInfoWork_InitFields(void);
extern char g_beNDMWPanelWazaInfoWork_callbackList[];
void *beNDMWPanelWazaInfoWork_Register(void);
}

void *beNDMWPanelWazaInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelWazaInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWPanelWazaInfoWork_GetMetaObject,
        beNDMWPanelWazaInfoWork_className,
        0x30, /* instance size */
        beNDMWPanelWazaInfoWork_GetVTable,
        beNDMWPanelWazaInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelWazaInfoWork_callbackList /* callback list */
    );
}
