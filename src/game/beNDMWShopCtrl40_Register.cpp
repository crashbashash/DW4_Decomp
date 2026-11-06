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
extern igMetaObject *g_beNDMWShopCtrl40_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrl40_GetMetaObject(void);
extern const char beNDMWShopCtrl40_className[];
int beNDMWShopCtrl40_GetVTable(void);
void beNDMWShopCtrl40_InitFields(void);
void *beNDMWShopCtrl40_Register(void);
}

void *beNDMWShopCtrl40_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrl40_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl40_GetMetaObject,
        beNDMWShopCtrl40_className,
        0x58, /* instance size */
        beNDMWShopCtrl40_GetVTable,
        beNDMWShopCtrl40_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
