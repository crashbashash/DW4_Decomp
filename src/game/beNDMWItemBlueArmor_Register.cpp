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
extern igMetaObject *g_beNDMWItemBlueArmor_metaObject[];
void *beNDMWItemRevisionPocketBase_Register(void);
igMetaObject *beNDMWItemRevisionPocketBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWItemBlueArmor_GetMetaObject(void);
extern const char beNDMWItemBlueArmor_className[];
int beNDMWItemBlueArmor_GetVTable(void);
void *beNDMWItemBlueArmor_Register(void);
}

void *beNDMWItemBlueArmor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemBlueArmor_metaObject,
        beNDMWItemRevisionPocketBase_Register,
        beNDMWItemRevisionPocketBase_GetPublishedMetaObject,
        beNDMWItemBlueArmor_GetMetaObject,
        beNDMWItemBlueArmor_className,
        0x1c, /* instance size */
        beNDMWItemBlueArmor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
