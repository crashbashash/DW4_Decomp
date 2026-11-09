struct StreamSlotState { char pad0[48]; int value; char pad1[18]; signed char state : 7; unsigned char flag : 1;
    int getState() const { return state; }
};
extern "C" void FUN_0020c840(StreamSlotState *s, int value) {
    if (s->getState() != 1) {
        s->state = 6;
    }
    s->value = value;
}
