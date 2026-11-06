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
extern igMetaObject *g_beNDMWShopSelect11_metaObject[];
void *beNDMWWindowSelect_Register(void);
igMetaObject *beNDMWWindowSelect_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopSelect11_GetMetaObject(void);
extern const char beNDMWShopSelect11_className[];
int beNDMWShopSelect11_GetVTable(void);
void *beNDMWShopSelect11_Register(void);
}

void *beNDMWShopSelect11_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect11_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect11_GetMetaObject,
        beNDMWShopSelect11_className,
        0x70, /* instance size */
        beNDMWShopSelect11_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
