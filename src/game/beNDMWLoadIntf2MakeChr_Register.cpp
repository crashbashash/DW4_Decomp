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
extern igMetaObject *g_beNDMWLoadIntf2MakeChr_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2MakeChr_GetMetaObject(void);
extern const char beNDMWLoadIntf2MakeChr_className[];
int beNDMWLoadIntf2MakeChr_GetVTable(void);
void beNDMWLoadIntf2MakeChr_InitFields(void);
void *beNDMWLoadIntf2MakeChr_Register(void);
}

void *beNDMWLoadIntf2MakeChr_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2MakeChr_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2MakeChr_GetMetaObject,
        beNDMWLoadIntf2MakeChr_className,
        0x3c, /* instance size */
        beNDMWLoadIntf2MakeChr_GetVTable,
        beNDMWLoadIntf2MakeChr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
