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
extern igMetaObject *g_beNDMWStatusSelect00_metaObject[];
void *beNDMWWindowSelect_Register(void);
igMetaObject *beNDMWWindowSelect_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusSelect00_GetMetaObject(void);
extern const char beNDMWStatusSelect00_className[];
int beNDMWStatusSelect00_GetVTable(void);
void *beNDMWStatusSelect00_Register(void);
}

void *beNDMWStatusSelect00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSelect00_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelect00_GetMetaObject,
        beNDMWStatusSelect00_className,
        0x70, /* instance size */
        beNDMWStatusSelect00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
