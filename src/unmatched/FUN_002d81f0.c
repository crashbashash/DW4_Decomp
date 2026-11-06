int FUN_002d8230(void *, int);
int igProperty_FindByName(int, int, int);

void FUN_002d81f0(void *arg0, int arg1) {
    FUN_002d8230(arg0, igProperty_FindByName(*(int *)((char *)arg0 + 28), *(int *)0x585BE0, arg1));
}
