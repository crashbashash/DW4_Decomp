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
extern igMetaObject *g_beNDMWShopCtrlSell_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrlSell_GetMetaObject(void);
extern const char beNDMWShopCtrlSell_className[];
int beNDMWShopCtrlSell_GetVTable(void);
void *beNDMWShopCtrlSell_Register(void);
}

void *beNDMWShopCtrlSell_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlSell_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlSell_GetMetaObject,
        beNDMWShopCtrlSell_className,
        0x54, /* instance size */
        beNDMWShopCtrlSell_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
