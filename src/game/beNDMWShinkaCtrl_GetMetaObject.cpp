extern "C" {
void beNDMWShinkaCtrl_ResolveMetaObject(void);
void beNDMWShinkaCtrl_GetMetaObject(void);
}
void beNDMWShinkaCtrl_GetMetaObject(void)
{
    beNDMWShinkaCtrl_ResolveMetaObject();
}
