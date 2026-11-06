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
extern igMetaObject *g_beNDMWLogoInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWLogoInfo_GetMetaObject(void);
extern const char beNDMWLogoInfo_className[];
int beNDMWLogoInfo_GetVTable(void);
void *beNDMWLogoInfo_Register(void);
}

void *beNDMWLogoInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLogoInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLogoInfo_GetMetaObject,
        beNDMWLogoInfo_className,
        0x1c, /* instance size */
        beNDMWLogoInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
