/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003ca480();

void FUN_003ca380(int arg0) {
    FUN_003ca480();
    igMetaObject_CreateInstance(*(int *)0x58C108, arg0);
}
} /* extern "C" */
