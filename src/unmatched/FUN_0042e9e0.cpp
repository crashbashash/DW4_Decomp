#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, int);
int beNDMWWindow_SendModelSequence(beNDMWShopCtrlA1 *, char *, int, int *);
extern int DAT_0051b620[4];
extern int DAT_00586f20[4];
void FUN_0042e9e0(beNDMWShopCtrlA1 *arg0);
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* Returns the copied list entry through a hidden return pointer into the caller's token. */
extern "C" StringRef StringList_CopyRetained(igDataList *, int);

void FUN_0042e9e0(beNDMWShopCtrlA1 *arg0) {
    int *temp_a1_2;
    int temp_a2;
    int var_s2;
    int temp_v1_2;
    int var_s1;
    igDataList *l2;
    int temp_s5;
    int var_s4;
    int var_v0;
    int **temp_s3;
    int *temp_a0;
    int *temp_s2;
    igDataList *var_a1;
    int var_s1_2;

    var_s2 = 0;
    var_a1 = (igDataList *)arg0->_cardInfoList;
    if (0 < var_a1->_count) {
        var_s1 = 0;
        do {
            {
                StringRef name = StringList_CopyRetained(var_a1, var_s2);
                temp_a2 = *(int *)(((igDataList *)arg0->_cardRamNoList)->_data + var_s1);
                if (temp_a2 != -1) {
                    beNDMWWindow_SendModelSequence(arg0, name.p, temp_a2, &DAT_0051b620[0]);
                }
            }
            var_a1 = (igDataList *)arg0->_cardInfoList;
            var_s2 += 1;
            var_s1 += 4;
        } while (var_s2 < var_a1->_count);
    }
    temp_s5 = *(int *)&var_a1->_count;
    l2 = (igDataList *)var_a1;
    var_s4 = 0;
    if (0 < temp_s5) {
        var_s1_2 = 0;
        do {
            temp_s3 = (int **)(l2->_data + var_s1_2);
            if (DAT_00586f20[0] == 0) {
                var_v0 = FUN_002eb010(0x10);
                if (var_v0 != 0) {
                    var_v0 = StringPool_Construct(var_v0);
                }
                DAT_00586f20[0] = var_v0;
            }
            temp_s2 = (int *)StringPool_Intern(DAT_00586f20[0], 0);
            temp_a0 = *temp_s3;
            if (temp_a0 != 0) {
                temp_a1_2 = temp_a0 - 2;
                temp_v1_2 = temp_a0[-1] - 1;
                temp_a0[-1] = temp_v1_2;
                if (temp_v1_2 == 0) {
                    StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
                }
            }
            var_s4 += 1;
            *temp_s3 = temp_s2;
            var_s1_2 += 4;
        } while (var_s4 < temp_s5);
    }
    l2->_count = 0;
    ((igDataList *)arg0->_cardRamNoList)->_count = 0;
}
