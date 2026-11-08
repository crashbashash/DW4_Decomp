char *FUN_001143f0(const char *filename, int argc, char **argv);
void thunk_FUN_00113950(void);
void _LoadExecPS2(const char *filename, int argc, char **argv);
extern char *D_004822a0;

void FUN_00114580(const char *filename, int argc, char **argv)
{
    char *name = FUN_001143f0(filename, argc, argv);
    thunk_FUN_00113950();
    _LoadExecPS2(name, argc, (char **)(D_004822a0 + 4));
}
