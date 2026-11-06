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
extern igMetaObject *g_beNDMWShopCtrlDeviceSell_metaObject[];
void *beNDMWListCtrl_Register(void);
igMetaObject *beNDMWListCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrlDeviceSell_GetMetaObject(void);
extern const char beNDMWShopCtrlDeviceSell_className[];
int beNDMWShopCtrlDeviceSell_GetVTable(void);
void beNDMWShopCtrlDeviceSell_InitFields(void);
extern char g_beNDMWShopCtrlDeviceSell_callbackList[];
void *beNDMWShopCtrlDeviceSell_Register(void);
}

void *beNDMWShopCtrlDeviceSell_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlDeviceSell_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlDeviceSell_GetMetaObject,
        beNDMWShopCtrlDeviceSell_className,
        0x64, /* instance size */
        beNDMWShopCtrlDeviceSell_GetVTable,
        beNDMWShopCtrlDeviceSell_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDeviceSell_callbackList /* callback list */
    );
}
