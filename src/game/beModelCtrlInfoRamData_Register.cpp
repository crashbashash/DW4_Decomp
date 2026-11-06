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
extern igMetaObject *g_beModelCtrlInfoRamData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfoRamData_GetMetaObject(void);
extern const char beModelCtrlInfoRamData_className[];
int beModelCtrlInfoRamData_GetVTable(void);
void beModelCtrlInfoRamData_InitFields(void);
extern char g_beModelCtrlInfoRamData_callbackList[];
void *beModelCtrlInfoRamData_Register(void);
}

void *beModelCtrlInfoRamData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoRamData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoRamData_GetMetaObject,
        beModelCtrlInfoRamData_className,
        0x18, /* instance size */
        beModelCtrlInfoRamData_GetVTable,
        beModelCtrlInfoRamData_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoRamData_callbackList /* callback list */
    );
}
