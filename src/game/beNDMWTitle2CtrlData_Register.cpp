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
extern igMetaObject *g_beNDMWTitle2CtrlData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWTitle2CtrlData_GetMetaObject(void);
extern const char beNDMWTitle2CtrlData_className[];
int beNDMWTitle2CtrlData_GetVTable(void);
void beNDMWTitle2CtrlData_InitFields(void);
void *beNDMWTitle2CtrlData_Register(void);
}

void *beNDMWTitle2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWTitle2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWTitle2CtrlData_GetMetaObject,
        beNDMWTitle2CtrlData_className,
        0x30, /* instance size */
        beNDMWTitle2CtrlData_GetVTable,
        beNDMWTitle2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
