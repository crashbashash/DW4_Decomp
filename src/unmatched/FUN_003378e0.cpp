/* Compiled as C++ so the call stays a real jal; C would turn it into a tail jump. */
extern "C" {
int FUN_00337630(int, int, int, int, int, int, int, int);
void FUN_003378e0(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
}
void FUN_003378e0(int a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    FUN_00337630(a0, a1, 0x400, a2, a3, a4, a5, a6);
}
