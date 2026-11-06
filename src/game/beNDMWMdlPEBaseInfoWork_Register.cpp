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
extern igMetaObject *g_beNDMWMdlPEBaseInfoWork_metaObject[];
void *beModelCtrlInfoWork_Register(void);
igMetaObject *beModelCtrlInfoWork_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlPEBaseInfoWork_GetMetaObject(void);
extern const char beNDMWMdlPEBaseInfoWork_className[];
int beNDMWMdlPEBaseInfoWork_GetVTable(void);
void beNDMWMdlPEBaseInfoWork_InitFields(void);
extern char g_beNDMWMdlPEBaseInfoWork_callbackList[];
void *beNDMWMdlPEBaseInfoWork_Register(void);
}

void *beNDMWMdlPEBaseInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPEBaseInfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlPEBaseInfoWork_GetMetaObject,
        beNDMWMdlPEBaseInfoWork_className,
        0x114, /* instance size */
        beNDMWMdlPEBaseInfoWork_GetVTable,
        beNDMWMdlPEBaseInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPEBaseInfoWork_callbackList /* callback list */
    );
}
