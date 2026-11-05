/* 0x00315050 - FUN_00315050. Unlinks every list node in [lo, hi) from 95 intrusive doubly linked lists (head table at base+72, 20 bytes apart); the link pair sits at +4 or +12 depending on the top bit of the node's byte 3 (`b7 == 0 ? 4 : 12` gives the movn form). Alternate compiler -O4. */
#include "dw4/reflected.h"
struct F { char pad[3]; unsigned char b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1; };
#define OFF(p) (((struct F *)(p))->b7 == 0 ? 4 : 12)
#define NEXT(p) (*(int *)((char *)(p) + OFF(p) + 4))
#define PREV(p) (*(int *)((char *)(p) + OFF(p)))
extern int DAT_004fb410[4];
void FUN_00315050(int *arg0, igArenaMemoryPool *arg1, unsigned int arg2, unsigned int arg3) {
    char *base;
    int i;
    char *head;
    unsigned int cur;
    int prev;
    base = (char *)arg1->_arenaState;
    head = base + 72;
    for (i = 1; i < 96; i++, head += 20) {
        cur = NEXT(head);
        while (cur != (unsigned)head) {
            if (cur >= arg2 && cur < arg3) {
                prev = PREV(cur);
                cur = NEXT(cur);
                NEXT(prev) = cur;
                PREV(cur) = prev;
            } else {
                cur = NEXT(cur);
            }
        }
    }
    cur = *(unsigned *)(base + 48);
    if (cur != 0 && cur >= arg2 && cur < arg3) {
        *(int *)(base + 48) = 0;
    }
    *arg0 = DAT_004fb410[0];
}
