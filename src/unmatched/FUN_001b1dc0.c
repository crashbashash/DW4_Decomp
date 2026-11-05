#include "dw4/reflected.h"
int memset();

void FUN_001b1dc0(igDataList *arg0) {
    unsigned int temp_a2;
    int *temp_a0;

    temp_a2 = arg0->_count;
    temp_a0 = (int *)(arg0->_data);
    switch (temp_a2) {
    case 16:
        temp_a0[15] = 0;
        
    case 15:
        temp_a0[14] = 0;
        
    case 14:
        temp_a0[13] = 0;
        
    case 13:
        temp_a0[12] = 0;
        
    case 12:
        temp_a0[11] = 0;
        
    case 11:
        temp_a0[10] = 0;
        
    case 10:
        temp_a0[9] = 0;
        
    case 9:
        temp_a0[8] = 0;
        
    case 8:
        temp_a0[7] = 0;
        
    case 7:
        temp_a0[6] = 0;
        
    case 6:
        temp_a0[5] = 0;
        
    case 5:
        temp_a0[4] = 0;
        
    case 4:
        temp_a0[3] = 0;
        
    case 3:
        temp_a0[2] = 0;
        
    case 2:
        temp_a0[1] = 0;
        
    case 1:
        temp_a0[0] = 0;
    case 0:
        break;
    default:
        memset(temp_a0, 0, temp_a2 * 4);
        break;
    }
}
