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
extern igMetaObject *g_beModelCtrlInfoDataAIH_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfoDataAIH_GetMetaObject(void);
extern const char beModelCtrlInfoDataAIH_className[];
int beModelCtrlInfoDataAIH_GetVTable(void);
void beModelCtrlInfoDataAIH_InitFields(void);
void *beModelCtrlInfoDataAIH_Register(void);
}

void *beModelCtrlInfoDataAIH_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoDataAIH_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataAIH_GetMetaObject,
        beModelCtrlInfoDataAIH_className,
        0x2c, /* instance size */
        beModelCtrlInfoDataAIH_GetVTable,
        beModelCtrlInfoDataAIH_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
