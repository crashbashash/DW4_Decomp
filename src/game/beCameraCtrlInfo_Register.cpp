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
extern igMetaObject *g_beCameraCtrlInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beCameraCtrlInfo_GetMetaObject(void);
extern const char beCameraCtrlInfo_className[];
int beCameraCtrlInfo_GetVTable(void);
void beCameraCtrlInfo_InitFields(void);
extern char g_beCameraCtrlInfo_callbackList[];
void *beCameraCtrlInfo_Register(void);
}

void *beCameraCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beCameraCtrlInfo_GetMetaObject,
        beCameraCtrlInfo_className,
        0x20, /* instance size */
        beCameraCtrlInfo_GetVTable,
        beCameraCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beCameraCtrlInfo_callbackList /* callback list */
    );
}
