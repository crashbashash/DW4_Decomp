typedef void (*ConvertFunc)(void);

void FUN_0015aaf0(void);
void FUN_0015ab50(void);
void FUN_0015ab70(void);
void FUN_0015ab90(void);
void FUN_0016f690(void);
void FUN_0016f700(void);
void FUN_0016f780(void);
void FUN_0016f7f0(void);
void FUN_0016f8a0(void);
void FUN_0016f930(void);
void FUN_0016f9b0(void);
void FUN_0016fa10(void);
void FUN_0016fa60(void);
void FUN_0016fae0(void);
void FUN_0016fb60(void);
void FUN_0016fbd0(void);
void FUN_0016fc20(void);
void FUN_0016fc80(void);
void FUN_0016fcd0(void);
void thunk_memcpy(void);
void FUN_0016fd50(void);
void FUN_0016fdb0(void);
void FUN_0016fe00(void);
void FUN_0016fe20(void);

/* matching construct: a small sweep of spellings */
ConvertFunc Gap__Gfx__igPsx2ImageConvert__vfunc_24(void *self, int srcFormat, int from, int to)
{
    switch (from) {
    case 0x10001:
        switch (to) {
        case 0x10000: return FUN_0015ab90;
        case 0x10001: break;
        }
        break;
    case 0x10000:
        switch (to) {
        case 0x10001: return FUN_0015aaf0;
        case 7: return FUN_0016f690;
        case 0x10000: break;
        }
        break;
    case 6:
        break;
    case 4:
        break;
    case 8:
        switch (to) {
        case 7: return FUN_0016f700;
        case 8: break;
        }
        break;
    case 10:
        switch (to) {
        case 5: return FUN_0016f780;
        case 10: break;
        }
        break;
    case 9:
        switch (to) {
        case 7: return FUN_0016f7f0;
        case 9: break;
        }
        break;
    case 11:
        break;
    case 5:
        switch (to) {
        case 7: return FUN_0016f8a0;
        case 8: return FUN_0016f930;
        case 10: return FUN_0016f9b0;
        case 5: break;
        }
        break;
    case 7:
        switch (to) {
        case 5: return FUN_0016fa10;
        case 8: return FUN_0016fa60;
        case 9: return FUN_0016fae0;
        case 7: break;
        }
        break;
    case 0:
        switch (to) {
        case 1: return FUN_0015ab70;
        case 0x10000: return FUN_0016fe00;
        case 0: break;
        }
        break;
    case 1:
        switch (to) {
        case 0: return FUN_0015ab50;
        case 0x10000: return FUN_0016fe20;
        case 0x10001: return FUN_0016fdb0;
        case 1: break;
        }
        break;
    case 3:
        switch (to) {
        case 7: return FUN_0016fc20;
        case 2: return FUN_0016fbd0;
        case 0x10000: return FUN_0016fc80;
        case 0x10001: return FUN_0016fcd0;
        case 3: break;
        }
        break;
    case 2:
        switch (to) {
        case 3: return FUN_0016fb60;
        case 0x10000: return thunk_memcpy;
        case 0x10001: return FUN_0016fd50;
        case 2: break;
        }
        break;
    }
    return 0;
}
