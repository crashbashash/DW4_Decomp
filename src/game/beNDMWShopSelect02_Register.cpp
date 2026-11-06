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
extern igMetaObject *g_beNDMWShopSelect02_metaObject[];
void *beNDMWWindowSelect_Register(void);
igMetaObject *beNDMWWindowSelect_GetPublishedMetaObject(void);
igMetaObject *beNDMWShopSelect02_GetMetaObject(void);
extern const char beNDMWShopSelect02_className[];
int beNDMWShopSelect02_GetVTable(void);
void beNDMWShopSelect02_InitFields(void);
extern char g_beNDMWShopSelect02_callbackList[];
void *beNDMWShopSelect02_Register(void);
}

void *beNDMWShopSelect02_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopSelect02_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect02_GetMetaObject,
        beNDMWShopSelect02_className,
        0x74, /* instance size */
        beNDMWShopSelect02_GetVTable,
        beNDMWShopSelect02_InitFields,
        0, /* extra callback item */
        g_beNDMWShopSelect02_callbackList /* callback list */
    );
}
