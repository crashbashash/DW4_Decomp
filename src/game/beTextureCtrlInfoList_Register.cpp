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
extern igMetaObject *g_beTextureCtrlInfoList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beTextureCtrlInfoList_GetMetaObject(void);
extern const char beTextureCtrlInfoList_className[];
int beTextureCtrlInfoList_GetVTable(void);
extern char g_beTextureCtrlInfoList_callbackList[];
void *beTextureCtrlInfoList_Register(void);
}

void *beTextureCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beTextureCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beTextureCtrlInfoList_GetMetaObject,
        beTextureCtrlInfoList_className,
        0x14, /* instance size */
        beTextureCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beTextureCtrlInfoList_callbackList /* callback list */
    );
}
