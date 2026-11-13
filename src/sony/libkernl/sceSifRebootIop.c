int scePrintf(const char *fmt, ...);
void sceSifInitRpc(unsigned int mode);
void sceSifExitRpc(void);
int sceSifResetIop(const char *arg, int mode);
extern char rom0Udnl[]; /* "rom0:UDNL " */
extern char tooLongParameter[]; /* "too long parameter '%s'\n" */

int sceSifRebootIop(const char *arg)
{
    char param[80];
    const char *udnl = rom0Udnl;
    const char *p;
    char *d;
    for (p = arg; *p; p++);
    /* length of "rom0:UDNL " + arg must fit the 80-byte parameter */
    if ((unsigned int)(p + 11 - arg) > 80) {
        scePrintf(tooLongParameter, arg);
        return 0;
    }
    sceSifInitRpc(0);
    sceSifExitRpc();
    d = param;
    while (*udnl) *d++ = *udnl++;
    while (*arg) *d++ = *arg++;
    *d = 0;
    return sceSifResetIop(param, 0);
}
