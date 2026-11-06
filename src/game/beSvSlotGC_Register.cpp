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
extern igMetaObject *g_beSvSlotGC_metaObject[];
void *beSvSlotData_Register(void);
igMetaObject *beSvSlotData_GetPublishedMetaObject(void);
igMetaObject *beSvSlotGC_GetMetaObject(void);
extern const char beSvSlotGC_className[];
int beSvSlotGC_GetVTable(void);
void *beSvSlotGC_Register(void);
}

void *beSvSlotGC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvSlotGC_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotGC_GetMetaObject,
        beSvSlotGC_className,
        0x18, /* instance size */
        beSvSlotGC_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
