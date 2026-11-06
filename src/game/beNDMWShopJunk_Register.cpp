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
extern igMetaObject *g_beNDMWShopJunk_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopJunk_GetMetaObject(void);
extern const char beNDMWShopJunk_className[];
int beNDMWShopJunk_GetVTable(void);
void beNDMWShopJunk_InitFields(void);
extern char g_beNDMWShopJunk_callbackList[];
void *beNDMWShopJunk_Register(void);
}

void *beNDMWShopJunk_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopJunk_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopJunk_GetMetaObject,
        beNDMWShopJunk_className,
        0x60, /* instance size */
        beNDMWShopJunk_GetVTable,
        beNDMWShopJunk_InitFields,
        0, /* extra callback item */
        g_beNDMWShopJunk_callbackList /* callback list */
    );
}
