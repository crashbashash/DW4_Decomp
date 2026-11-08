void FUN_0010eee0(void);
int WaitSema(int sema);
extern int D_00481f04;

int FUN_0010ef30(void)
{
    FUN_0010eee0();
    WaitSema(D_00481f04);
    return 0;
}
