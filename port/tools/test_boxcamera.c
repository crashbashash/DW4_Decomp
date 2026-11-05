#include "dw4/boxcamera.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
static void identity(float m[16])
{memset(m,0,64);m[0]=m[5]=m[10]=m[15]=1;}
int main(void)
{
    float eye[16],a[16],b[16],p[3]={60,10,-30},world[16];
    identity(eye);identity(a);identity(b);eye[14]=80;
    b[0]=b[10]=0;b[2]=1;b[8]=-1;
    dw4_boxcamera c={0};dw4_boxcamera_tick(&c,1,eye,a,p,1);
    assert(c.current==1 && c.previous==1 && c.interest[0]==1);
    p[0]++;dw4_boxcamera_tick(&c,2,eye,b,p,1);
    assert(c.current==2 && c.previous==1 && c.frame==0 && c.interest[0]==1);
    for(unsigned i=0;i<60;i++){p[0]++;dw4_boxcamera_tick(&c,2,eye,b,p,1);}
    assert(c.frame==60 && c.interest[0]>.65f && c.interest[0]<.8f);
    float interrupted[16];memcpy(interrupted,c.interest,64);
    p[0]++;dw4_boxcamera_tick(&c,3,eye,a,p,1);
    assert(c.frame==1 && c.current==3 && c.previous==2);
    for(unsigned i=0;i<16;i++)assert(fabsf(c.interest[i]-interrupted[i])<1e-6f);
    for(unsigned i=0;i<81;i++)dw4_boxcamera_tick(&c,3,eye,a,p,1);
    assert(c.current==c.previous && !memcmp(c.interest,a,64) && !c.timer);
    dw4_boxcamera_world(&c,world);
    assert(world[12]==p[0] && world[13]==10 && world[14]==50);
    p[0]++;dw4_boxcamera_tick(&c,2,eye,b,p,1);
    dw4_boxcamera held=c;
    for(unsigned i=0;i<200;i++)dw4_boxcamera_world(&c,world);
    assert(!memcmp(&c,&held,sizeof c));
    dw4_boxcamera_tick(&c,2,eye,b,p,100);
    assert(c.frame==4.5f); /* Timer delta caps at three, stationary rate 1.5. */
    puts("box camera: initial acquisition, smooth rotation, interruption, stationary completion, timer cap and read-only presentation pass");
}
