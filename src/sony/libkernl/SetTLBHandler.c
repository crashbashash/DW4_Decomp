int SetVTLBRefillHandler(int cause, void *handler);
extern char D_00113bc0[];
extern int D_00482258;

int SetTLBHandler(int value)
{
    D_00482258 = value;
    SetVTLBRefillHandler(1, D_00113bc0);
    SetVTLBRefillHandler(2, D_00113bc0);
    SetVTLBRefillHandler(3, D_00113bc0);
    return value;
}
