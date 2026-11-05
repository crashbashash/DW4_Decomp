extern void * DAT_0056c0c8[4];
typedef struct O {
    long long f0;
    long long f8;
    int pad[2];
    void *f24;
    int f28;
    char pad2[38];
    signed char lo : 7;
    unsigned char hi : 1;
} O;
void FUN_002082b0(O *arg0) {
    arg0->lo = 0;
    arg0->f8 = 0;
    arg0->f0 = 0;
    arg0->f24 = DAT_0056c0c8[0];
    arg0->f28 = 0;
    DAT_0056c0c8[0] = arg0;
}
