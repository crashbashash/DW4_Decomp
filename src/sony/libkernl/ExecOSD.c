char *SetArg(const char *filename, int argc, char **argv);
void thunk_InitTLB(void);
void _ExecOSD(int argc, char **argv);
extern char D_004d2750[];
extern char *D_004822a0;

void ExecOSD(int argc, char **argv)
{
    SetArg(D_004d2750, argc, argv);
    thunk_InitTLB();
    _ExecOSD(argc, (char **)(D_004822a0 + 4));
}
