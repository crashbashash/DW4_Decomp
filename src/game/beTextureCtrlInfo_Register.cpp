struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beTextureCtrlInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beTextureCtrlInfo_GetMetaObject(void);
extern const char beTextureCtrlInfo_className[];
int beTextureCtrlInfo_GetVTable(void);
void beTextureCtrlInfo_InitFields(void);
extern char g_beTextureCtrlInfo_callbackList[];
void *beTextureCtrlInfo_Register(void);
}

void *beTextureCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beTextureCtrlInfo_GetMetaObject,
        beTextureCtrlInfo_className,
        0x24, /* instance size */
        beTextureCtrlInfo_GetVTable,
        beTextureCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beTextureCtrlInfo_callbackList /* callback list */
    );
}
