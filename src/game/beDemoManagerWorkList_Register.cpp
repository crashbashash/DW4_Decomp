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
extern igMetaObject *g_beDemoManagerWorkList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beDemoManagerWorkList_GetMetaObject(void);
extern const char beDemoManagerWorkList_className[];
int beDemoManagerWorkList_GetVTable(void);
extern char text_096[];
void *beDemoManagerWorkList_Register(void);
}

void *beDemoManagerWorkList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDemoManagerWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDemoManagerWorkList_GetMetaObject,
        beDemoManagerWorkList_className,
        0x14, /* instance size */
        beDemoManagerWorkList_GetVTable,
        0,
        0, /* extra callback item */
        text_096 /* callback list */
    );
}
