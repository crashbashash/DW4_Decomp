/* Forwards its two arguments to the shared item-base data-base request (0x447bc0) with this
 * class's static data-base table (DAT_0051d770) as the third. */
extern "C" {
extern char DAT_0051d770[];
int beNDMWItemBase_RequestDataBase(int, int, char *);
void Gap__Bec__beNDMWItemWaza__vfunc_21(int, int);
}
void Gap__Bec__beNDMWItemWaza__vfunc_21(int a0, int a1)
{
    beNDMWItemBase_RequestDataBase(a0, a1, DAT_0051d770);
}
