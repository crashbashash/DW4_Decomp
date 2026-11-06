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
extern igMetaObject *g_beNDMWShopCtrl50_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrl50_GetMetaObject(void);
extern const char beNDMWShopCtrl50_className[];
int beNDMWShopCtrl50_GetVTable(void);
void beNDMWShopCtrl50_InitFields(void);
void *beNDMWShopCtrl50_Register(void);
}

void *beNDMWShopCtrl50_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrl50_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl50_GetMetaObject,
        beNDMWShopCtrl50_className,
        0x68, /* instance size */
        beNDMWShopCtrl50_GetVTable,
        beNDMWShopCtrl50_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
