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
extern igMetaObject *g_beNDMWMcSlotPS2_metaObject[];
void *beNDMWMcSlot_Register(void);
igMetaObject *beNDMWMcSlot_GetPublishedMetaObject(void);
igMetaObject *beNDMWMcSlotPS2_GetMetaObject(void);
extern const char beNDMWMcSlotPS2_className[];
int beNDMWMcSlotPS2_GetVTable(void);
void *beNDMWMcSlotPS2_Register(void);
}

void *beNDMWMcSlotPS2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcSlotPS2_metaObject,
        beNDMWMcSlot_Register,
        beNDMWMcSlot_GetPublishedMetaObject,
        beNDMWMcSlotPS2_GetMetaObject,
        beNDMWMcSlotPS2_className,
        0x18, /* instance size */
        beNDMWMcSlotPS2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
