/* Release step for igDriverDatabase: run FUN_002da770 (which tail-calls with the object's word at
 * +40), then the igObject slot-10 base step. */
int FUN_002da770();
int Gap__Core__igObject__vfunc_10(int);

void Gap__Core__igDriverDatabase__vfunc_12(int self) {
    FUN_002da770();
    Gap__Core__igObject__vfunc_10(self);
}
