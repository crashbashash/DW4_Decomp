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
extern igMetaObject *g_beMessengerGroup_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beMessengerGroup_GetMetaObject(void);
extern const char beMessengerGroup_className[];
int beMessengerGroup_GetVTable(void);
void beMessengerGroup_InitFields(void);
extern char g_beMessengerGroup_callbackList[];
void *beMessengerGroup_Register(void);
}

void *beMessengerGroup_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerGroup_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMessengerGroup_GetMetaObject,
        beMessengerGroup_className,
        0x18, /* instance size */
        beMessengerGroup_GetVTable,
        beMessengerGroup_InitFields,
        0, /* extra callback item */
        g_beMessengerGroup_callbackList /* callback list */
    );
}
