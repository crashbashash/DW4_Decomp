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
extern igMetaObject *g_beNDMWSaveCtrlCtrlData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWSaveCtrlCtrlData_GetMetaObject(void);
extern const char beNDMWSaveCtrlCtrlData_className[];
int beNDMWSaveCtrlCtrlData_GetVTable(void);
void beNDMWSaveCtrlCtrlData_InitFields(void);
void *beNDMWSaveCtrlCtrlData_Register(void);
}

void *beNDMWSaveCtrlCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveCtrlCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWSaveCtrlCtrlData_GetMetaObject,
        beNDMWSaveCtrlCtrlData_className,
        0x2c, /* instance size */
        beNDMWSaveCtrlCtrlData_GetVTable,
        beNDMWSaveCtrlCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
