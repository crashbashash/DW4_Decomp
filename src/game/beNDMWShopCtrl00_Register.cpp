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
extern igMetaObject *g_beNDMWShopCtrl00_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrl00_GetMetaObject(void);
extern const char beNDMWShopCtrl00_className[];
int beNDMWShopCtrl00_GetVTable(void);
void *beNDMWShopCtrl00_Register(void);
}

void *beNDMWShopCtrl00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrl00_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl00_GetMetaObject,
        beNDMWShopCtrl00_className,
        0x54, /* instance size */
        beNDMWShopCtrl00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
