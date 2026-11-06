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
extern igMetaObject *g_beSvSlotPS2_metaObject[];
void *beSvSlotData_Register(void);
igMetaObject *beSvSlotData_GetPublishedMetaObject(void);
igMetaObject *beSvSlotPS2_GetMetaObject(void);
extern const char beSvSlotPS2_className[];
int beSvSlotPS2_GetVTable(void);
void *beSvSlotPS2_Register(void);
}

void *beSvSlotPS2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvSlotPS2_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotPS2_GetMetaObject,
        beSvSlotPS2_className,
        0x18, /* instance size */
        beSvSlotPS2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
