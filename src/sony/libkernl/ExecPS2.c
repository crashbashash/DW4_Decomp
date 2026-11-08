char *SetArg(const char *filename, int argc, char **argv);
void thunk_InitTLB(void);
int FUN_0010ab30(int a, int b, int argc, char **argv);
extern char D_004d2750[];
extern char *D_004822a0;

int ExecPS2(int a, int b, int argc, char **argv)
{
    int result;
    SetArg(D_004d2750, argc, argv);
    thunk_InitTLB();
    result = FUN_0010ab30(a, b, argc, (char **)(D_004822a0 + 4));
    return result;
}
