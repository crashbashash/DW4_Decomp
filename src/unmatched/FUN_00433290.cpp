extern "C" {
extern char DAT_0051b318[];
extern char DAT_0051b868[];
extern char DAT_0051b620[];
void beNDMWWindow_PresentModelAtOrigin(int, char *, int, char *, char *);
void FUN_00433290(int, char *, int, char *, char *);
}
void FUN_00433290(int p0, char * p1, int p2, char * p3, char * p4)
{
    beNDMWWindow_PresentModelAtOrigin(p0, DAT_0051b318, 0, DAT_0051b868, DAT_0051b620);
}
