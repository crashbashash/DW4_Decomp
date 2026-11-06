/* Clears the two pending-request flags at +0xA18/+0xA1C once FUN_0029e2d0/FUN_0029e2b0 report the
 * channel idle, then forwards both to FUN_002ace60. */
int FUN_0029e2b0(int obj, int channel);
int FUN_0029e2d0(int obj, int channel);
void FUN_002ace60(int obj, int request1, int request2);

struct PendingPair {
    char pad0[20];
    int request1; /* +20 */
    int request2; /* +24 */
};

void FUN_002aab90(int obj) {
    struct PendingPair *pending = (struct PendingPair *)(obj + 0xA04);

    if (pending->request1 == 1 && FUN_0029e2d0(obj, 1) == 0 && FUN_0029e2b0(obj, 1) == 0) {
        pending->request1 = 0;
    }
    if (pending->request2 == 1 && FUN_0029e2d0(obj, 2) == 0 && FUN_0029e2b0(obj, 2) == 0) {
        pending->request2 = 0;
    }
    FUN_002ace60(obj, pending->request1, pending->request2);
}
