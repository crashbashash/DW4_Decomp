char *SetArg(const char *filename, int argc, char **argv);
void thunk_InitTLB(void);
void _LoadExecPS2(const char *filename, int argc, char **argv);
extern char *D_004822a0;

void LoadExecPS2(const char *filename, int argc, char **argv)
{
    char *name = SetArg(filename, argc, argv);
    thunk_InitTLB();
    _LoadExecPS2(name, argc, (char **)(D_004822a0 + 4));
}
