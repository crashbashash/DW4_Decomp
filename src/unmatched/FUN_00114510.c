char *FUN_001143f0(const char *filename, int argc, char **argv);
void thunk_FUN_00113950(void);
int FUN_0010ab30(int a, int b, int argc, char **argv);
extern char D_004d2750[];
extern char *D_004822a0;

int FUN_00114510(int a, int b, int argc, char **argv)
{
    int result;
    FUN_001143f0(D_004d2750, argc, argv);
    thunk_FUN_00113950();
    result = FUN_0010ab30(a, b, argc, (char **)(D_004822a0 + 4));
    return result;
}
