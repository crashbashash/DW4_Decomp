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
extern igMetaObject *g_beSvSlotData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beSvSlotData_GetMetaObject(void);
extern const char beSvSlotData_className[];
void beSvSlotData_InitFields(void);
void *beSvSlotData_Register(void);
}

void *beSvSlotData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beSvSlotData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvSlotData_GetMetaObject,
        beSvSlotData_className,
        0x18, /* instance size */
        0,
        beSvSlotData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
