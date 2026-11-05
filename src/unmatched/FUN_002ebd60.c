/* 0x002ebd60 - FUN_002ebd60. Near-miss sweep fix, verified byte-identical to retail by tools/verify.py. */
int ObjectList_AppendRetained();
extern int DAT_00586f40[4];
void FUN_002ebd60(int arg0) {
    ObjectList_AppendRetained(DAT_00586f40[0], arg0);
}
