struct Obj { virtual int a0(int, int); virtual int a1(int, int); virtual int a2(int, int); virtual int a3(int, int); virtual int a4(int, int); virtual int a5(int, int); virtual int a6(int, int); virtual int a7(int, int); virtual int a8(int, int); virtual int a9(int, int); virtual int a10(int, int); virtual int a11(int, int); virtual int a12(int, int); virtual int a13(int, int); virtual int a14(int, int); virtual int a15(int, int); virtual int a16(int, int); virtual int a17(int, int); virtual int a18(int, int); virtual int a19(int, int); virtual int a20(int, int); virtual int a21(int, int); virtual int a22(int, int); virtual int a23(int, int); virtual int a24(int, int); virtual int a25(int, int); virtual int a26(int, int); virtual int a27(int, int); virtual int a28(int, int); virtual int a29(int, int); virtual int a30(int, int); virtual int a31(int, int); virtual int a32(int, int); virtual int a33(int, int); virtual int a34(int, int); virtual int a35(int, int); virtual int a36(int, int); virtual int a37(int, int); virtual int a38(int, int); virtual int a39(int, int); virtual int a40(int, int); virtual int v41(int, int); };
struct List { int pad[2]; int count; int pad2; Obj **arr; };
struct Self { char pad[52]; List *list; };
extern "C" { int FUN_002d55a0(Self *arg0, int arg1, int arg2); }
int FUN_002d55a0(Self *arg0, int arg1, int arg2) {
    int sum = 0;
    int i;
    for (i = 0; i < arg0->list->count; i++) {
        sum += arg0->list->arr[i]->v41(arg1, arg2);
    }
    return sum;
}
