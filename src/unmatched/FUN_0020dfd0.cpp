extern "C" {
int FUN_0020d270(long long *);
int WaitSema(int);
extern int DAT_00568ed0[4];
extern int DAT_0056c174[4];
}
struct ThreadLock {
    int sema;
    int pad;
    int owner;
    int semaphore() const { return sema; }
};
extern "C" ThreadLock DAT_0056c640;
extern "C" void FUN_0020dfd0(int arg0) {
    long long start;
    long long end;
    FUN_0020d270(&start);
    DAT_00568ed0[0] = DAT_0056c640.semaphore();
    WaitSema(DAT_0056c640.sema);
    DAT_00568ed0[0] = -1;
    FUN_0020d270(&end);
    DAT_0056c640.owner = arg0;
    DAT_0056c174[0] += (long long) ((end - start) << 0x20) >> 0x20;
}
