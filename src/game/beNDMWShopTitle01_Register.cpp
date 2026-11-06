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
extern igMetaObject *g_beNDMWShopTitle01_metaObject[];
void *beNDMWWindowTitle_Register(void);
igMetaObject *beNDMWWindowTitle_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopTitle01_GetMetaObject(void);
extern const char beNDMWShopTitle01_className[];
int beNDMWShopTitle01_GetVTable(void);
void *beNDMWShopTitle01_Register(void);
}

void *beNDMWShopTitle01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopTitle01_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle01_GetMetaObject,
        beNDMWShopTitle01_className,
        0x50, /* instance size */
        beNDMWShopTitle01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
