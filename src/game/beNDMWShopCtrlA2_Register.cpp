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
extern igMetaObject *g_beNDMWShopCtrlA2_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrlA2_GetMetaObject(void);
extern const char beNDMWShopCtrlA2_className[];
int beNDMWShopCtrlA2_GetVTable(void);
void *beNDMWShopCtrlA2_Register(void);
}

void *beNDMWShopCtrlA2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlA2_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA2_GetMetaObject,
        beNDMWShopCtrlA2_className,
        0x54, /* instance size */
        beNDMWShopCtrlA2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
