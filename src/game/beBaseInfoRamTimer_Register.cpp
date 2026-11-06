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
extern igMetaObject *g_beBaseInfoRamTimer_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beBaseInfoRamTimer_GetMetaObject(void);
extern const char beBaseInfoRamTimer_className[];
int beBaseInfoRamTimer_GetVTable(void);
void beBaseInfoRamTimer_InitFields(void);
void *beBaseInfoRamTimer_Register(void);
}

void *beBaseInfoRamTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoRamTimer_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beBaseInfoRamTimer_GetMetaObject,
        beBaseInfoRamTimer_className,
        0x40, /* instance size */
        beBaseInfoRamTimer_GetVTable,
        beBaseInfoRamTimer_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
