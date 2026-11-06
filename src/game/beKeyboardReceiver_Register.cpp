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
extern igMetaObject *g_beKeyboardReceiver_metaObject[];
void *igEventReceiver_Register(void);
igMetaObject *igEventReceiver_GetPublishedMetaObject(void);
igMetaObject *beKeyboardReceiver_GetMetaObject(void);
extern const char beKeyboardReceiver_className[];
int beKeyboardReceiver_GetVTable(void);
void beKeyboardReceiver_InitFields(void);
extern char g_beKeyboardReceiver_callbackList[];
void *beKeyboardReceiver_Register(void);
}

void *beKeyboardReceiver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beKeyboardReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        beKeyboardReceiver_GetMetaObject,
        beKeyboardReceiver_className,
        0xc, /* instance size */
        beKeyboardReceiver_GetVTable,
        beKeyboardReceiver_InitFields,
        0, /* extra callback item */
        g_beKeyboardReceiver_callbackList /* callback list */
    );
}
