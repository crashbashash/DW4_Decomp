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
extern igMetaObject *g_beSelectCtrlInfoRamData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beSelectCtrlInfoRamData_GetMetaObject(void);
extern const char beSelectCtrlInfoRamData_className[];
int beSelectCtrlInfoRamData_GetVTable(void);
void beSelectCtrlInfoRamData_InitFields(void);
extern char text_0X4[];
void *beSelectCtrlInfoRamData_Register(void);
}

void *beSelectCtrlInfoRamData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSelectCtrlInfoRamData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSelectCtrlInfoRamData_GetMetaObject,
        beSelectCtrlInfoRamData_className,
        0x20, /* instance size */
        beSelectCtrlInfoRamData_GetVTable,
        beSelectCtrlInfoRamData_InitFields,
        0, /* extra callback item */
        text_0X4 /* callback list */
    );
}
