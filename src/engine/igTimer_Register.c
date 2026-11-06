extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igTimer_GetMetaObject[];
extern char igObject_Register[];
extern char igTimer_className[];
extern char g_igTimer_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002b7b40(void);
void igTimer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igTimer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igTimer_GetMetaObject,
        igTimer_className,
        8, /* instance size */
        0,
        FUN_002b7b40,
        0, /* extra callback item */
        0 /* callback list */
    );
}
