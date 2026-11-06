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
extern igMetaObject *g_beModelCtrlInfoDataHit_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfoDataHit_GetMetaObject(void);
extern const char beModelCtrlInfoDataHit_className[];
int beModelCtrlInfoDataHit_GetVTable(void);
void beModelCtrlInfoDataHit_InitFields(void);
extern char g_beModelCtrlInfoDataHit_callbackList[];
void *beModelCtrlInfoDataHit_Register(void);
}

void *beModelCtrlInfoDataHit_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoDataHit_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataHit_GetMetaObject,
        beModelCtrlInfoDataHit_className,
        0x1c, /* instance size */
        beModelCtrlInfoDataHit_GetVTable,
        beModelCtrlInfoDataHit_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataHit_callbackList /* callback list */
    );
}
