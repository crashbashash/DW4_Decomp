/* Framed call written as C++ so the receiver copy and delay slot match; verified by tools/verify.py. */
extern "C" int FUN_00236b10(int, int);

extern "C" void Gap__igMoviePlugin__vfunc_22(void *arg0, int arg1) {
    FUN_00236b10(arg1, *(int *)((char *)(arg0) + 8));
}
