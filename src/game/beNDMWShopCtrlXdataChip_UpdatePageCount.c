/* Chip list pagination: refresh maximum pages and return current row count. Two original NOPs plus
 * balanced assembler scheduling directives preserve the conditional branches. -O3,p reproduces
 * constant-division lowering. */
#include "dw4/reflected.h"
int beNDMWShopCtrlXdataChip_UpdatePageCount(beNDMWShopCtrlXdataChip *self){
    int count=((igObjectList *)self->_itemBaseList)->_count,pages,remaining,result;
    if(count%12)pages=count/12+1;
    else pages=count/12;
    self->_maxPage=pages;
    remaining=(int)((unsigned)((igObjectList *)self->_itemBaseList)->_count-(unsigned)self->_nowPage*12);
    asm { .set noreorder }
    if(remaining>=12){
        asm { nop
            .set reorder }
        result=12;
    }
    else result=remaining%12;
    if(result<1){result=1;asm { nop }}
    return result;
}
