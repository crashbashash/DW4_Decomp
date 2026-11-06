struct igMetaObject;
extern "C" {
void AdxMovieLibrary_MarkRegistered(void);
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
extern igMetaObject *g_igCriMovieData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *igCriMovieData_GetMetaObject(void);
extern const char igCriMovieData_className[];
int igCriMovieData_GetVTable(void);
void igCriMovieData_InitFields(void);
void *igCriMovieData_Register(void);
}

void *igCriMovieData_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCriMovieData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igCriMovieData_GetMetaObject,
        igCriMovieData_className,
        0x1c, /* instance size */
        igCriMovieData_GetVTable,
        igCriMovieData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
