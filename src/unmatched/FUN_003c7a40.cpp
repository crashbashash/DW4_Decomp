/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c7b60();

void FUN_003c7a40(int arg0) {
    FUN_003c7b60();
    igMetaObject_CreateInstance(*(int *)0x58BEB0, arg0);
}
} /* extern "C" */
