#include "pad-manager-selection.h"
uint64_t dw4_pad_manager_selection(const Dw4MessengerResultsApi *a,
                                   uint64_t self,uint64_t player){
    uint32_t manager=(uint32_t)self,index=4;
    if(!a->read(a->user,manager+29,1)&&(int64_t)player<4)index=(uint32_t)player;
    uint32_t list=(uint32_t)a->read(a->user,manager+20,4);
    uint32_t data=(uint32_t)a->read(a->user,list+16,4);
    uint32_t pad=(uint32_t)a->read(a->user,data+index*4,4);
    return (uint64_t)(int64_t)(int32_t)pad;
}
