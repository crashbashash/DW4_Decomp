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
extern igMetaObject *g_beNDMWLoadCtrl2Info_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadCtrl2Info_GetMetaObject(void);
extern const char beNDMWLoadCtrl2Info_className[];
int beNDMWLoadCtrl2Info_GetVTable(void);
void beNDMWLoadCtrl2Info_InitFields(void);
extern char g_beNDMWLoadCtrl2Info_callbackList[];
void *beNDMWLoadCtrl2Info_Register(void);
}

void *beNDMWLoadCtrl2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadCtrl2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLoadCtrl2Info_GetMetaObject,
        beNDMWLoadCtrl2Info_className,
        0x20, /* instance size */
        beNDMWLoadCtrl2Info_GetVTable,
        beNDMWLoadCtrl2Info_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2Info_callbackList /* callback list */
    );
}
