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
extern igMetaObject *g_beNDMWShopTitle03_metaObject[];
void *beNDMWWindowTitle_Register(void);
igMetaObject *beNDMWWindowTitle_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopTitle03_GetMetaObject(void);
extern const char beNDMWShopTitle03_className[];
int beNDMWShopTitle03_GetVTable(void);
void *beNDMWShopTitle03_Register(void);
}

void *beNDMWShopTitle03_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopTitle03_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle03_GetMetaObject,
        beNDMWShopTitle03_className,
        0x50, /* instance size */
        beNDMWShopTitle03_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
