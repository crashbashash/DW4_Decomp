/* Screen clipping after the near-plane divide. STQ, Z, colour and fog are
 * affine here; clipping UV or colour in world space changes the GS gradients. */
#ifndef DW4_LOBBYCLIP_H
#define DW4_LOBBYCLIP_H
#include "dw4/render.h"
#include <string.h>
/* Clip the original camera's near/far interval before the perspective divide.
 * A triangle clipped by both parallel planes has at most five vertices. */
static unsigned lobby_clip_depth(const float in[3][10],float near,float far,float out[5][10])
{
    float a[5][10],b[5][10];unsigned count=3;
    memcpy(a,in,3*sizeof a[0]);
    for(unsigned plane=0;plane<2 && count;plane++) {
        unsigned n=0;float edge=plane?far:near;
        for(unsigned e=0;e<count;e++) {
            const float *p=a[(e+count-1)%count],*q=a[e];
            float dp=plane?edge-p[2]:p[2]-edge,dq=plane?edge-q[2]:q[2]-edge;
            if((dp>=0)!=(dq>=0)) {
                float t=dp/(dp-dq);
                for(unsigned k=0;k<10;k++) b[n][k]=p[k]+t*(q[k]-p[k]);
                b[n++][2]=edge;
            }
            if(dq>=0) memcpy(b[n++],q,sizeof b[0]);
        }
        count=n;memcpy(a,b,n*sizeof a[0]);
    }
    memcpy(out,a,count*sizeof a[0]);return count;
}
static unsigned lobby_clip_screen(const dw4_layer_draw *in,int width,int height,
                                   dw4_layer_draw out[5])
{
    float a[8][11],b[8][11];
    unsigned count=3;
    for(unsigned e=0;e<3;e++) {
        memcpy(a[e],in->v[e],5*sizeof(float));
        a[e][5]=in->z[e];a[e][6]=in->f[e];
        for(unsigned k=0;k<4;k++) a[e][7+k]=in->rgba[e][k];
    }
    for(unsigned plane=0;plane<4 && count;plane++) {
        unsigned axis=plane/2,n=0;
        float edge=(plane&1)?(axis?height:width):0;
        for(unsigned e=0;e<count;e++) {
            const float *p=a[(e+count-1)%count],*q=a[e];
            float dp=(plane&1)?edge-p[axis]:p[axis]-edge;
            float dq=(plane&1)?edge-q[axis]:q[axis]-edge;
            if((dp>=0)!=(dq>=0)) {
                float t=dp/(dp-dq);
                for(unsigned k=0;k<11;k++) b[n][k]=p[k]+t*(q[k]-p[k]);
                b[n++][axis]=edge;
            }
            if(dq>=0) memcpy(b[n++],q,sizeof b[0]);
        }
        count=n;memcpy(a,b,n*sizeof a[0]);
    }
    unsigned n=0;
    for(unsigned j=1;j+1<count;j++) {
        const float *v[3]={a[0],a[j],a[j+1]};
        out[n]=*in;
        for(unsigned e=0;e<3;e++) {
            memcpy(out[n].v[e],v[e],5*sizeof(float));
            out[n].z[e]=v[e][5];out[n].f[e]=v[e][6];
            for(unsigned k=0;k<4;k++) out[n].rgba[e][k]=(uint8_t)v[e][7+k];
        }
        n++;
    }
    return n;
}
#endif
