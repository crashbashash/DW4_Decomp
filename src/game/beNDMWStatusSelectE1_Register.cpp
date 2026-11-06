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
extern igMetaObject *g_beNDMWStatusSelectE1_metaObject[];
void *beNDMWWindowSelect_Register(void);
igMetaObject *beNDMWWindowSelect_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusSelectE1_GetMetaObject(void);
extern const char beNDMWStatusSelectE1_className[];
int beNDMWStatusSelectE1_GetVTable(void);
void *beNDMWStatusSelectE1_Register(void);
}

void *beNDMWStatusSelectE1_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSelectE1_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelectE1_GetMetaObject,
        beNDMWStatusSelectE1_className,
        0x70, /* instance size */
        beNDMWStatusSelectE1_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
