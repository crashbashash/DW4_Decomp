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
extern igMetaObject *g_beNDMWShopCtrlEditBit_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopCtrlEditBit_GetMetaObject(void);
extern const char beNDMWShopCtrlEditBit_className[];
int beNDMWShopCtrlEditBit_GetVTable(void);
void beNDMWShopCtrlEditBit_InitFields(void);
void *beNDMWShopCtrlEditBit_Register(void);
}

void *beNDMWShopCtrlEditBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlEditBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlEditBit_GetMetaObject,
        beNDMWShopCtrlEditBit_className,
        0x5c, /* instance size */
        beNDMWShopCtrlEditBit_GetVTable,
        beNDMWShopCtrlEditBit_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
