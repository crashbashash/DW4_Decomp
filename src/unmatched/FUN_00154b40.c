int FUN_00154ad0();
typedef struct Obj { char pad[29]; unsigned char f29; } Obj;

int FUN_00154b40(Obj *arg0) {
    int temp_v0;
    if (arg0->f29 != 0) {
        temp_v0 = FUN_00154ad0();
        arg0->f29 = 0U;
        return temp_v0 & 0xFF;
    }
    return 1;
}
