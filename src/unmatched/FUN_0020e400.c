struct T { long long q[6]; };
int ChangeThreadPriority();
int CreateThread();
int GetThreadId();
int _StartThread();
extern struct T DAT_004965d0;
extern int DAT_004965b8[4];
void FUN_0020e400(void) {
    struct T sp;
    int t, p;
    sp = DAT_004965d0;
    t = GetThreadId();
    p = ChangeThreadPriority(t, 2);
    if (p > 2) {
        ChangeThreadPriority(t, p);
    }
    DAT_004965b8[0] = CreateThread(&sp);
    _StartThread(DAT_004965b8[0], 0);
}
