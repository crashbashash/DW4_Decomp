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
extern igMetaObject *g_beNDMWShopCtrlDigilabo_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrlDigilabo_GetMetaObject(void);
extern const char beNDMWShopCtrlDigilabo_className[];
int beNDMWShopCtrlDigilabo_GetVTable(void);
void beNDMWShopCtrlDigilabo_InitFields(void);
extern char g_beNDMWShopCtrlDigilabo_callbackList[];
void *beNDMWShopCtrlDigilabo_Register(void);
}

void *beNDMWShopCtrlDigilabo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlDigilabo_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlDigilabo_GetMetaObject,
        beNDMWShopCtrlDigilabo_className,
        0x6c, /* instance size */
        beNDMWShopCtrlDigilabo_GetVTable,
        beNDMWShopCtrlDigilabo_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDigilabo_callbackList /* callback list */
    );
}
