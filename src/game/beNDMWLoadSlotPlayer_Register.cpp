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
extern igMetaObject *g_beNDMWLoadSlotPlayer_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWLoadSlotPlayer_GetMetaObject(void);
extern const char beNDMWLoadSlotPlayer_className[];
int beNDMWLoadSlotPlayer_GetVTable(void);
void beNDMWLoadSlotPlayer_InitFields(void);
extern char g_beNDMWLoadSlotPlayer_callbackList[];
void *beNDMWLoadSlotPlayer_Register(void);
}

void *beNDMWLoadSlotPlayer_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadSlotPlayer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadSlotPlayer_GetMetaObject,
        beNDMWLoadSlotPlayer_className,
        0x14, /* instance size */
        beNDMWLoadSlotPlayer_GetVTable,
        beNDMWLoadSlotPlayer_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadSlotPlayer_callbackList /* callback list */
    );
}
