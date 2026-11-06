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
extern igMetaObject *g_beMessengerWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beMessengerWork_GetMetaObject(void);
extern const char beMessengerWork_className[];
int beMessengerWork_GetVTable(void);
void beMessengerWork_InitFields(void);
extern char g_beMessengerWork_callbackList[];
void *beMessengerWork_Register(void);
}

void *beMessengerWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerWork_GetMetaObject,
        beMessengerWork_className,
        0x20, /* instance size */
        beMessengerWork_GetVTable,
        beMessengerWork_InitFields,
        0, /* extra callback item */
        g_beMessengerWork_callbackList /* callback list */
    );
}
