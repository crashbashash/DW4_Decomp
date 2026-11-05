/* Behavioral recovery of 0038d470..0038e6b0. This does not claim a compiler
 * match. List, registry, allocator, intern and receiver callbacks are leaves. */
#include "messenger-dispatch.h"
typedef const Dw4MessengerResultsApi *Api;
static uint32_t r(Api a,uint32_t p){return (uint32_t)a->read(a->user,p,4);}
static unsigned b(Api a,uint32_t p){return (unsigned)a->read(a->user,p,1);}
static void w(Api a,uint32_t p,uint32_t v){a->write(a->user,p,4,v);}
static uint64_t call(Api a,uint32_t e,uint64_t x,uint64_t y,uint64_t z,uint64_t q,uint64_t t){
    uint64_t args[8]={x,y,z,q,t,0,0,0};return a->call(a->user,e,args);
}
static void retain(Api a,uint32_t p){if(p)w(a,p+4,r(a,p+4)+1);}
static void release(Api a,uint32_t p){
    if(p){w(a,p+4,r(a,p+4)-1);if(!(r(a,p+4)&0x7fffff))call(a,0x2ff820,p,0,0,0,0);}
}
static void unstring(Api a,uint32_t p){
    if(p){uint32_t n=r(a,p-4)-1;w(a,p-4,n);if(!n)call(a,0x30c940,r(a,p-8),p-8,0,0,0);}
}
static uint32_t intern(Api a,uint32_t p){
    uint32_t pool=r(a,0x586f20);
    if(!pool){pool=(uint32_t)call(a,0x2eb010,16,0,0,0,0);if(pool)pool=(uint32_t)call(a,0x2eadf0,pool,0,0,0,0);w(a,0x586f20,pool);}
    return (uint32_t)call(a,0x2eaf60,r(a,0x586f20),p,0,0,0);
}
static void assign_string(Api a,uint32_t slot,uint32_t text){
    uint32_t value=intern(a,text);unstring(a,r(a,slot));w(a,slot,value);
}
static uint32_t item(Api a,uint32_t list,int32_t index){return r(a,r(a,list+16)+(uint32_t)index*4);}
static void append(Api a,uint32_t list,uint32_t value,unsigned stride){
    int32_t n=(int32_t)r(a,list+8);
    if(n<(int32_t)r(a,list+12))w(a,list+8,r(a,list+8)+1);
    else call(a,0x2d6790,list,(uint32_t)n+1,stride,0,0);
    a->write(a->user,r(a,list+16)+(uint32_t)n*stride,stride,value);
}
static void prepare(Api a,uint32_t self){
    if(!b(a,self+48))call(a,0x38bee0,self,0,0,0,0);
    else call(a,0x38ca40,r(a,self+16),0,0,0,0);
}
static void promote(Api a,uint32_t self,int32_t index,uint32_t owner,uint32_t scratch){
    uint32_t list=r(a,self+24);release(a,item(a,list,index));
    call(a,0x2d6cf0,list,(uint32_t)index,0,0,0);
    w(a,r(a,list+16)+r(a,list+8)*4,0);
    w(a,scratch,owner);list=r(a,self+24);retain(a,owner);
    call(a,0x2d6b80,list,0,1,scratch,0);
}
static void select_receivers(Api a,uint32_t self,uint32_t category,uint32_t name,uint32_t id,uint32_t scratch){
    int found=0;prepare(a,self);
    int32_t count=(int32_t)r(a,r(a,self+24)+8);
    for(int32_t i=0;i<count;i++){
        uint32_t row=item(a,r(a,self+24),i);retain(a,row);
        if(r(a,row+8)&&!call(a,0x12a4a4,r(a,row+8),category,0,0,0)){
            uint32_t old=r(a,row+12);
            int same=(!old||!name)?old==name:!call(a,0x12a4a4,old,name,0,0,0);
            if(same){w(a,row+16,id);if(i)promote(a,self,i,row,scratch);found=1;release(a,row);break;}
        }
        release(a,row);
    }
    if(!found){
        uint32_t list=r(a,self+24),row=item(a,list,(int32_t)r(a,list+8)-1);retain(a,row);
        assign_string(a,row+8,category);assign_string(a,row+12,name);w(a,row+16,id);
        uint32_t ids=r(a,row+24);w(a,ids+8,0);
        if((int32_t)r(a,ids+12)>4&&(int32_t)r(a,ids+8)<5)call(a,0x2d6680,ids,4,4,0,0);
        uint32_t receivers=r(a,row+28);int32_t n=(int32_t)r(a,receivers+8);
        for(int32_t i=0;i<n;i++)release(a,item(a,receivers,i));
        /* Count and backing pointer are re-read after destructor callbacks. */
        n=(int32_t)r(a,receivers+8);
        for(int32_t i=0;i<n;i++)w(a,r(a,receivers+16)+(uint32_t)i*4,0);
        w(a,receivers+8,0);receivers=r(a,row+28);
        if((int32_t)r(a,receivers+12)>4&&(int32_t)r(a,receivers+8)<5)call(a,0x2d6680,receivers,4,4,0,0);
        list=r(a,self+24);promote(a,self,(int32_t)r(a,list+8)-1,row,scratch);release(a,row);
    }
    uint32_t row=item(a,r(a,self+24),0);
    if(!r(a,r(a,row+28)+8)){
        uint32_t record=(uint32_t)call(a,0x3022c0,r(a,self+20),r(a,0x585be0),r(a,row+8),0,0);
        if(record){
            int32_t n=(int32_t)r(a,r(a,record+20)+8);
            for(int32_t i=0;i<n;i++){
                call(a,0x1c64e0,scratch+8,r(a,record+12),(uint32_t)i,0,0);
                uint32_t candidate=r(a,scratch+8);unstring(a,candidate);
                uint32_t filter=r(a,row+12);
                if(!filter||!candidate||!call(a,0x12a4a4,filter,candidate,0,0,0)){
                    uint32_t source=r(a,r(a,record+16)+16);
                    append(a,r(a,row+24),r(a,source+(uint32_t)i*4),4);
                    call(a,0x301e30,r(a,row+28),item(a,r(a,record+20),i),0,0,0);
                }
            }
        }
    }
}
static void dispatch(Api a,uint32_t self,uint32_t key,uint32_t scratch){
    uint32_t row=item(a,r(a,self+24),0);assign_string(a,row+20,key);
    int32_t n=(int32_t)r(a,r(a,row+28)+8);
    if(!call(a,0x12a4a4,key,0x50ee10,0,0,0)){
        uint32_t hits=0;
        for(int32_t i=0;i<n;i++){
            uint32_t id=item(a,r(a,row+24),i),filter=r(a,row+16);
            if(filter==0xffffffff||id==0xffffffff||id==filter)hits++;
        }
        append(a,r(a,r(a,self+16)+16),b(a,hits?0x5549d4:0x5549d8),1);
        append(a,r(a,r(a,self+16)+20),hits?hits:r(a,0x4c8f88),4);
    }else if(!call(a,0x12a4a4,key,0x50ee18,0,0,0)){
        w(a,scratch,0);
        /* This query intentionally ignores numeric filtering and context state. */
        uint32_t data=r(a,r(a,row+28)+16);
        for(int32_t i=0;i<n;i++){
            uint32_t receiver=r(a,data+(uint32_t)i*4);
            if(!b(a,receiver+20)){retain(a,receiver);w(a,scratch,receiver);break;}
        }
        uint32_t receiver=r(a,scratch);
        if(receiver)call(a,0x301e30,r(a,r(a,self+16)+40),receiver,0,0,0);
        release(a,r(a,scratch));
    }else{
        for(int32_t i=0;i<n;i++){
            uint32_t receiver=item(a,r(a,row+28),i),filter=r(a,row+16);
            int accept;
            if(filter==0xfffffffe)accept=!b(a,receiver+20);
            else{
                uint32_t id=item(a,r(a,row+24),i);
                accept=(b(a,r(a,self+16)+8)!=1||b(a,receiver+20))&&
                       (filter==0xffffffff||id==0xffffffff||id==filter);
            }
            if(accept){
                uint32_t obj=r(a,receiver+16);
                if(!(call(a,r(a,r(a,obj)+144),obj,receiver,row,0,0)&255))
                    call(a,r(a,r(a,obj)+140),obj,receiver,key,0,0);
                if(r(a,row+16)==0xfffffffe)return;
            }
        }
    }
}
uint64_t dw4_messenger_dispatch(Api a,uint32_t entry,const uint64_t args[8],uint32_t scratch){
    uint32_t self=(uint32_t)args[0],x=(uint32_t)args[1],y=(uint32_t)args[2],z=(uint32_t)args[3],t=(uint32_t)args[4];
    switch(entry){
    case 0x38d470:
        a->write(a->user,self+40,8,args[1]?a->read(a->user,r(a,self+12)+80,8):0);break;
    case 0x38d4a0:
        if(r(a,0x58a4e0)==x&&!call(a,0x12a4a4,0x58a4f0,y,0,0,0))return (uint64_t)(int64_t)(int32_t)r(a,0x58a530);
        call(a,0x2fba30,scratch,x,y,scratch+4,0);
        if(r(a,scratch)!=r(a,0x4fb410))return UINT64_MAX;
        w(a,0x58a4e0,x);call(a,0x12a5fc,0x58a4f0,y,0,0,0);w(a,0x58a530,r(a,scratch+4));
        return (uint64_t)(int64_t)(int32_t)r(a,scratch+4);
    case 0x38d560:{
        uint32_t record=(uint32_t)call(a,0x3022c0,r(a,self+20),r(a,0x585be0),y,0,0);retain(a,record);
        if(!record){
            uint32_t alloc=(uint32_t)call(a,0x301000,self,0,0,0,0);
            if(!b(a,0x554c14))alloc=(uint32_t)call(a,0x2f88e0,r(a,0x587110),0,0,0,0);
            release(a,record);record=(uint32_t)call(a,0x3584e0,alloc,0,0,0,0);
            call(a,0x2fecb0,record,y,0,0,0);call(a,0x301e30,r(a,self+20),record,0,0,0);
        }
        call(a,0x301e30,r(a,record+20),x,0,0,0);
        w(a,scratch,z?intern(a,z):0);call(a,0x1ca620,r(a,record+12),scratch,0,0,0);
        unstring(a,r(a,scratch));append(a,r(a,record+16),t,4);release(a,record);break;
    }
    case 0x38d7a0:case 0x38e530:
        if(args[0]){release(a,r(a,self));if((int16_t)x>0)call(a,0x100610,args[0],0,0,0,0);}return args[0];
    case 0x38d820:{
        uint32_t name=r(a,r(a,x+12)+8);uint64_t next[8]={args[0],args[1],args[2],name?name:0x4e0858,r(a,x+8),0,0,0};
        dw4_messenger_dispatch(a,0x38d560,next,scratch);break;
    }
    case 0x38d860:select_receivers(a,self,x,y,z,scratch);break;
    case 0x38e060:dispatch(a,self,x,scratch);break;
    case 0x38e5b0:select_receivers(a,self,x,0,y,scratch);break;
    case 0x38e5d0:select_receivers(a,self,x,0,0xffffffff,scratch);break;
    case 0x38e5f0:select_receivers(a,self,x,y,z,scratch);dispatch(a,self,t,scratch);break;
    case 0x38e630:select_receivers(a,self,x,0,y,scratch);dispatch(a,self,z,scratch);break;
    case 0x38e670:select_receivers(a,self,x,0,0xffffffff,scratch);dispatch(a,self,y,scratch);break;
    case 0x38e6b0:{
        prepare(a,self);uint32_t list=r(a,self+28),row=item(a,list,(int32_t)r(a,list+8)-1);retain(a,row);
        if(b(a,row+8)){
            uint32_t alloc=(uint32_t)call(a,0x301000,args[0],0,0,0,0);
            if(!b(a,0x554c14))alloc=(uint32_t)call(a,0x2f88e0,r(a,0x587110),0,0,0,0);
            release(a,row);row=(uint32_t)call(a,0x358950,alloc,0,0,0,0);call(a,0x301e30,r(a,self+28),row,0,0,0);
        }
        assign_string(a,row+24,x);assign_string(a,row+28,y);w(a,row+32,z);release(a,row);break;
    }
    default:return UINT64_MAX;
    }
    return 0; /* void entries have no defined integer return value. */
}
