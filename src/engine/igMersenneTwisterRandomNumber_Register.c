extern char igRandomNumber_Register[];
extern char thunk_igMersenneTwisterRandomNumber_GetMetaObject[];
extern char igMersenneTwisterRandomNumber_GetVTable[];
extern char igRandomNumber_GetPublishedMetaObject[];
extern char igMersenneTwisterRandomNumber_className[];
extern char g_igMersenneTwisterRandomNumber_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMersenneTwisterRandomNumber_InitFields();

void igMersenneTwisterRandomNumber_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMersenneTwisterRandomNumber_metaObject,
        igRandomNumber_Register,
        igRandomNumber_GetPublishedMetaObject,
        thunk_igMersenneTwisterRandomNumber_GetMetaObject,
        igMersenneTwisterRandomNumber_className,
        0x9CC, /* instance size */
        igMersenneTwisterRandomNumber_GetVTable,
        &igMersenneTwisterRandomNumber_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
