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
extern igMetaObject *g_beNDMWShopCtrl10_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrl10_GetMetaObject(void);
extern const char beNDMWShopCtrl10_className[];
int beNDMWShopCtrl10_GetVTable(void);
void beNDMWShopCtrl10_InitFields(void);
void *beNDMWShopCtrl10_Register(void);
}

void *beNDMWShopCtrl10_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrl10_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl10_GetMetaObject,
        beNDMWShopCtrl10_className,
        0x5c, /* instance size */
        beNDMWShopCtrl10_GetVTable,
        beNDMWShopCtrl10_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
