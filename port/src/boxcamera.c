#include "dw4/boxcamera.h"
#include "eefloat.h"
#include <math.h>
#include <string.h>

static unsigned bits(float f){unsigned b;memcpy(&b,&f,4);return b;}
static float value(unsigned b){float f;memcpy(&f,&b,4);return f;}
static float add(float a,float b){return value(ee_f32_add(bits(a),bits(b)));}
static float sub(float a,float b){return value(ee_f32_sub(bits(a),bits(b)));}
static float mul(float a,float b){return value(ee_f32_mul(bits(a),bits(b)));}
static float divide(float a,float b){return value(ee_f32_div(bits(a),bits(b)));}
/* Positive finite sqrt with the same toward-zero model as the EE oracle.
 * Double precision resolves which adjacent float is below the exact root. */
static float root(float a)
{
    double r=sqrt((double)a);float f=(float)r;
    if((double)f>r)f=nextafterf(f,0);
    return f;
}
static void quaternion(float q[4],const float m[16])
{
    float trace=add(add(m[10],m[0]),m[5]), s;
    if(trace>=0) {
        s=root(add(trace,1));q[3]=mul(s,.5f);s=divide(.5f,s);
        q[0]=mul(s,sub(m[9],m[6]));q[1]=mul(s,sub(m[2],m[8]));q[2]=mul(s,sub(m[4],m[1]));
    } else {
        unsigned i=m[0]<m[5]?1:0;if(m[i*5]<m[10])i=2;
        unsigned j=(i+1)%3,k=(i+2)%3;
        s=root(add(m[15],sub(m[i*5],add(m[j*5],m[k*5]))));
        q[i]=mul(s,.5f);s=divide(.5f,s);
        q[j]=mul(s,add(m[i*4+j],m[j*4+i]));
        q[k]=mul(s,add(m[k*4+i],m[i*4+k]));
        q[3]=mul(s,sub(m[k*4+j],m[j*4+k]));
    }
}
static void normalize(float q[4])
{
    float n=divide(1,root(add(add(add(mul(q[3],q[3]),mul(q[2],q[2])),mul(q[1],q[1])),mul(q[0],q[0]))));
    for(unsigned i=0;i<4;i++)q[i]=mul(q[i],n);
}
static void rotation(float m[16],float q[4])
{
    normalize(q);float x=q[0],y=q[1],z=q[2],w=q[3];
    m[0]=sub(1,mul(add(mul(y,y),mul(z,z)),2));
    m[1]=mul(sub(mul(x,y),mul(z,w)),2);m[2]=mul(add(mul(z,x),mul(y,w)),2);
    m[4]=mul(add(mul(x,y),mul(z,w)),2);m[5]=sub(1,mul(add(mul(z,z),mul(x,x)),2));
    m[6]=mul(sub(mul(y,z),mul(x,w)),2);m[8]=mul(sub(mul(z,x),mul(y,w)),2);
    m[9]=mul(add(mul(y,z),mul(x,w)),2);m[10]=sub(1,mul(add(mul(y,y),mul(x,x)),2));
}
static void blend(float out[16],const float from[16],const float to[16],float t)
{
    float a[4],b[4];quaternion(a,from);quaternion(b,to);
    float dot=add(add(add(mul(a[3],b[3]),mul(a[2],b[2])),mul(a[0],b[0])),mul(a[1],b[1]));
    for(unsigned i=0;i<4;i++)a[i]=add(mul(t,dot<0?-b[i]:b[i]),mul(sub(1,t),a[i]));
    normalize(a);rotation(out,a);
    for(unsigned i=12;i<15;i++)out[i]=add(from[i],mul(t,sub(to[i],from[i])));
}
void dw4_boxcamera_tick(dw4_boxcamera *c,unsigned region,const float eye[16],
    const float interest[16],const float p[3],float delta)
{
    int moved=!c->initialized || p[0]!=c->position[0] ||
        p[1]!=c->position[1] || p[2]!=c->position[2];
    memcpy(c->position,p,sizeof c->position);c->initialized=1;
    if(moved && region && region!=c->current) {
        c->previous=c->current;c->current=region;c->frame=0;
        memcpy(c->start_eye,c->eye,sizeof c->eye);
        memcpy(c->start_interest,c->interest,sizeof c->interest);
    }
    if(c->current==c->previous)return;
    if(!c->previous || c->frame>=120) {
        memcpy(c->eye,eye,sizeof c->eye);memcpy(c->interest,interest,sizeof c->interest);
        c->previous=c->current;c->timer=0;
    } else {
        float t=divide(c->frame,120);
        blend(c->eye,c->start_eye,eye,t);blend(c->interest,c->start_interest,interest,t);
        if(!c->timer){c->timer=1;delta=0;}
        if(delta>3)delta=3;
        c->frame=add(c->frame,moved?delta:mul(delta,1.5f));
    }
}
void dw4_boxcamera_world(const dw4_boxcamera *c,float world[16])
{
    for(unsigned row=0;row<4;row++)for(unsigned col=0;col<4;col++) {
        float v=0;for(unsigned k=0;k<4;k++)v=add(v,mul(c->eye[4*row+k],c->interest[4*k+col]));
        world[4*row+col]=v;
    }
    for(unsigned k=0;k<3;k++)world[12+k]=add(world[12+k],c->position[k]);
}
