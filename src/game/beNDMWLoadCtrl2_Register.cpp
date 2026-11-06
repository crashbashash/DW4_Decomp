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
extern igMetaObject *g_beNDMWLoadCtrl2_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadCtrl2_GetMetaObject(void);
extern const char beNDMWLoadCtrl2_className[];
int beNDMWLoadCtrl2_GetVTable(void);
void beNDMWLoadCtrl2_InitFields(void);
extern char g_beNDMWLoadCtrl2_callbackList[];
void *beNDMWLoadCtrl2_Register(void);
}

void *beNDMWLoadCtrl2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadCtrl2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWLoadCtrl2_GetMetaObject,
        beNDMWLoadCtrl2_className,
        0x2c, /* instance size */
        beNDMWLoadCtrl2_GetVTable,
        beNDMWLoadCtrl2_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2_callbackList /* callback list */
    );
}
