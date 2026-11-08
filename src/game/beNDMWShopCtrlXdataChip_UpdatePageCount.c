/* Chip list pagination: refresh maximum pages and return current row count. */
#include "dw4/reflected.h"
int beNDMWShopCtrlXdataChip_UpdatePageCount(beNDMWShopCtrlXdataChip *self){
    int count=((igObjectList *)self->_itemBaseList)->_count,pages,remaining,result;
    if(count%12)pages=count/12+1;
    else pages=count/12;
    self->_maxPage=pages;
    remaining=(int)((unsigned)((igObjectList *)self->_itemBaseList)->_count-(unsigned)self->_nowPage*12);
    if(remaining>=12){
        result=12;
    }
    else result=remaining%12;
    if(result<1){result=1;}
    return result;
}
