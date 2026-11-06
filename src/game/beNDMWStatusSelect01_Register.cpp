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
extern igMetaObject *g_beNDMWStatusSelect01_metaObject[];
void *beNDMWWindowSelect_Register(void);
igMetaObject *beNDMWWindowSelect_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusSelect01_GetMetaObject(void);
extern const char beNDMWStatusSelect01_className[];
int beNDMWStatusSelect01_GetVTable(void);
void *beNDMWStatusSelect01_Register(void);
}

void *beNDMWStatusSelect01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSelect01_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelect01_GetMetaObject,
        beNDMWStatusSelect01_className,
        0x70, /* instance size */
        beNDMWStatusSelect01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
