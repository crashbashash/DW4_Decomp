typedef struct { int type; int pad[7]; } CbData;
int FUN_00109208(void *, CbData *);
int FUN_00109280(void *mp) {
    CbData cb;
    cb.type = 1;
    FUN_00109208(mp, &cb);
    return 1;
}
