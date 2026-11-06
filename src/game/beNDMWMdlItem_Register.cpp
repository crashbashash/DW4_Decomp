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
extern igMetaObject *g_beNDMWMdlItem_metaObject[];
void *beModelCtrl_Register(void);
igMetaObject *beModelCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWMdlItem_GetMetaObject(void);
extern const char beNDMWMdlItem_className[];
int beNDMWMdlItem_GetVTable(void);
void beNDMWMdlItem_InitFields(void);
extern char g_beNDMWMdlItem_callbackList[];
void *beNDMWMdlItem_Register(void);
}

void *beNDMWMdlItem_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlItem_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlItem_GetMetaObject,
        beNDMWMdlItem_className,
        0x34, /* instance size */
        beNDMWMdlItem_GetVTable,
        beNDMWMdlItem_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlItem_callbackList /* callback list */
    );
}
