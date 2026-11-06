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
extern igMetaObject *g_beBinDataObject_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beBinDataObject_GetMetaObject(void);
extern const char beBinDataObject_className[];
void beBinDataObject_InitFields(void);
void *beBinDataObject_Register(void);
}

void *beBinDataObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beBinDataObject_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beBinDataObject_GetMetaObject,
        beBinDataObject_className,
        0x18, /* instance size */
        0,
        beBinDataObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
