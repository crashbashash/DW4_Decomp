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
extern igMetaObject *g_beNDMWShopCtrlDiskSell_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrlDiskSell_GetMetaObject(void);
extern const char beNDMWShopCtrlDiskSell_className[];
int beNDMWShopCtrlDiskSell_GetVTable(void);
void beNDMWShopCtrlDiskSell_InitFields(void);
extern char g_beNDMWShopCtrlDiskSell_callbackList[];
void *beNDMWShopCtrlDiskSell_Register(void);
}

void *beNDMWShopCtrlDiskSell_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlDiskSell_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlDiskSell_GetMetaObject,
        beNDMWShopCtrlDiskSell_className,
        0x68, /* instance size */
        beNDMWShopCtrlDiskSell_GetVTable,
        beNDMWShopCtrlDiskSell_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDiskSell_callbackList /* callback list */
    );
}
