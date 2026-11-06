extern "C" {
extern char DAT_0050db10[];
void sd_29(char *, int, int, char *, char *);
void MDLsetSD(char *, char *, char *, int, int);
}
void MDLsetSD(char * p0, char * p1, char * p2, int p3, int p4)
{
    sd_29(DAT_0050db10, *(int *)0x0058a1f8, *(int *)0x0058a1e4, p0, p1);
}
