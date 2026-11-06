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
extern igMetaObject *g_beNDMWShopSelect34_metaObject[];
void *beNDMWWindowSelect_Register(void);
igMetaObject *beNDMWWindowSelect_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopSelect34_GetMetaObject(void);
extern const char beNDMWShopSelect34_className[];
int beNDMWShopSelect34_GetVTable(void);
void *beNDMWShopSelect34_Register(void);
}

void *beNDMWShopSelect34_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect34_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect34_GetMetaObject,
        beNDMWShopSelect34_className,
        0x70, /* instance size */
        beNDMWShopSelect34_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
