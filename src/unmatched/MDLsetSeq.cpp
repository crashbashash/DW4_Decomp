extern "C" {
extern char DAT_0050db10[];
void beMessenger_SendNamed(int, char *, int, int, char *);
void MDLsetSeq(char *, char *, char *, char *, int);
}
void MDLsetSeq(char * p0, char * p1, char * p2, char * p3, int p4)
{
    beMessenger_SendNamed(*(int *)0x0058a1c0, DAT_0050db10, *(int *)0x0058a1f8, *(int *)0x0058a1e4, p0);
}
