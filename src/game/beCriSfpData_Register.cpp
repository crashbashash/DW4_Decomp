struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beCriSfpData_metaObject[];
void *beBinDataObject_Register(void);
igMetaObject *beBinDataObject_GetPublishedMetaObject(void);
igMetaObject *beCriSfpData_GetMetaObject(void);
extern const char beCriSfpData_className[];
int beCriSfpData_GetVTable(void);
void beCriSfpData_InitFields(void);
void FUN_00366760(void);
void *beCriSfpData_Register(void);
}

void *beCriSfpData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriSfpData_metaObject,
        beBinDataObject_Register,
        beBinDataObject_GetPublishedMetaObject,
        beCriSfpData_GetMetaObject,
        beCriSfpData_className,
        0x28, /* instance size */
        beCriSfpData_GetVTable,
        beCriSfpData_InitFields,
        FUN_00366760, /* extra callback item */
        0 /* callback list */
    );
}
