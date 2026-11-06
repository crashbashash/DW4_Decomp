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
extern igMetaObject *g_beNDMWItemAbilityChip_metaObject[];
void *beNDMWItemBase_Register(void);
igMetaObject *beNDMWItemBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWItemAbilityChip_GetMetaObject(void);
extern const char beNDMWItemAbilityChip_className[];
int beNDMWItemAbilityChip_GetVTable(void);
void *beNDMWItemAbilityChip_Register(void);
}

void *beNDMWItemAbilityChip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemAbilityChip_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemAbilityChip_GetMetaObject,
        beNDMWItemAbilityChip_className,
        0x14, /* instance size */
        beNDMWItemAbilityChip_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
