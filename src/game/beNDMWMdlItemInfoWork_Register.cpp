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
extern igMetaObject *g_beNDMWMdlItemInfoWork_metaObject[];
void *beModelCtrlInfoWork_Register(void);
igMetaObject *beModelCtrlInfoWork_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlItemInfoWork_GetMetaObject(void);
extern const char beNDMWMdlItemInfoWork_className[];
int beNDMWMdlItemInfoWork_GetVTable(void);
void beNDMWMdlItemInfoWork_InitFields(void);
extern char g_beNDMWMdlItemInfoWork_callbackList[];
void *beNDMWMdlItemInfoWork_Register(void);
}

void *beNDMWMdlItemInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlItemInfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlItemInfoWork_GetMetaObject,
        beNDMWMdlItemInfoWork_className,
        0x10c, /* instance size */
        beNDMWMdlItemInfoWork_GetVTable,
        beNDMWMdlItemInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlItemInfoWork_callbackList /* callback list */
    );
}
