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
extern igMetaObject *g_beModelCtrlInfoDataAIM_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfoDataAIM_GetMetaObject(void);
extern const char beModelCtrlInfoDataAIM_className[];
int beModelCtrlInfoDataAIM_GetVTable(void);
void beModelCtrlInfoDataAIM_InitFields(void);
extern char g_beModelCtrlInfoDataAIM_callbackList[];
void *beModelCtrlInfoDataAIM_Register(void);
}

void *beModelCtrlInfoDataAIM_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoDataAIM_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataAIM_GetMetaObject,
        beModelCtrlInfoDataAIM_className,
        0x14, /* instance size */
        beModelCtrlInfoDataAIM_GetVTable,
        beModelCtrlInfoDataAIM_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataAIM_callbackList /* callback list */
    );
}
