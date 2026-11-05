/* 0x0030c830 - StringChunk_AllocateToken. String chunk token allocator: walk the chunk chain taking a block, growing the chain with a freshly constructed chunk; bounds test spelled limit > x so the compare fuses into the branch (sltu at); default compiler. Verified byte-identical by tools/verify.py. */
struct A { struct A *f0; int f4; int f8; int f12; };
struct C { struct A *f0; struct C *next; int f8; unsigned f12; int p16[3]; int f28; char f32; };
void *StringChunk_AllocateObject();
void *StringChunk_Construct();
int StringChunk_TakeBlock();
int StringChunk_AllocateToken(struct C *arg0, int arg1, struct C **arg2, int *arg3) {
    unsigned int var_s0; struct C *var_s1; int var_s2; unsigned int temp_s3; void *var_v0;

    temp_s3 = ((arg1 + 3) & ~3) + 8;
    var_s2 = 0;
    var_s1 = arg0;
    for (;;) {
        int temp_v0 = var_s1->f28;
        if (!(temp_v0 >= 0 && temp_s3 > (unsigned int) temp_v0)) {
            var_s2 = StringChunk_TakeBlock(var_s1, temp_s3);
        }
        if (var_s2 != 0) break;
        if (var_s1->next == 0) {
            var_s0 = arg0->f12;
            if (var_s0 < temp_s3) {
                var_s0 = temp_s3;
            }
            var_v0 = StringChunk_AllocateObject(0x24, arg0->f0->f0->f12);
            if (var_v0 != 0) {
                var_v0 = StringChunk_Construct(var_v0, var_s1, arg0->f0, var_s0);
            }
            var_s1->next = (struct C *)var_v0;
        }
        var_s1 = var_s1->next;
    }
    *arg2 = var_s1;
    var_s1->f32 = 0;
    *arg3 = var_s2;
    return var_s2 + 8;
}
