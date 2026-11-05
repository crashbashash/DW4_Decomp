/* 0x00207d70 - FUN_00207d70. Runs the due timer-queue entries (those with the head's key), recycles them to the free list, then signals the semaphore if its counters differ and calls FUN_001f0310(1/2). The status block is a 32-byte struct (only two words used) so the frame matches; the loop test is `!((head != 0) ^ 1)` and the head is re-read at the top of each pass. Alternate compiler -O3. */
struct Node { int w0; struct Node *next; long long key; void (*fn)(struct Node *, int); int arg; };
extern int DAT_0056bf38[4];
extern struct Node *DAT_0056bf40[4];
extern struct Node *DAT_0056bf48[4];
extern struct Node *DAT_0056bf50[4];
extern int DAT_0056bf88[4];
int FUN_001f0310();
int iReferSemaStatus();
int iSignalSema();
void FUN_00207d70(void) {
    struct { int a; int b; int pad[6]; } loc;
    long long key;
    struct Node *n;
    if (DAT_0056bf48[0] != 0) {
        key = DAT_0056bf48[0]->key;
        while (((DAT_0056bf48[0] != 0) ^ 1) == 0 && key == DAT_0056bf48[0]->key) {
            DAT_0056bf48[0]->fn(DAT_0056bf48[0], DAT_0056bf48[0]->arg);
            n = DAT_0056bf48[0];
            if (n == DAT_0056bf40[0]) {
                DAT_0056bf40[0] = 0;
                DAT_0056bf48[0] = 0;
            } else {
                DAT_0056bf48[0] = n->next;
            }
            n->next = DAT_0056bf50[0];
            DAT_0056bf50[0] = n;
        }
    }
    DAT_0056bf38[0] = 1;
    iReferSemaStatus(DAT_0056bf88[0], &loc);
    if (loc.a != loc.b) {
        iSignalSema(DAT_0056bf88[0]);
    }
    FUN_001f0310(1);
    FUN_001f0310(2);
}
