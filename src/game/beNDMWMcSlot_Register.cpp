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
extern igMetaObject *g_beNDMWMcSlot_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWMcSlot_GetMetaObject(void);
extern const char beNDMWMcSlot_className[];
void beNDMWMcSlot_InitFields(void);
void *beNDMWMcSlot_Register(void);
}

void *beNDMWMcSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWMcSlot_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWMcSlot_GetMetaObject,
        beNDMWMcSlot_className,
        0x18, /* instance size */
        0,
        beNDMWMcSlot_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
