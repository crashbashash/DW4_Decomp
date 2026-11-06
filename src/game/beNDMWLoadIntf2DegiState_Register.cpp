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
extern igMetaObject *g_beNDMWLoadIntf2DegiState_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWLoadIntf2DegiState_GetMetaObject(void);
extern const char beNDMWLoadIntf2DegiState_className[];
int beNDMWLoadIntf2DegiState_GetVTable(void);
void beNDMWLoadIntf2DegiState_InitFields(void);
extern char g_beNDMWLoadIntf2DegiState_callbackList[];
void *beNDMWLoadIntf2DegiState_Register(void);
}

void *beNDMWLoadIntf2DegiState_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2DegiState_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadIntf2DegiState_GetMetaObject,
        beNDMWLoadIntf2DegiState_className,
        0x44, /* instance size */
        beNDMWLoadIntf2DegiState_GetVTable,
        beNDMWLoadIntf2DegiState_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiState_callbackList /* callback list */
    );
}
