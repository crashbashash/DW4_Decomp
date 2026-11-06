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
extern igMetaObject *g_beModelCtrlInfoRideOn4_metaObject[];
void *beModelCtrlInfoRideOn_Register(void);
igMetaObject *beModelCtrlInfoRideOn_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlInfoRideOn4_GetMetaObject(void);
extern const char beModelCtrlInfoRideOn4_className[];
int beModelCtrlInfoRideOn4_GetVTable(void);
void beModelCtrlInfoRideOn4_InitFields(void);
void *beModelCtrlInfoRideOn4_Register(void);
}

void *beModelCtrlInfoRideOn4_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoRideOn4_metaObject,
        beModelCtrlInfoRideOn_Register,
        beModelCtrlInfoRideOn_GetPublishedMetaObject,
        beModelCtrlInfoRideOn4_GetMetaObject,
        beModelCtrlInfoRideOn4_className,
        0x78, /* instance size */
        beModelCtrlInfoRideOn4_GetVTable,
        beModelCtrlInfoRideOn4_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
