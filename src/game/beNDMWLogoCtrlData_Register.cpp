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
extern igMetaObject *g_beNDMWLogoCtrlData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLogoCtrlData_GetMetaObject(void);
extern const char beNDMWLogoCtrlData_className[];
int beNDMWLogoCtrlData_GetVTable(void);
void beNDMWLogoCtrlData_InitFields(void);
void *beNDMWLogoCtrlData_Register(void);
}

void *beNDMWLogoCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLogoCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLogoCtrlData_GetMetaObject,
        beNDMWLogoCtrlData_className,
        0x20, /* instance size */
        beNDMWLogoCtrlData_GetVTable,
        beNDMWLogoCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
