extern "C" {
int FUN_00241930(void *, int *, int *, int, int, int, int, int);
extern int DAT_0050ceb8[4];
extern int DAT_0050d7f0[4];
extern int DAT_00539f00[4];
void *FUN_003717e0(void *arg0);
}

void *FUN_003717e0(void *arg0) {
    FUN_00241930(arg0, &DAT_0050ceb8[0], &DAT_0050d7f0[0], 0, 0, 0, 0, 0);
    *(int *)((char *)(arg0) + 88) = (int)(&DAT_00539f00[0]);
    return arg0;
}
