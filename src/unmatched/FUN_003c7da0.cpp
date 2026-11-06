/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c7ef0();

void FUN_003c7da0(int arg0) {
    FUN_003c7ef0();
    igMetaObject_CreateInstance(*(int *)0x58BEF0, arg0);
}
} /* extern "C" */
