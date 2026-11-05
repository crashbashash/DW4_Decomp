extern "C" {
int FUN_00241930(void *, int *, int, int, int, int, int, int);
extern int DAT_0050c908[4];
extern int DAT_00539ef0[4];
void *FUN_003718d0(void *arg0);
}

void *FUN_003718d0(void *arg0) {
    FUN_00241930(arg0, &DAT_0050c908[0], 0, 0, 0, 0, 0, 0);
    *(int *)((char *)(arg0) + 88) = (int)(&DAT_00539ef0[0]);
    return arg0;
}
