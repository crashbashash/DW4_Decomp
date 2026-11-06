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
extern igMetaObject *g_beNDMWShopTitle00_metaObject[];
void *beNDMWWindowTitle_Register(void);
igMetaObject *beNDMWWindowTitle_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopTitle00_GetMetaObject(void);
extern const char beNDMWShopTitle00_className[];
int beNDMWShopTitle00_GetVTable(void);
void *beNDMWShopTitle00_Register(void);
}

void *beNDMWShopTitle00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopTitle00_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle00_GetMetaObject,
        beNDMWShopTitle00_className,
        0x50, /* instance size */
        beNDMWShopTitle00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
