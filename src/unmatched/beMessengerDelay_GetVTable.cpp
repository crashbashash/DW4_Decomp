union U { int vt; int w[12]; char b[48]; };
extern "C" {
int FUN_00357a90(int *, int);
int StringRef_Destruct_00130720(int *, int);
int igObject_InitHeader(char *);
extern int DAT_00536d70[4];
extern void * DAT_00586dc8[4];
int beMessengerDelay_GetVTable(void);
}
int beMessengerDelay_GetVTable(void) {
    union U u;
    int temp_s3;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00536d70[0]);
    u.w[6] = 0;
    u.w[7] = 0;
    u.w[9] = 0;
    u.w[10] = 0;
    temp_s3 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00536d70[0]);
    FUN_00357a90(&u.w[10], -1);
    StringRef_Destruct_00130720(&u.w[9], -1);
    StringRef_Destruct_00130720(&u.w[7], -1);
    StringRef_Destruct_00130720(&u.w[6], -1);
    return temp_s3;
}
