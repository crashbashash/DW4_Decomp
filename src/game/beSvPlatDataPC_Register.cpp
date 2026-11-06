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
extern igMetaObject *g_beSvPlatDataPC_metaObject[];
void *beSvPlatBaseData_Register(void);
igMetaObject *beSvPlatBaseData_GetPublishedMetaObject(void);
igMetaObject *beSvPlatDataPC_GetMetaObject(void);
extern const char beSvPlatDataPC_className[];
int beSvPlatDataPC_GetVTable(void);
void *beSvPlatDataPC_Register(void);
}

void *beSvPlatDataPC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatDataPC_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataPC_GetMetaObject,
        beSvPlatDataPC_className,
        0x18, /* instance size */
        beSvPlatDataPC_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
