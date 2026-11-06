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
extern igMetaObject *g_beMessengerDelay_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beMessengerDelay_GetMetaObject(void);
extern const char beMessengerDelay_className[];
int beMessengerDelay_GetVTable(void);
void beMessengerDelay_InitFields(void);
extern char g_beMessengerDelay_callbackList[];
void *beMessengerDelay_Register(void);
}

void *beMessengerDelay_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerDelay_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerDelay_GetMetaObject,
        beMessengerDelay_className,
        0x30, /* instance size */
        beMessengerDelay_GetVTable,
        beMessengerDelay_InitFields,
        0, /* extra callback item */
        g_beMessengerDelay_callbackList /* callback list */
    );
}
