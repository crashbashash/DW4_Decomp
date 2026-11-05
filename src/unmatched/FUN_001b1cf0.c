#include "dw4/reflected.h"
int memset();

void FUN_001b1cf0(igDataList *arg0) {
    unsigned int temp_a2;
    int *temp_a0;

    temp_a2 = arg0->_count;
    temp_a0 = (int *)arg0->_data;
    switch (temp_a2) {
    case 16:
        temp_a0[15] = -1;
        
    case 15:
        temp_a0[14] = -1;
        
    case 14:
        temp_a0[13] = -1;
        
    case 13:
        temp_a0[12] = -1;
        
    case 12:
        temp_a0[11] = -1;
        
    case 11:
        temp_a0[10] = -1;
        
    case 10:
        temp_a0[9] = -1;
        
    case 9:
        temp_a0[8] = -1;
        
    case 8:
        temp_a0[7] = -1;
        
    case 7:
        temp_a0[6] = -1;
        
    case 6:
        temp_a0[5] = -1;
        
    case 5:
        temp_a0[4] = -1;
        
    case 4:
        temp_a0[3] = -1;
        
    case 3:
        temp_a0[2] = -1;
        
    case 2:
        temp_a0[1] = -1;
        
    case 1:
        temp_a0[0] = -1;
        break;
    case 0:
        break;
    default:
        memset(temp_a0, 0xFF, temp_a2 * 4);
        break;
    }
}
