extern int DAT_00586020;
extern int thunk_igPsx2Media_GetMetaObject;
extern int thunk_FUN_002ebd70;
void FUN_002fe480(int);
void FUN_002c1810(void) {
    *(int *)((char *)(DAT_00586020) + 60) = (int)&thunk_igPsx2Media_GetMetaObject;
    FUN_002fe480((int)&thunk_FUN_002ebd70);
}
