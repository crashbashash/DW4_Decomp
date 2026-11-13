long long Gap__Core__igPsx2LongTimer__vfunc_37(void) {
    long long rawTime;

    p2ReadNanoseconds(&rawTime);
    return rawTime;
}

int Gap__Core__igPsx2LongTimer__vfunc_24(void) {
    return 0x6C;
}

void FUN_0032dae0(void) {
    GPR_00554ddc = 1;
    p2InitTimer();
}

void FUN_0032daf0(void) {
    FUN_0032dae0();
}

