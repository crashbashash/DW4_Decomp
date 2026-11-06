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
extern igMetaObject *g_beNDMWShopCtrl30_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrl30_GetMetaObject(void);
extern const char beNDMWShopCtrl30_className[];
int beNDMWShopCtrl30_GetVTable(void);
void beNDMWShopCtrl30_InitFields(void);
void *beNDMWShopCtrl30_Register(void);
}

void *beNDMWShopCtrl30_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrl30_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl30_GetMetaObject,
        beNDMWShopCtrl30_className,
        0x58, /* instance size */
        beNDMWShopCtrl30_GetVTable,
        beNDMWShopCtrl30_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
