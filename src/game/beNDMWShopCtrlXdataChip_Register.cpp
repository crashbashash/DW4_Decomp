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
extern igMetaObject *g_beNDMWShopCtrlXdataChip_metaObject[];
void *beNDMWListCtrl_Register(void);
igMetaObject *beNDMWListCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrlXdataChip_GetMetaObject(void);
extern const char beNDMWShopCtrlXdataChip_className[];
int beNDMWShopCtrlXdataChip_GetVTable(void);
void beNDMWShopCtrlXdataChip_InitFields(void);
extern char g_beNDMWShopCtrlXdataChip_callbackList[];
void *beNDMWShopCtrlXdataChip_Register(void);
}

void *beNDMWShopCtrlXdataChip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlXdataChip_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlXdataChip_GetMetaObject,
        beNDMWShopCtrlXdataChip_className,
        0x64, /* instance size */
        beNDMWShopCtrlXdataChip_GetVTable,
        beNDMWShopCtrlXdataChip_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlXdataChip_callbackList /* callback list */
    );
}
