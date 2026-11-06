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
extern igMetaObject *g_beMessengerArgData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beMessengerArgData_GetMetaObject(void);
extern const char beMessengerArgData_className[];
int beMessengerArgData_GetVTable(void);
void beMessengerArgData_InitFields(void);
extern char g_beMessengerArgData_callbackList[];
void *beMessengerArgData_Register(void);
}

void *beMessengerArgData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerArgData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerArgData_GetMetaObject,
        beMessengerArgData_className,
        0x30, /* instance size */
        beMessengerArgData_GetVTable,
        beMessengerArgData_InitFields,
        0, /* extra callback item */
        g_beMessengerArgData_callbackList /* callback list */
    );
}
