int SetVTLBRefillHandler(int cause, void *handler);
void FUN_00113bc0(void);
extern int D_00482258;

int SetTLBHandler(int value)
{
    D_00482258 = value;
    SetVTLBRefillHandler(1, FUN_00113bc0);
    SetVTLBRefillHandler(2, FUN_00113bc0);
    SetVTLBRefillHandler(3, FUN_00113bc0);
    return value;
}
