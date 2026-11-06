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
extern igMetaObject *g_beNDMWShopCtrlEvolve_metaObject[];
void *beNDMWListCtrl_Register(void);
igMetaObject *beNDMWListCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrlEvolve_GetMetaObject(void);
extern const char beNDMWShopCtrlEvolve_className[];
int beNDMWShopCtrlEvolve_GetVTable(void);
void beNDMWShopCtrlEvolve_InitFields(void);
extern char g_beNDMWShopCtrlEvolve_callbackList[];
void *beNDMWShopCtrlEvolve_Register(void);
}

void *beNDMWShopCtrlEvolve_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlEvolve_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlEvolve_GetMetaObject,
        beNDMWShopCtrlEvolve_className,
        0x64, /* instance size */
        beNDMWShopCtrlEvolve_GetVTable,
        beNDMWShopCtrlEvolve_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlEvolve_callbackList /* callback list */
    );
}
