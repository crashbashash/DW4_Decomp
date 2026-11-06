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
extern igMetaObject *g_beNDMWShopDevice_metaObject[];
void *beNDMWListCtrl_Register(void);
igMetaObject *beNDMWListCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopDevice_GetMetaObject(void);
extern const char beNDMWShopDevice_className[];
int beNDMWShopDevice_GetVTable(void);
void beNDMWShopDevice_InitFields(void);
extern char g_beNDMWShopDevice_callbackList[];
void *beNDMWShopDevice_Register(void);
}

void *beNDMWShopDevice_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopDevice_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopDevice_GetMetaObject,
        beNDMWShopDevice_className,
        0x64, /* instance size */
        beNDMWShopDevice_GetVTable,
        beNDMWShopDevice_InitFields,
        0, /* extra callback item */
        g_beNDMWShopDevice_callbackList /* callback list */
    );
}
