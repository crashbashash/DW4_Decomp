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
extern igMetaObject *g_beNDMWItemYellowArmor_metaObject[];
void *beNDMWItemRevisionBase_Register(void);
igMetaObject *beNDMWItemRevisionBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWItemYellowArmor_GetMetaObject(void);
extern const char beNDMWItemYellowArmor_className[];
int beNDMWItemYellowArmor_GetVTable(void);
void *beNDMWItemYellowArmor_Register(void);
}

void *beNDMWItemYellowArmor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemYellowArmor_metaObject,
        beNDMWItemRevisionBase_Register,
        beNDMWItemRevisionBase_GetPublishedMetaObject,
        beNDMWItemYellowArmor_GetMetaObject,
        beNDMWItemYellowArmor_className,
        0x18, /* instance size */
        beNDMWItemYellowArmor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
