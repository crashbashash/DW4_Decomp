/* Complete retained-object list / property lookup group, plus name publication.
 * Behavioral reference only; compiler matching is verified separately. */
#include "object-lists.h"
typedef const Dw4MessengerResultsApi *Api;
#define P(p) ((uint32_t)a->read(a->user,(p),4))
#define W(p,v) a->write(a->user,(p),4,(uint32_t)(v))
#define CALL(e,...) a->call(a->user,(e),(const uint64_t[8]){__VA_ARGS__})
#define CORE(e,...) dw4_object_list(a,(e),(const uint64_t[8]){__VA_ARGS__})
static void retain(Api a,uint32_t p){if(p)W(p+4,P(p+4)+1);}
static void release(Api a,uint32_t p){if(p){W(p+4,P(p+4)-1);if(!(P(p+4)&0x7fffff))CALL(0x2ff820,p);}}
static uint32_t item(Api a,uint32_t list,int32_t index){return P(P(list+16)+(uint32_t)index*4);}
static int32_t find_pointer(Api a,uint32_t list,uint32_t value,int32_t start){
    for(;start<(int32_t)P(list+8);start++)if(item(a,list,start)==value)return start;
    return -1;
}
static void remove_at(Api a,uint32_t list,int32_t index){
    release(a,item(a,list,index));CALL(0x2d6cf0,list,(uint64_t)(int64_t)index);
    W(P(list+16)+P(list+8)*4,0);
}
static uint64_t word(uint32_t n){return (uint64_t)(int64_t)(int32_t)n;}
uint64_t dw4_object_list(Api a,uint32_t entry,const uint64_t v[8]){
    uint32_t self=(uint32_t)v[0],value=(uint32_t)v[1],other=(uint32_t)v[2];
    int32_t n,i,index;
    switch(entry){
    case 0x301c90:
        n=(int32_t)P(self+8);
        if(v[1])for(i=0;i<n;i++)retain(a,value);
        for(i=0;i<n;i++)release(a,item(a,self,i));
        n=(int32_t)P(self+8);value=(uint32_t)v[1];{uint32_t data=P(self+16);for(i=0;i<n;i++)W(data+(uint32_t)i*4,value);}break;
    case 0x301d80:
        n=(int32_t)P(self+8);for(i=0;i<n;i++)release(a,item(a,self,i));
        if(P(self+8))CALL(0x12724c,P(self+16),0,P(self+8)*4);
        break;
    case 0x301e30:
        if(v[1])retain(a,value);
        n=(int32_t)P(self+8);
        if(n<(int32_t)P(self+12)){W(self+8,(uint32_t)n+1);W(P(self+16)+(uint32_t)n*4,value);}
        else CALL(0x2d6b20,v[0],v[1]);
        break;
    case 0x301e90:{
        uint32_t data=P(value+16);n=(int32_t)P(value+8);
        for(i=0;i<n;i++)retain(a,P(data+(uint32_t)i*4));
        CALL(0x2d6c60,v[0],P(value+8),P(value+16));break;
    }
    case 0x301ee0:
        n=(int32_t)P(self+8);index=(int32_t)value;
        if(n<index){
            if(index>=0){if((int32_t)P(self+12)<index)CALL(0x2d6790,v[0],v[1],4);else W(self+8,value);}
            CALL(0x12724c,P(self+16)+(uint32_t)n*4,0,(value-(uint32_t)n)*4);
        }else{
            for(i=index;i<n;i++)release(a,item(a,self,i));
            for(i=index;i<n;i++)W(P(self+16)+(uint32_t)i*4,0);
            W(self+8,value);
        }break;
    case 0x302000:
        index=find_pointer(a,value,other,(int32_t)v[3]);
        if(index<0)W(self,P(0x4fb418));
        else{remove_at(a,value,index);W(self,P(0x4fb410));}break;
    case 0x302100:{
        uint32_t removed=0;index=(int32_t)v[2];
        while((index=find_pointer(a,self,value,index))>=0){remove_at(a,self,index);removed++;}
        return word(removed);
    }
    case 0x302240:
        n=(int32_t)P(self+8);
        for(i=0;i<n;i++)if(item(a,self,i)==value)return word((uint32_t)i);
        CORE(0x301e30,v[0],v[1]);return word((uint32_t)n);
    case 0x3022c0:
        if(!v[1]||!v[2])return 0;
        n=(int32_t)P(self+8);
        for(i=0;i<n;i++){
            uint32_t record=item(a,self,i),name=P(record+P(value+8));
            if(name&&!CALL(0x12a4a4,name,v[2]))return word(record);
        }return 0;
    case 0x302380:
        n=(int32_t)P(self+8);if(!v[1])return 0;
        for(i=0;i<n;i++){uint32_t record=item(a,self,i);if(record&&P(record+P(value+8))==other)return word(record);}return 0;
    case 0x3023f0:
        if(!v[1])return 0;
        index=(int32_t)CORE(0x302480,v[0],v[1],v[2]);
        if(index<(int32_t)P(self+8)){uint32_t record=item(a,self,index);if(P(record+P(value+8))==other)return word(record);}return 0;
    case 0x302480:{
        if(!v[1])return UINT64_MAX;
        n=(int32_t)P(self+8);if(n<1)return 0;
        int32_t low=0,high=n-1;
        while(low<high){
            int32_t mid=(int32_t)((uint32_t)low+(uint32_t)high)>>1;
            uint32_t key=P(item(a,self,mid)+P(value+8));
            if(key<other)low=mid+1;else if(key==other)return word((uint32_t)mid);else high=mid-1;
        }
        if(P(item(a,self,low)+P(value+8))<other)low++;
        return word((uint32_t)low);
    }
    case 0x2fecb0:{
        uint32_t pool=P(0x586f20);
        if(!pool){pool=(uint32_t)CALL(0x2eb010,16);if(pool)pool=(uint32_t)CALL(0x2eadf0,pool);W(0x586f20,pool);}
        uint32_t next=(uint32_t)CALL(0x2eaf60,P(0x586f20),v[1]),old=P(self+8);
        if(old){uint32_t refs=P(old-4)-1;W(old-4,refs);if(!refs)CALL(0x30c940,P(old-8),old-8);}
        W(self+8,next);break;
    }
    default:return UINT64_MAX;
    }
    return 0;
}
