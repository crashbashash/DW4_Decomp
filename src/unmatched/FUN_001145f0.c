char *FUN_001143f0(const char *filename, int argc, char **argv);
void thunk_FUN_00113950(void);
void _ExecOSD(int argc, char **argv);
extern char D_004d2750[];
extern char *D_004822a0;

void FUN_001145f0(int argc, char **argv)
{
    FUN_001143f0(D_004d2750, argc, argv);
    thunk_FUN_00113950();
    _ExecOSD(argc, (char **)(D_004822a0 + 4));
}
