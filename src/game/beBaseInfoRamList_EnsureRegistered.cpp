extern char beBaseInfoRamList_Register[];
extern "C" {
void igMetaObject_RunStaticInit(char *);
void beBaseInfoRamList_EnsureRegistered(void);
}
void beBaseInfoRamList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRamList_Register);
}
