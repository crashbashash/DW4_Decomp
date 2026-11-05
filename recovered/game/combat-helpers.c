/* Complete 3fc6f0/3fc780 helper behavior; nonmatching source. */
#include "combat-helpers.h"
#include "../frontend/eefloat.h"
#include "../engine/matrix-primitives.h"
#define P(x) ((uint32_t)a->read(a->user,(x),4))
#define W(x,v) a->write(a->user,(x),4,(uint32_t)(v))
#define CALL(x,...) a->call(a->user,(x),(const uint64_t[8]){__VA_ARGS__})

void dw4_combat_find_technique_row(const Dw4MessengerResultsApi *a,uint32_t player,
                                  int32_t base_no,uint32_t output)
{
    uint32_t property=(uint32_t)CALL(0x3a9340,player,0x518928);
    uint32_t list=P(property+12);
    int32_t count=(int32_t)P(list+8),i;
    if(count>0) {
        uint32_t cursor=P(list+16);
        for(i=0;i<count;i++,cursor+=4) {
            uint32_t item=P(cursor);
            if(base_no==(int32_t)P(item+20)) {
                W(output,P(item+12));
                return;
            }
        }
    }
}

static uint32_t matrix_read(void *user,uint32_t address)
{
    const Dw4MessengerResultsApi *a=user;
    return P(address);
}
static void matrix_write(void *user,uint32_t address,uint32_t value)
{
    const Dw4MessengerResultsApi *a=user;
    W(address,value);
}

uint32_t dw4_combat_collect_nearby(const Dw4MessengerResultsApi *a,uint32_t output,
                                  uint32_t self,uint32_t group,int32_t excluded,
                                  uint32_t center,uint32_t frame)
{
    uint32_t allocator=(uint32_t)CALL(0x301000,self);
    uint32_t list,matrix=frame+0xb0,vector=frame+0xf0,i;
    int32_t count;
    Dw4MatrixApi matrices={(void *)a,matrix_read,matrix_write};
    if(!a->read(a->user,0x554c14,1))
        allocator=(uint32_t)CALL(0x2f88e0,P(0x587110));
    list=(uint32_t)CALL(0x2caa70,allocator);
    CALL(0x38e670,P(self+20),group,0x519030);
    count=(int32_t)CALL(0x38f240,P(self+20));
    for(i=0;(int32_t)i<count;i++) {
        uint32_t id=(uint32_t)CALL(0x38f320,P(self+20),i);
        if(id!=(uint32_t)excluded) {
            uint32_t x,y,z,distance;
            CALL(0x38f630,matrix,P(self+20),i);
            dw4_matrix_get_translation(&matrices,matrix,vector);
            W(vector,ee_f32_sub(P(vector),P(center)));
            W(vector+4,ee_f32_sub(P(vector+4),P(center+4)));
            W(vector+8,ee_f32_sub(P(vector+8),P(center+8)));
            y=ee_f32_mul(P(vector+4),P(vector+4));
            x=ee_f32_mul(P(vector),P(vector));
            z=P(vector+8);
            distance=ee_f32_add(ee_f32_add(x,y),ee_f32_mul(z,z));
            if(ee_f32_cmp(distance,0x44610000)<0) {
                CALL(0x38ed70,P(self+20));
                CALL(0x38d860,P(self+20),group,0,id);
                CALL(0x38f0e0,P(self+20),1);
                CALL(0x38e060,P(self+20),0x519040);
                if((int32_t)CALL(0x38f320,P(self+20),0)!=0) {
                    uint32_t index=P(list+8);
                    if((int32_t)index<(int32_t)P(list+12)) W(list+8,P(list+8)+1);
                    else CALL(0x2d6790,list,index+1,4);
                    W(P(list+16)+index*4,id);
                }
                CALL(0x38ef50,P(self+20));
            }
        }
    }
    W(output,list);
    {
        uint32_t retained=P(output);
        if(retained) W(retained+4,P(retained+4)+1);
    }
    if(list) {
        W(list+4,P(list+4)-1);
        if(!(P(list+4)&0x7fffff)) CALL(0x2ff820,list);
    }
    return 0;
}
