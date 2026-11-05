/* 0x00328f70 — 12 bytes. Drops its own first argument and tail-calls FUN_00123730 with the remaining
 * two (retail: `move a0,a1; j FUN_00123730; move a1,a2` — C mode, not C++, gives the direct jump). */
int FUN_00123730();
void Gap__Core__igPsx2CallStackTracer__vfunc_38(int unused, int a, int b) {
    FUN_00123730(a, b);
}
