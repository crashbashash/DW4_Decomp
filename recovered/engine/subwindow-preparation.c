/* Complete original SUBWND work ownership, record caps and stock preparation.
 * This guest-memory reference preserves service calls and reference lifetimes;
 * it is not an exact compiler unit or a host shop implementation. See finding907.
 */
#include "subwindow-preparation.h"
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define B(p) ((uint32_t)a->read(a->user,(p),1))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define SB(p,v) a->write(a->user,(p),1,(uint8_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
static uint64_t word(uint32_t x){return (uint64_t)(int64_t)(int32_t)x;}
static void release(const Dw4MessengerResultsApi*a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,word(p));}}
static uint64_t allocator(const Dw4MessengerResultsApi*a,uint64_t owner,uint32_t selector){
    uint64_t p=CALL(0x301000,owner);
    if(!B(0x554c14))p=CALL(0x2f88e0,word(P(selector)));
    return p;
}
static uint64_t player(const Dw4MessengerResultsApi*a,uint32_t owner,unsigned index){
    CALL(0x38e5d0,word(P(owner+20)),0x516848);CALL(0x38f250,word(P(owner+20)),index);
    CALL(0x38e060,word(P(owner+20)),0x516850);return CALL(0x38f800,word(P(owner+20)),0);
}
static void cap(const Dw4MessengerResultsApi*a,uint64_t folder,uint32_t key,int32_t limit){
    uint32_t p=(uint32_t)CALL(0x3a9220,folder,key);
    if((int32_t)P(p+12)>limit){p=(uint32_t)CALL(0x3a9220,folder,key);W(p+12,(uint32_t)limit);}
}
static unsigned level_row(int32_t level,unsigned maximum){
    static const int cut[]={10,17,22,27,32,37,42,47,52,61,68,73,78,83,88,93,98,103,108,113,118,128,138,148,158,168,178,188,198};
    unsigned row=0;while(row<maximum&&level>=cut[row])row++;return row;
}
static int investment_row(int32_t value){
    static const int cut[]={1000,6000,26000,86000,206000,456000,956000,1956000,3956000};
    int row=-1;while(row<8&&value>=cut[row+1])row++;return row;
}
static uint64_t database(const Dw4MessengerResultsApi*a,uint32_t owner,uint32_t name){
    CALL(0x38e5f0,word(P(owner+20)),0x516980,name,0,0x516998);
    return CALL(0x38f800,word(P(owner+20)),0);
}
static void clear_stock(const Dw4MessengerResultsApi*a,uint32_t work,unsigned field){
    uint32_t list=P(work+field);
    if((int32_t)P(list+8)<37)CALL(0x2d6680,word(list),36,4);
    CALL(0x301c90,word(P(work+field)),0);
}
static void column(const Dw4MessengerResultsApi*a,uint32_t buffer,unsigned index){
    SB(buffer,index/10+'0');SB(buffer+1,index%10+'0');SB(buffer+2,0);
}
static void append_item(const Dw4MessengerResultsApi*a,uint32_t work,unsigned field,uint64_t owner,
                        uint32_t temp,uint64_t id,uint32_t level,unsigned kind){
    static const uint32_t factories[]={0x3c8c90,0x3c8b00,0x3c8970,0x3c87f0};
    static const uint32_t initializers[]={0x4482e0,0x448430,0x448580,0x448660};
    W(temp,CALL(factories[kind],allocator(a,owner,0x587108)));
    if(kind==3)CALL(initializers[kind],word(P(temp)),id);
    else CALL(initializers[kind],word(P(temp)),id,owner,word(level));
    CALL(0x301e30,word(P(work+field)),word(P(temp)));release(a,P(temp));
}
uint64_t dw4_subwindow_preparation(const Dw4MessengerResultsApi*a,const uint64_t v[8],uint32_t scratch){
    uint32_t owner=(uint32_t)v[0],ram=(uint32_t)v[1],work=P(ram+44);
    if(!work){
        W(scratch+220,CALL(0x3b5ec0,allocator(a,v[0],0x587110)));
        uint32_t made=P(scratch+220);if(made)W(made+4,P(made+4)+1);
        release(a,P(ram+44));W(ram+44,made);work=P(ram+44);release(a,P(scratch+220));
    }
    /* Cap only joined players, but always use player zero for stock level. */
    unsigned joined=0;
    for(unsigned i=0;i<4;i++){
        uint64_t folder=player(a,owner,i);uint32_t use=(uint32_t)CALL(0x3a9280,folder,0x516860);
        if(B(use+12)){joined++;cap(a,folder,0x516ad8,9999999);cap(a,folder,0x516ac8,9999);}
    }
    uint64_t folder=player(a,owner,0);uint32_t value=(uint32_t)CALL(0x3a9220,folder,0x516960);
    uint32_t level=P(value+12),mode=P(owner+40);
    /* Populated work lists persist across reopen; do not silently refresh. */
    if(mode==9){
        CALL(0x38e670,word(P(owner+20)),0x516848,0x516b80);
        uint64_t common=CALL(0x38f800,word(P(owner+20)),0);
        uint32_t property=(uint32_t)CALL(0x3a9250,common,0x516b90);
        uint32_t invested=P(P(P(property+12)+16)+4);int row=investment_row((int32_t)invested);
        if((int32_t)P(P(work+28)+8)<1){
            W(work+32,invested);clear_stock(a,work,28);
            if(row!=-1){
                uint64_t data=database(a,owner,0x516b98);
                for(unsigned i=0;i<36;i++){
                    column(a,scratch+160,i);
                    uint64_t id=CALL(0x3a9460,data,word((uint32_t)row),scratch+160);
                    if(id!=UINT64_MAX){
                        CALL(0x12a1e8,scratch+160,0x516ba8);
                        uint64_t kind=CALL(0x3a9460,data,word((uint32_t)row),scratch+160);
                        if(kind==2)append_item(a,work,28,v[0],scratch+192,id,level,2);
                        else if(kind==1)append_item(a,work,28,v[0],scratch+196,id,level,1);
                        else if(kind==0)append_item(a,work,28,v[0],scratch+200,id,level,0);
                    }
                }
            }
        }
    }else if(mode==8){
        if((int32_t)P(P(work+24)+8)<1){
            clear_stock(a,work,24);unsigned row=level_row((int32_t)level,29);
            uint64_t data=database(a,owner,0x516b70);
            for(unsigned i=0;i<36;i++){
                column(a,scratch+168,i);uint64_t id=CALL(0x3a9460,data,row,scratch+168);
                if(id==UINT64_MAX)CALL(0x301e30,word(P(work+24)),0);
                else append_item(a,work,24,v[0],scratch+204,id,level,3);
            }
        }
    }else if(mode==7){
        if((int32_t)P(P(work+20)+8)<1){
            clear_stock(a,work,20);unsigned row=level_row((int32_t)level,29);
            uint64_t data=database(a,owner,0x516b60);
            /* Retail constructs blue armor even for the missing-entry sentinel. */
            for(unsigned i=0;i<12;i++){
                column(a,scratch+176,i);uint64_t id=CALL(0x3a9460,data,row,scratch+176);
                append_item(a,work,20,v[0],scratch+212,id,level,1);
            }
            for(unsigned i=12;i<36;i++){
                column(a,scratch+176,i);uint64_t id=CALL(0x3a9460,data,row,scratch+176);
                if(id==UINT64_MAX)CALL(0x301e30,word(P(work+20)),0);
                else append_item(a,work,20,v[0],scratch+208,id,level,2);
            }
        }
    }else if(mode==6&&(int32_t)P(P(work+16)+8)<1){
        clear_stock(a,work,16);unsigned base=150;
        if(joined<2){
            uint32_t property=(uint32_t)CALL(0x3a9220,folder,0x5169a8);
            switch(P(property+12)){
            case 1:case 4:case 12:base=25;break;
            case 2:case 7:case 14:base=50;break;
            case 3:case 9:base=75;break;
            case 6:case 10:base=100;break;
            case 8:case 11:case 13:base=125;break;
            default:base=0;break;
            }
        }
        unsigned row=base+level_row((int32_t)level,24);
        uint64_t data=database(a,owner,0x516b50);
        for(unsigned i=0;i<36;i++){
            column(a,scratch+184,i);uint64_t id=CALL(0x3a9460,data,row,scratch+184);
            if(id==UINT64_MAX)CALL(0x301e30,word(P(work+16)),0);
            else append_item(a,work,16,v[0],scratch+216,id,level,0);
        }
    }
    return 0;
}
