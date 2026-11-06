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
extern igMetaObject *g_beNDMWMcSlotXbox_metaObject[];
void *beNDMWMcSlot_Register(void);
igMetaObject *beNDMWMcSlot_GetPublishedMetaObject(void);
igMetaObject *beNDMWMcSlotXbox_GetMetaObject(void);
extern const char beNDMWMcSlotXbox_className[];
int beNDMWMcSlotXbox_GetVTable(void);
void beNDMWMcSlotXbox_InitFields(void);
void *beNDMWMcSlotXbox_Register(void);
}

void *beNDMWMcSlotXbox_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcSlotXbox_metaObject,
        beNDMWMcSlot_Register,
        beNDMWMcSlot_GetPublishedMetaObject,
        beNDMWMcSlotXbox_GetMetaObject,
        beNDMWMcSlotXbox_className,
        0x1c, /* instance size */
        beNDMWMcSlotXbox_GetVTable,
        beNDMWMcSlotXbox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
