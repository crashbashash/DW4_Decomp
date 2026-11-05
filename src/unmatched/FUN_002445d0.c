typedef struct Nd { int p0; struct Nd *next; } Nd;
typedef struct It { int p0; Nd *cur; unsigned int idx; } It;
extern unsigned int DAT_004986a8[4];
extern Nd **DAT_0056dea8[4];
It *FUN_002445d0(It *it) {
    it->cur = it->cur->next;
    if (it->cur != 0) {
    } else {
        while (it->cur == 0 && it->idx < DAT_004986a8[0]) {
            it->cur = ((Nd **)DAT_0056dea8[0])[it->idx++];
        }
    }
    return it;
}
