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
extern igMetaObject *g_beNDMWSaveIntfCtrlData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWSaveIntfCtrlData_GetMetaObject(void);
extern const char beNDMWSaveIntfCtrlData_className[];
int beNDMWSaveIntfCtrlData_GetVTable(void);
void beNDMWSaveIntfCtrlData_InitFields(void);
void *beNDMWSaveIntfCtrlData_Register(void);
}

void *beNDMWSaveIntfCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveIntfCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWSaveIntfCtrlData_GetMetaObject,
        beNDMWSaveIntfCtrlData_className,
        0x34, /* instance size */
        beNDMWSaveIntfCtrlData_GetVTable,
        beNDMWSaveIntfCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
