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
extern igMetaObject *g_beSvSlotXbox_metaObject[];
void *beSvSlotData_Register(void);
igMetaObject *beSvSlotData_GetPublishedMetaObject(void);
igMetaObject *beSvSlotXbox_GetMetaObject(void);
extern const char beSvSlotXbox_className[];
int beSvSlotXbox_GetVTable(void);
void beSvSlotXbox_InitFields(void);
void *beSvSlotXbox_Register(void);
}

void *beSvSlotXbox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvSlotXbox_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotXbox_GetMetaObject,
        beSvSlotXbox_className,
        0x38, /* instance size */
        beSvSlotXbox_GetVTable,
        beSvSlotXbox_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
