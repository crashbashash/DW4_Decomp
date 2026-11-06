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
extern igMetaObject *g_beModelCtrlInfoDataTrc_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfoDataTrc_GetMetaObject(void);
extern const char beModelCtrlInfoDataTrc_className[];
int beModelCtrlInfoDataTrc_GetVTable(void);
void beModelCtrlInfoDataTrc_InitFields(void);
extern char g_beModelCtrlInfoDataTrc_callbackList[];
void *beModelCtrlInfoDataTrc_Register(void);
}

void *beModelCtrlInfoDataTrc_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoDataTrc_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataTrc_GetMetaObject,
        beModelCtrlInfoDataTrc_className,
        0x14, /* instance size */
        beModelCtrlInfoDataTrc_GetVTable,
        beModelCtrlInfoDataTrc_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataTrc_callbackList /* callback list */
    );
}
