typedef struct {
    char pad0[40];
} SifClientData;

extern SifClientData DAT_004aa3b0;
extern int DAT_0056e580[64];
extern int DAT_0056e680[64];
void FUN_0027e1c0(void);
void FUN_0027e1d8(void);
int FUN_0010e2a8(SifClientData *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize,
                 void *end, void *endarg);

int FUN_00273820(int fno, int *send, int nsend, int *recv, int nrecv)
{
    int i;

    FUN_0027e1c0();
    for (i = 0; i < nsend; i++) {
        DAT_0056e580[i] = send[i];
    }
    FUN_0010e2a8(&DAT_004aa3b0, fno + 1024, 0, DAT_0056e580, nsend * 4, DAT_0056e680, nrecv * 4, 0, 0);
    for (i = 0; i < nrecv; i++) {
        recv[i] = DAT_0056e680[i];
    }
    FUN_0027e1d8();
    return DAT_0056e680[0];
}
