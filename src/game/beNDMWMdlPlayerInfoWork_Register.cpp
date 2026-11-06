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
extern igMetaObject *g_beNDMWMdlPlayerInfoWork_metaObject[];
void *beNDMWMdlPEBaseInfoWork_Register(void);
igMetaObject *beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlPlayerInfoWork_GetMetaObject(void);
extern const char beNDMWMdlPlayerInfoWork_className[];
int beNDMWMdlPlayerInfoWork_GetVTable(void);
void beNDMWMdlPlayerInfoWork_InitFields(void);
extern char g_beNDMWMdlPlayerInfoWork_callbackList[];
void *beNDMWMdlPlayerInfoWork_Register(void);
}

void *beNDMWMdlPlayerInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPlayerInfoWork_metaObject,
        beNDMWMdlPEBaseInfoWork_Register,
        beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject,
        beNDMWMdlPlayerInfoWork_GetMetaObject,
        beNDMWMdlPlayerInfoWork_className,
        0x130, /* instance size */
        beNDMWMdlPlayerInfoWork_GetVTable,
        beNDMWMdlPlayerInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPlayerInfoWork_callbackList /* callback list */
    );
}
