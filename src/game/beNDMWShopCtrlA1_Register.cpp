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
extern igMetaObject *g_beNDMWShopCtrlA1_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrlA1_GetMetaObject(void);
extern const char beNDMWShopCtrlA1_className[];
int beNDMWShopCtrlA1_GetVTable(void);
void beNDMWShopCtrlA1_InitFields(void);
extern char g_beNDMWShopCtrlA1_callbackList[];
void *beNDMWShopCtrlA1_Register(void);
}

void *beNDMWShopCtrlA1_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlA1_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA1_GetMetaObject,
        beNDMWShopCtrlA1_className,
        0x5c, /* instance size */
        beNDMWShopCtrlA1_GetVTable,
        beNDMWShopCtrlA1_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlA1_callbackList /* callback list */
    );
}
