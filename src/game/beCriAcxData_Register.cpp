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
extern igMetaObject *g_beCriAcxData_metaObject[];
void *beBinDataObject_Register(void);
igMetaObject *beBinDataObject_GetPublishedMetaObject(void);
igMetaObject *beCriAcxData_GetMetaObject(void);
extern const char beCriAcxData_className[];
int beCriAcxData_GetVTable(void);
void *beCriAcxData_Register(void);
}

void *beCriAcxData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriAcxData_metaObject,
        beBinDataObject_Register,
        beBinDataObject_GetPublishedMetaObject,
        beCriAcxData_GetMetaObject,
        beCriAcxData_className,
        0x18, /* instance size */
        beCriAcxData_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
