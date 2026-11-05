/* 0x00366340 - FUN_00366340. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00589960[4];
int FUN_00366340(void);
}

int FUN_00366340(void) {
    if (DAT_00589960[0] == 0) {
        DAT_00589960[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00589960[0];
}
