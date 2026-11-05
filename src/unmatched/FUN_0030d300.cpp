extern "C" int FUN_0030d230(int, int);
extern "C" int FUN_0030d350();
extern "C" int FUN_0030d300(int arg0, int arg1) {
    int r = FUN_0030d350();
    if (r != -1) return r;
    return FUN_0030d230(arg0, arg1);
}
