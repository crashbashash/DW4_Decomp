extern "C" int __register_global_object(...);
extern "C" int DAT_005878c8[4];
extern "C" int DAT_005878d8[4];
extern "C" int FUN_00338e50(...);

extern "C" void FUN_005216a0(void) {
    DAT_005878d8[0] = 0;
    __register_global_object(&DAT_005878d8[0], &FUN_00338e50, &DAT_005878c8[0]);
}
