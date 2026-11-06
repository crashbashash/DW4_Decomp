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
extern igMetaObject *g_beNDMWMcSlotGC_metaObject[];
void *beNDMWMcSlot_Register(void);
igMetaObject *beNDMWMcSlot_GetPublishedMetaObject(void);
igMetaObject *beNDMWMcSlotGC_GetMetaObject(void);
extern const char beNDMWMcSlotGC_className[];
int beNDMWMcSlotGC_GetVTable(void);
void beNDMWMcSlotGC_InitFields(void);
void *beNDMWMcSlotGC_Register(void);
}

void *beNDMWMcSlotGC_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcSlotGC_metaObject,
        beNDMWMcSlot_Register,
        beNDMWMcSlot_GetPublishedMetaObject,
        beNDMWMcSlotGC_GetMetaObject,
        beNDMWMcSlotGC_className,
        0x20, /* instance size */
        beNDMWMcSlotGC_GetVTable,
        beNDMWMcSlotGC_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
