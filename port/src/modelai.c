#include "dw4/modelai.h"
#include <string.h>
int dw4_model_floor_response(int floor,int fall,int upward,int falling,int support,int landing,int sleeping)
{
    if(!(uint8_t)floor || upward || !(uint8_t)fall)return DW4_FLOOR_KEEP;
    if(falling)return (uint8_t)landing?DW4_FLOOR_ADJUST:DW4_FLOOR_KEEP;
    if((uint8_t)support)return DW4_FLOOR_ADJUST;
    return sleeping?DW4_FLOOR_KEEP:DW4_FLOOR_FALL;
}
static ee_f32 retail_atan(ee_f32 input)
{
    static const ee_f32 hi[]={0x3eed6338,0x3f490fda,0x3f7b985d,0x3fc90fda};
    static const ee_f32 lo[]={0x31ac3769,0x33222167,0x33140fb4,0x33a22168};
    static const ee_f32 a[]={0x3eaaaaab,0xbe4ccccc,0x3e124924,0xbde38e38,0x3dba2e6e,0xbd9d8795,
        0x3d886b34,0xbd6ef16a,0x3d4bda59,0xbd15a221,0x3c8569d7};
    ee_f32 x=input,absolute=input&0x7fffffff;
    if(absolute>0x507fffff)return input&0x80000000?
        ee_f32_sub(hi[3]^0x80000000,lo[3]):ee_f32_add(hi[3],lo[3]);
    if(absolute<=0x30ffffff)return input;
    int id=-1;
    if(absolute>0x3edfffff) {
        x=absolute;
        if(absolute<=0x3f97ffff) {
            if(absolute<=0x3f2fffff){id=0;x=ee_f32_div(ee_f32_sub(ee_f32_add(x,x),0x3f800000),ee_f32_add(x,0x40000000));}
            else{id=1;x=ee_f32_div(ee_f32_sub(x,0x3f800000),ee_f32_add(x,0x3f800000));}
        } else if(absolute<=0x401bffff) {
            id=2;x=ee_f32_div(ee_f32_sub(x,0x3fc00000),ee_f32_add(ee_f32_mul(x,0x3fc00000),0x3f800000));
        } else{id=3;x=ee_f32_div(0xbf800000,x);}
    }
    ee_f32 z=ee_f32_mul(x,x),w=ee_f32_mul(z,z);
    ee_f32 odd=a[10],even=a[9];
    for(int i=8;i>=0;i-=2)odd=ee_f32_add(a[i],ee_f32_mul(w,odd));
    for(int i=7;i>=1;i-=2)even=ee_f32_add(a[i],ee_f32_mul(w,even));
    ee_f32 sum=ee_f32_add(ee_f32_mul(z,odd),ee_f32_mul(w,even));
    if(id<0)return ee_f32_sub(x,ee_f32_mul(x,sum));
    ee_f32 result=ee_f32_sub(hi[id],ee_f32_sub(ee_f32_sub(ee_f32_mul(x,sum),lo[id]),x));
    return input&0x80000000?result^0x80000000:result;
}
ee_f32 dw4_model_ai_direction(ee_f32 y,ee_f32 x,ee_f32 offset)
{
    ee_f32 iy=y&0x7fffffff,ix=x&0x7fffffff,result;
    unsigned quadrant=(y>>31)|((x>>30)&2);
    if(x==0x3f800000)result=retail_atan(y);
    else if(iy<=0x007fffff)result=quadrant==2?0x40490fda:quadrant==3?0xc0490fda:y;
    else if(ix<=0x007fffff)result=y&0x80000000?0xbfc90fda:0x3fc90fda;
    else {
        int32_t difference=(int32_t)(iy-ix);int32_t k=difference>>23;
        ee_f32 z=k>60?0x3fc90fda:(x&0x80000000) && k<-60?0:retail_atan(ee_f32_div(y,x)&0x7fffffff);
        result=quadrant==0?z:quadrant==1?z^0x80000000:quadrant==2?
            ee_f32_sub(0x40490fda,ee_f32_sub(z,0x34222168)):
            ee_f32_sub(ee_f32_sub(z,0x34222168),0x40490fda);
    }
    return ee_f32_add(offset,result);
}
const char *dw4_model_ai_control(int control,int walking,const char *next,int *phase,int *move)
{
    *move=-1;
    if(!next || strcmp(next,"SQ_NONE"))return next;
    if(control==3 && !walking)return "SQ_WAIT";
    if(control==2 && walking)return "SQ_WALK";
    if(control==1) {
        int wanted=walking?1:2;
        if(*phase!=wanted){*phase=wanted;*move=walking?0:2;}
    }
    return next;
}
int dw4_model_ai_choose(dw4_random *random,const dw4_model_ai_choice *choices,unsigned count)
{
    if(!random || !choices || !count || choices[count-1].limit<16)return -1;
    unsigned draw=dw4_random_next(random)&15;
    for(unsigned i=0;i<count;i++)if((int32_t)draw<choices[i].limit)return (int)i;
    return -1;
}
unsigned dw4_model_ai_zone(ee_f32 distance,const ee_f32 bounds[3])
{
    for(unsigned i=0;i<3;i++)if(ee_f32_cmp(distance,bounds[i])<0)return i;
    return 3;
}
int64_t dw4_model_ai_duration(ee_f32 frames)
{return ee_f32_to_s64(ee_f32_div(ee_f32_mul(frames,0x4e6e6b28),0x42700000));}
ee_f32 dw4_model_player_direction(ee_f32 x,ee_f32 y,ee_f32 camera_x,ee_f32 camera_z)
{return dw4_model_ai_direction(x,y^0x80000000,dw4_model_ai_direction(camera_x,camera_z,0));}

int64_t dw4_model_ai_clock(int64_t ns)
{return (int64_t)((uint64_t)ee_f32_to_s64(ee_f32_from_clock_ticks(ns))<<18);}
ee_f32 dw4_model_frame_delta(int64_t previous,int64_t now)
{
    int64_t elapsed=(int64_t)((uint64_t)dw4_model_ai_clock(now)-(uint64_t)dw4_model_ai_clock(previous));
    /* 22fd70 converts signed long long through software double arithmetic,
     * rounding to nearest, before the EE single-precision division. */
    float converted=(float)elapsed;ee_f32 bits;memcpy(&bits,&converted,4);
    ee_f32 frames=ee_f32_div(bits,0x4b7e502b);
    return ee_f32_cmp(frames,0x40400000)>0?0x40400000:frames;
}
ee_f32 dw4_model_muteki_tick(ee_f32 count,ee_f32 frames)
{
    if(ee_f32_cmp(count,0)<=0)return count;
    count=ee_f32_sub(count,frames);
    return ee_f32_cmp(count,0)<0?0:count;
}
static ee_f32 normalize(ee_f32 angle)
{
    while(ee_f32_cmp(angle,0)<0)angle=ee_f32_add(angle,0x40c90fdb);
    while(ee_f32_cmp(angle,0x40c90fdb)>=0)angle=ee_f32_sub(angle,0x40c90fdb);
    return angle;
}
ee_f32 dw4_model_ai_turn(ee_f32 current,ee_f32 target,ee_f32 limit,ee_f32 frames)
{
    if(ee_f32_cmp(current,target)==0)return current;
    if(ee_f32_cmp(limit,0)==0)return current;
    ee_f32 step=ee_f32_mul(limit,frames),back,forward;
    current=normalize(current);target=normalize(target);
    if(ee_f32_cmp(current,target)<=0) {
        back=ee_f32_sub(target,current);
        forward=ee_f32_sub(current,ee_f32_sub(target,0x40c90fdb));
    } else {
        forward=ee_f32_sub(current,target);
        back=ee_f32_sub(ee_f32_add(target,0x40c90fdb),current);
    }
    if(ee_f32_cmp(back,forward)<0) {
        if(ee_f32_cmp(back,step)>0)target=ee_f32_add(current,step);
    } else if(ee_f32_cmp(forward,step)>0)target=ee_f32_sub(current,step);
    return target;
}

void dw4_model_lock_matrix(float out[16],const float parent[16],const float offset[3])
{
    uint32_t m[16],v[3];memcpy(m,parent,sizeof m);memcpy(v,offset,sizeof v);
    for(int i=0;i<4;i++){
        uint32_t xy=ee_f32_add(ee_f32_mul(m[i],v[0]),ee_f32_mul(m[4+i],v[1]));
        m[12+i]=ee_f32_add(m[12+i],ee_f32_add(xy,ee_f32_mul(m[8+i],v[2])));
    }
    memcpy(out,m,sizeof m);
}
void dw4_model_local_matrix(float out[16],const float world[16],const float local[16])
{
    uint32_t a[16],b[16],c[16];memcpy(a,world,64);memcpy(b,local,64);
    for(unsigned r=0;r<4;r++)for(unsigned j=0;j<4;j++){
        uint32_t v=ee_f32_mul(a[j],b[4*r]);
        for(unsigned k=1;k<4;k++)v=ee_f32_add(v,ee_f32_mul(a[4*k+j],b[4*r+k]));
        c[4*r+j]=v;
    }
    memcpy(out,c,64);
}
