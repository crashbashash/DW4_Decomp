#include "dw4/lobbycollision.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
/* Collect every authored kind1/2 graph, including stages with multiple floors.
 * Copy transformed vertices into owned arrays so independent graphs never borrow
 * another mesh's vertex numbering or lose their local transforms. */
/* `node`'s matrix relative to its ancestor `stop` (exclusive): the local matrices composed child x parent, root first. */
static int world_below(const dw4_scene *s,unsigned node,unsigned stop,float world[16])
{
    unsigned chain[64],n=0;float t[16];
    for(unsigned k=node;k!=stop && k<s->nnode && n<64;k=s->node[k].parent)chain[n++]=k;
    memset(world,0,16*sizeof *world);world[0]=world[5]=world[10]=world[15]=1;
    while(n--) {
        float lm[16];if(!dw4_scene_node_local(s,chain[n],lm))continue;
        for(unsigned r=0;r<4;r++)for(unsigned c=0;c<4;c++){float acc=0;for(unsigned k=0;k<4;k++)acc+=lm[4*r+k]*world[4*k+c];t[4*r+c]=acc;}
        memcpy(world,t,sizeof t);
    }
    return 0;
}
/* stop == UINT32_MAX: the node's world matrix; otherwise its matrix below the ancestor `stop` (a dynamic proxy lives in its slot's frame). */
static int append_below(dw4_collision_mesh *out,const dw4_scene *s,unsigned node,unsigned stop)
{
    uint32_t mi=dw4_scene_node_mesh(s,node);if(mi==UINT32_MAX)return 0;
    const dw4_scene_mesh *m=s->mesh+mi;const float *p=dw4_scene_host(s,m->positions);
    uint32_t *indices=NULL,count=0;float world[16];
    if(!p || dw4_scene_tris(s,m,&indices,&count,NULL) || (stop==UINT32_MAX?dw4_scene_node_world(s,node,world):world_below(s,node,stop,world))) {free(indices);return -1;}
    if(m->num_verts>UINT_MAX-out->vertices || count>UINT_MAX-out->count){free(indices);return -1;}
    for(size_t i=0;i<(size_t)count*3;i++)if(indices[i]>=m->num_verts){free(indices);return -1;}
    size_t vertices=(size_t)out->vertices+m->num_verts,triangles=(size_t)out->count+count;
    if(vertices>SIZE_MAX/(3*sizeof(float)) || triangles>SIZE_MAX/(3*sizeof(uint32_t))){free(indices);return -1;}
    float *positions=realloc(out->owned_positions,vertices*3*sizeof *positions);
    if(!positions){free(indices);return -1;}out->owned_positions=positions;out->positions=positions;
    uint32_t *joined=realloc(out->indices,triangles*3*sizeof *joined);
    if(!joined){free(indices);return -1;}out->indices=joined;
    for(uint32_t i=0;i<m->num_verts;i++)for(unsigned k=0;k<3;k++) {
        float value=p[3*i]*world[k]+p[3*i+1]*world[4+k]+p[3*i+2]*world[8+k]+world[12+k];
        if(!isfinite(value)){free(indices);return -1;}
        positions[3*((size_t)out->vertices+i)+k]=value;
    }
    for(size_t i=0;i<(size_t)count*3;i++)joined[3*(size_t)out->count+i]=indices[i]+out->vertices;
    free(indices);out->vertices+=(uint32_t)m->num_verts;out->count+=count;return 0;
}
static int append(dw4_collision_mesh *out,const dw4_scene *s,unsigned node){return append_below(out,s,node,UINT32_MAX);}
/* stagML11 pack 820's beHitLandModelInfo kind 1/2 graph leaves. These
 * collision graphs are separate from igSceneInfo's drawable graph roots. */
/* Per-triangle bounds for the exact prefilters in dw4_lobby_collision_check / _air (see the header). */
static int bounds_build(dw4_collision_mesh *m)
{
    if(!m->count)return 0;
    free(m->bounds);m->bounds=malloc((size_t)m->count*6*sizeof *m->bounds);if(!m->bounds)return -1;
    for(uint32_t i=0;i<m->count;i++) {
        const float *a=m->positions+3*m->indices[3*i],*b=m->positions+3*m->indices[3*i+1],*c=m->positions+3*m->indices[3*i+2];
        float *o=m->bounds+6*(size_t)i;
        float xmin=fminf(a[0],fminf(b[0],c[0])),xmax=fmaxf(a[0],fmaxf(b[0],c[0]));
        float zmin=fminf(a[2],fminf(b[2],c[2])),zmax=fmaxf(a[2],fmaxf(b[2],c[2]));
        o[4]=fminf(a[1],fminf(b[1],c[1]));o[5]=fmaxf(a[1],fmaxf(b[1],c[1]));
        float det=(b[2]-c[2])*(a[0]-c[0])+(c[0]-b[0])*(a[2]-c[2]);
        float extent=fmaxf(xmax-xmin,zmax-zmin);
        if(!isfinite(det) || fabsf(det)<1.0f) { /* thin or tiny: u and v are numerically unreliable, always run the real test */
            o[0]=o[2]=-INFINITY;o[1]=o[3]=INFINITY;
        } else {
            float pad=1e-3f+1e-4f*extent; /* the test accepts u,v >= -1e-5 and u+v <= 1.00001 */
            o[0]=xmin-pad;o[1]=xmax+pad;o[2]=zmin-pad;o[3]=zmax+pad;
        }
    }
    return 0;
}
const unsigned dw4_collision_special_kind[3]={4,8,0x802};
int dw4_lobby_collision_index(dw4_lobby_collision *c){
    if(bounds_build(&c->wall) || bounds_build(&c->floor))return -1;
    for(unsigned k=0;k<3;k++)if(bounds_build(&c->special[k]))return -1;
    return 0;
}
static int lobby_collision_open_raw(dw4_lobby_collision *,const dw4_scene *,const uint8_t *,const uint64_t *);
/* The dynamic prop walls of the scene: one node per slot of every kind-0x402 info, its proxy triangles in the slot's frame. */
static int dynamic_open(dw4_lobby_collision *c,const dw4_scene *s)
{
    unsigned total=0;
    for(unsigned k=0;k<s->ndynamic;k++)total+=s->dynamic[k].nslot;
    if(!total)return 0;
    c->dynamic=calloc(total,sizeof *c->dynamic);if(!c->dynamic)return -1;
    for(unsigned k=0;k<s->ndynamic;k++) {
        const dw4_scene_dynamic *d=s->dynamic+k;unsigned slot=0;
        if(d->node>=s->nnode)return -1;
        for(unsigned i=d->node+1;i<s->nnode && s->node[i].depth>s->node[d->node].depth;i++) {
            if(s->node[i].parent!=d->node)continue;
            if(slot>=d->nslot)return -1;
            dw4_dynamic_wall *w=c->dynamic+c->ndynamic++;
            w->name=d->name;w->slot=slot;memcpy(w->bound,d->bound+6*slot,sizeof w->bound);slot++;
            for(unsigned q=i+1;q<s->nnode && s->node[q].depth>s->node[i].depth;q++)if(append_below(&w->local,s,q,i))return -1;
        }
    }
    return 0;
}
int dw4_lobby_collision_open(dw4_lobby_collision *c, const dw4_scene *s)
{return dw4_lobby_collision_open_except(c,s,NULL);}
int dw4_lobby_collision_open_except(dw4_lobby_collision *c, const dw4_scene *s,const uint8_t *off)
{return dw4_lobby_collision_open_parts(c,s,off,NULL);}
unsigned dw4_lobby_collision_parts(const dw4_scene *s,unsigned graph)
{
    if(!s || graph>=s->ncollision)return 0;
    const dw4_scene_collision *g=s->collision+graph;unsigned n=0;
    for(unsigned i=g->node;i<s->nnode && (i==g->node || s->node[i].depth>s->node[g->node].depth);i++)n+=dw4_scene_node_mesh(s,i)!=UINT32_MAX;
    return n;
}
int dw4_lobby_collision_open_parts(dw4_lobby_collision *c, const dw4_scene *s,const uint8_t *off,const uint64_t *parts)
{
    int rc=lobby_collision_open_raw(c,s,off,parts);
    if(!rc && dw4_lobby_collision_index(c)){dw4_lobby_collision_close(c);return -1;}
    return rc;
}
static int lobby_collision_open_raw(dw4_lobby_collision *c, const dw4_scene *s,const uint8_t *off,const uint64_t *parts)
{
    memset(c, 0, sizeof *c);
    if(s->ncollision) {
        for(unsigned k=0;k<s->ncollision;k++) {
            const dw4_scene_collision *g=s->collision+k;
            if(off && off[k])continue;
            dw4_collision_mesh *m=g->kind==1?&c->floor:g->kind==2?&c->wall:NULL;
            for(unsigned q=0;q<3 && !m;q++)if(g->kind==dw4_collision_special_kind[q])m=&c->special[q];
            if(!m || g->node>=s->nnode)goto fail;
            unsigned part=0;
            for(unsigned i=g->node;i<s->nnode && (i==g->node || s->node[i].depth>s->node[g->node].depth);i++) {
                if(dw4_scene_node_mesh(s,i)!=UINT32_MAX && part++<64 && parts && ((parts[k]>>(part-1))&1))continue;   /* a door's part switched off */
                if(append(m,s,i))goto fail;
            }
        }
        if((c->floor.count && c->wall.count) || off || parts) {   /* a lift/door group switched off may be the only wall (or floor) the stage has */
            if(dynamic_open(c,s))goto fail;
            return 0;
        }
        goto fail;
    }
    for (unsigned i=0;i<s->nmesh;i++) {
        dw4_collision_mesh *m = s->mesh[i].attr_id == 139 ? &c->wall :
                                s->mesh[i].attr_id == 1064 ? &c->floor : NULL;
        if (!m) continue;
        m->positions=dw4_scene_host(s,s->mesh[i].positions);
        if (!m->positions || dw4_scene_tris(s,&s->mesh[i],&m->indices,&m->count,NULL)) goto fail;
    }
    if (c->wall.count == 286 && c->floor.count == 226) return 0;
fail: dw4_lobby_collision_close(c); return -1;
}
void dw4_lobby_collision_dynamic_pose(dw4_lobby_collision *c,dw4_dynamic_pose pose,void *user){c->pose=pose;c->pose_user=user;}
void dw4_lobby_collision_close(dw4_lobby_collision *c)
{
    free(c->wall.indices); free(c->floor.indices);free(c->wall.owned_positions);free(c->floor.owned_positions);free(c->wall.bounds);free(c->floor.bounds);
    for(unsigned k=0;k<3;k++){free(c->special[k].indices);free(c->special[k].owned_positions);free(c->special[k].bounds);}
    for(unsigned k=0;k<c->ndynamic;k++){free(c->dynamic[k].local.indices);free(c->dynamic[k].local.owned_positions);}
    free(c->dynamic);
    memset(c,0,sizeof *c);
}
static int floor_y(const float *a,const float *b,const float *c,float x,float z,float *y)
{
    float det=(b[2]-c[2])*(a[0]-c[0])+(c[0]-b[0])*(a[2]-c[2]);
    if (fabsf(det)<1e-6f) return 0;
    float u=((b[2]-c[2])*(x-c[0])+(c[0]-b[0])*(z-c[2]))/det;
    float v=((c[2]-a[2])*(x-c[0])+(a[0]-c[0])*(z-c[2]))/det;
    if (u < -1e-5f || v < -1e-5f || u+v > 1.00001f) return 0;
    *y=u*a[1]+v*b[1]+(1-u-v)*c[1]; return 1;
}
unsigned dw4_lobby_collision_move(const dw4_lobby_collision *c,const float old[3],
                                  float pos[3],float half_width,float up,float down)
{return dw4_lobby_collision_move_for(c,0,old,pos,half_width,up,down);}
/* Retail CHECKLAND (FUN_00388010, #3001 and the floor-selection trace): four vertical segments at the footprint corners cover y -100..1000. The chosen
 * floor is the highest triangle inside the height window (y-up < h < y+down), else the nearest one below the model, else the lowest one above it.
 * *in_window says whether the chosen floor passes the window; the return is 0 when no triangle is hit at all. */
static int floor_select(const dw4_lobby_collision *c,const float old[3],const float pos[3],float half_width,float up,float down,float *h,int *in_window)
{
    float win=-INFINITY,below=-INFINITY,lowest=INFINITY;
    for(unsigned corner=0;corner<4;corner++) {
        float x=pos[0]+(corner&1?half_width:-half_width),z=pos[2]+(corner&2?half_width:-half_width);
        for(unsigned i=0;i<c->floor.count;i++) {
            if(c->floor.bounds){const float *bb=c->floor.bounds+6*(size_t)i;if(x<bb[0] || x>bb[1] || z<bb[2] || z>bb[3])continue;}
            const float *a=c->floor.positions+3*c->floor.indices[3*i],*b=c->floor.positions+3*c->floor.indices[3*i+1],*d=c->floor.positions+3*c->floor.indices[3*i+2];float y;
            if(!floor_y(a,b,d,x,z,&y) || y<-100.f || y>1000.f)continue;
            if(old[1]<y+up && y-down<old[1] && y>win)win=y;
            if(y<old[1] && y>below)below=y;
            if(y<lowest)lowest=y;
        }
    }
    if(isfinite(win)){*h=win;*in_window=1;return 1;}
    *in_window=0;
    if(isfinite(below)){*h=below;return 1;}
    if(isfinite(lowest)){*h=lowest;return 1;}
    return 0;
}
static unsigned check_i(const dw4_lobby_collision *c,unsigned flags,const float old[3],float pos[3],float half_width,float up,float down,int wall,int floor);
static unsigned air_i(const dw4_lobby_collision *c,unsigned flags,const float old[3],
    float pos[3],float half_width,int wall,int floor)
{
    unsigned hit=check_i(c,flags,old,pos,half_width,4,4,wall,0);
    if(!floor || pos[1]>old[1])return hit;
    float best=-INFINITY;
    for(unsigned corner=0;corner<4;corner++) {
        float x=pos[0]+(corner&1?half_width:-half_width),z=pos[2]+(corner&2?half_width:-half_width);
        for(unsigned i=0;i<c->floor.count;i++) {
            if(c->floor.bounds){const float *bb=c->floor.bounds+6*(size_t)i;if(x<bb[0] || x>bb[1] || z<bb[2] || z>bb[3])continue;}
            const float *a=c->floor.positions+3*c->floor.indices[3*i];
            const float *b=c->floor.positions+3*c->floor.indices[3*i+1];
            const float *d=c->floor.positions+3*c->floor.indices[3*i+2];float y;
            if(floor_y(a,b,d,x,z,&y) && y<=old[1]+1e-5f && y>=pos[1] && y>best)best=y;
        }
    }
    if(isfinite(best) && best>=1.f){pos[1]=best;hit|=4;}
    else if(pos[1]<0){pos[1]=0;hit|=4;}   /* nothing to land on: the delivery layer lands a model that has dropped below y 0 on the y 0 plane */
    return hit;
}
static unsigned walk_i(const dw4_lobby_collision *c,unsigned flags,const float old[3],
    float pos[3],float half_width,float up,float down,int wall,int floor)
{
    unsigned hit=check_i(c,flags,old,pos,half_width,up,down,wall,0);
    float moved[3];memcpy(moved,pos,sizeof moved);
    unsigned support=check_i(c,flags,old,pos,half_width,up,down,0,floor);
    if(support&2)memcpy(pos,moved,sizeof moved);
    return hit|support;
}

/* Retail CHECKWALL (FUN_00386780, findings #3001/#3003): rays at y+downRange against back-face-culled wall triangles. Returns the nearest hit
 * distance along the ray (and the unit face normal) or a negative number. A triangle only blocks a ray travelling against its face normal
 * (n.dir < -5e-7, n = (v1-v0)x(v2-v0)); the port's strips keep one facing, so the sign agrees with retail's parity-corrected strips. */
/* One back-face-culled triangle against the ray: the hit distance in [0,maxt] and the unit face normal, or a negative number. */
static float ray_tri(const float *a,const float *b,const float *c,const float o[3],const float d[3],float maxt,float n_out[3])
{
    float e1[3]={b[0]-a[0],b[1]-a[1],b[2]-a[2]},e2[3]={c[0]-a[0],c[1]-a[1],c[2]-a[2]};
    float n[3]={e1[1]*e2[2]-e1[2]*e2[1],e1[2]*e2[0]-e1[0]*e2[2],e1[0]*e2[1]-e1[1]*e2[0]},nl=sqrtf(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
    if(nl<1e-12f)return -1;
    n[0]/=nl;n[1]/=nl;n[2]/=nl;
    float den=n[0]*d[0]+n[1]*d[1]+n[2]*d[2];if(!(den<-5e-7f))return -1;
    float t=-(n[0]*(o[0]-a[0])+n[1]*(o[1]-a[1])+n[2]*(o[2]-a[2]))/den;if(!(t>=0 && t<=maxt))return -1;
    float h[3]={o[0]+t*d[0],o[1]+t*d[1],o[2]+t*d[2]};
    const float *v[3]={a,b,c};float side[3];
    for(unsigned k=0;k<3;k++){const float *p=v[k],*q=v[(k+1)%3];
        float u[3]={p[0]-h[0],p[1]-h[1],p[2]-h[2]},w2[3]={q[0]-h[0],q[1]-h[1],q[2]-h[2]};
        side[k]=(u[1]*w2[2]-u[2]*w2[1])*n[0]+(u[2]*w2[0]-u[0]*w2[2])*n[1]+(u[0]*w2[1]-u[1]*w2[0])*n[2];}
    if((side[0]<0)!=(side[1]<0) || (side[1]<0)!=(side[2]<0))return -1;
    memcpy(n_out,n,sizeof(float)*3);return t;
}
static float wall_ray_mesh(const dw4_collision_mesh *w,const float o[3],const float d[3],float maxt,float n_out[3])
{
    float best=-1,x0=fminf(o[0],o[0]+d[0]*maxt),x1=fmaxf(o[0],o[0]+d[0]*maxt),z0=fminf(o[2],o[2]+d[2]*maxt),z1=fmaxf(o[2],o[2]+d[2]*maxt);
    for(unsigned i=0;i<w->count;i++) {
        if(w->bounds){const float *bb=w->bounds+6*(size_t)i;if(bb[1]<x0 || bb[0]>x1 || bb[3]<z0 || bb[2]>z1 || o[1]<bb[4] || o[1]>bb[5])continue;}
        float n[3];float t=ray_tri(w->positions+3*w->indices[3*i],w->positions+3*w->indices[3*i+1],w->positions+3*w->indices[3*i+2],o,d,maxt,n);
        if(t>=0 && (best<0 || t<best)){best=t;memcpy(n_out,n,sizeof n);}
    }
    return best;
}
/* A dynamic node whose model instance is live, with the matrix it had at the start of the query. */
struct dyn_active {const dw4_dynamic_wall *node;float m[16];};
/* Retail's prefilter of a dynamic node (FUN_00388640 + FUN_003885e0): the proxy's local bound plus the matrix translation ONLY (not rotated or scaled),
 * on x and z, inclusive, against the ray's box. The triangles then go through the whole matrix. */
static float wall_ray_dynamic(const struct dyn_active *a,const float o[3],const float d[3],float maxt,float n_out[3])
{
    float x0=fminf(o[0],o[0]+d[0]*maxt),x1=fmaxf(o[0],o[0]+d[0]*maxt),z0=fminf(o[2],o[2]+d[2]*maxt),z1=fmaxf(o[2],o[2]+d[2]*maxt);
    const float *m=a->m,*bd=a->node->bound;
    if(bd[3]+m[12]<x0 || bd[0]+m[12]>x1 || bd[5]+m[14]<z0 || bd[2]+m[14]>z1)return -1;
    const dw4_collision_mesh *l=&a->node->local;float best=-1;
    for(unsigned i=0;i<l->count;i++) {
        float v[3][3];
        for(unsigned k=0;k<3;k++) {
            const float *p=l->positions+3*l->indices[3*i+k];
            for(unsigned e=0;e<3;e++)v[k][e]=p[0]*m[e]+p[1]*m[4+e]+p[2]*m[8+e]+m[12+e];
        }
        float n[3];float t=ray_tri(v[0],v[1],v[2],o,d,maxt,n);
        if(t>=0 && (best<0 || t<best)){best=t;memcpy(n_out,n,sizeof n);}
    }
    return best;
}
/* One ray against every wall of the query: the merged kind-2 graphs, the special kinds (4, 8, 0x802) the model's check flag selects and the live dynamic
 * prop nodes; the nearest hit wins. */
struct wall_set {const dw4_collision_mesh *mesh[4];unsigned n;const struct dyn_active *dyn;unsigned ndyn;};
static float wall_ray(const struct wall_set *w,const float o[3],const float d[3],float maxt,float n_out[3])
{
    float best=-1;
    for(unsigned i=0;i<w->n;i++) {float n[3];float t=wall_ray_mesh(w->mesh[i],o,d,maxt,n);if(t>=0 && (best<0 || t<best)){best=t;memcpy(n_out,n,sizeof n);}}
    for(unsigned i=0;i<w->ndyn;i++) {float n[3];float t=wall_ray_dynamic(w->dyn+i,o,d,maxt,n);if(t>=0 && (best<0 || t<best)){best=t;memcpy(n_out,n,sizeof n);}}
    return best;
}
static unsigned wall_retail(const struct wall_set *w,const float old[3],float pos[3],float half_width,float down)
{
    float dx=pos[0]-old[0],dz=pos[2]-old[2],dl=hypotf(dx,dz);
    if(dl<=0)return 0;                                         /* retail queries only when x or z changed */
    float D[3]={dx/dl,0,dz/dl},S[3]={-D[2],0,D[0]},r=half_width*1.42f,P1[3]={pos[0],pos[1]+down,pos[2]},n[3];
    float back[3]={P1[0]-r*D[0],P1[1],P1[2]-r*D[2]};
    int full=0;
    for(int k=-1;k<=1 && !full;k++) {float o[3]={back[0]+k*r*S[0],back[1],back[2]+k*r*S[2]};full=wall_ray(w,o,D,2*r,n)>=0;}
    if(!full)return 0;
    unsigned hit=0;float dmin=-1;
    for(int k=-1;k<=1;k+=2) {float o[3]={back[0]+k*.5f*r*S[0],back[1],back[2]+k*.5f*r*S[2]};float t=wall_ray(w,o,D,2*r,n);if(t>=0 && (dmin<0 || t<dmin))dmin=t;}
    if(dmin>=0){pos[0]-=(2*r-dmin)*D[0];pos[2]-=(2*r-dmin)*D[2];hit=1;}
    float Q[3]={pos[0]+.75f*r*D[0],P1[1],pos[2]+.75f*r*D[2]},bt=-1,bn[3]={0};
    for(int k=-1;k<=1;k+=2) {float dir[3]={k*S[0],0,k*S[2]};float t=wall_ray(w,Q,dir,r,n);if(t>=0 && (bt<0 || t<bt)){bt=t;memcpy(bn,n,sizeof bn);}}
    if(bt>=0){pos[0]+=(r-bt)*bn[0];pos[2]+=(r-bt)*bn[2];hit=1;}
    return hit;
}
int dw4_hitland_info_applies(unsigned info_kind,unsigned check_flags)
{
    unsigned order=check_flags&~1u;
    return (info_kind&order&0x1FFu)!=0 && (!(info_kind&0x800u) || !(order&0x800u)) && (!(order&0x1000u) || (info_kind&0x1000u));
}
static unsigned check_i(const dw4_lobby_collision *c,unsigned flags,const float old[3],
    float pos[3],float half_width,float up,float down,int wall,int floor)
{
    unsigned hit=0;
    if(wall) {
        struct wall_set ws={{&c->wall},1,NULL,0};
        for(unsigned k=0;k<3;k++)if(c->special[k].count && dw4_hitland_info_applies(dw4_collision_special_kind[k],flags))ws.mesh[ws.n++]=&c->special[k];
        /* the live dynamic nodes, with the matrices they have now (a model moves between ticks, not inside a query) */
        struct dyn_active stack[128],*active=stack;unsigned nactive=0;
        if(c->ndynamic && c->pose && dw4_hitland_info_applies(DW4_HITLAND_DYNAMIC_WALL,flags)) {
            if(c->ndynamic>sizeof stack/sizeof *stack)active=malloc((size_t)c->ndynamic*sizeof *active);
            if(active)for(unsigned k=0;k<c->ndynamic;k++)if(c->pose(c->pose_user,k,active[nactive].m))active[nactive++].node=c->dynamic+k;
        }
        ws.dyn=active;ws.ndyn=nactive;
        hit=wall_retail(&ws,old,pos,half_width,down);wall=0;
        if(active!=stack)free(active);
    }
    /* Contact at the delivered lower probe height; separate authored triangles
     * into horizontal slices and push out along the old-position side. Iteration
     * handles a corner shared by multiple wall planes without tunnelling. */
    float radius=half_width*1.42f, height=pos[1]+down;
    for (unsigned pass=0;wall && pass<3;pass++) for (unsigned i=0;i<c->wall.count;i++) {
        /* A slice segment needs two edges crossing the probe height, so the triangle must straddle it. */
        if(c->wall.bounds && !(c->wall.bounds[6*(size_t)i+4]<=height && c->wall.bounds[6*(size_t)i+5]>height)) continue;
        const float *v[3]; float p[2][2]; unsigned n=0;
        for (unsigned k=0;k<3;k++) v[k]=c->wall.positions+3*c->wall.indices[3*i+k];
        for (unsigned k=0;k<3 && n<2;k++) {
            const float *a=v[k],*b=v[(k+1)%3];
            if ((a[1]<=height && b[1]>height)||(b[1]<=height && a[1]>height)) {
                float t=(height-a[1])/(b[1]-a[1]);
                p[n][0]=a[0]+t*(b[0]-a[0]);p[n++][1]=a[2]+t*(b[2]-a[2]);
            }
        }
        if(n!=2) continue;
        float dx=p[1][0]-p[0][0],dz=p[1][1]-p[0][1],len=hypotf(dx,dz);
        if(len<1e-6f) continue;
        float nx=-dz/len,nz=dx/len;
        float side=(old[0]-p[0][0])*nx+(old[2]-p[0][1])*nz;
        if(side<0) {nx=-nx;nz=-nz;}
        float along=((pos[0]-p[0][0])*dx+(pos[2]-p[0][1])*dz)/(len*len);
        float dist=(pos[0]-p[0][0])*nx+(pos[2]-p[0][1])*nz;
        if(along>=0 && along<=1 && dist<radius && dist>-radius-hypotf(pos[0]-old[0],pos[2]-old[2])) {
            pos[0]+=nx*(radius-dist);pos[2]+=nz*(radius-dist);hit|=1;
        }
    }
    /* Retail HITFLOOR: the selection above, then the delivery layer (beHitLandDeliv::vfunc_33, 0x385eec): a reply with no floor, or a floor below height 1,
     * counts as nothing under the model. A model at y >= 0 is then reported supported and not landed, so it keeps its height and walks on in the air (the
     * practice stage past its edge, a hub lip); below y 0 it snaps to the y 0 plane and lands. Only a floor that exists but lies outside the height window
     * reports no support, which is what starts SQ_FALL. */
    if(!floor)return hit;
    float h;int in_window;
    if(!floor_select(c,old,pos,half_width,up,down,&h,&in_window) || h<1.f) {
        if(pos[1]<0){pos[1]=0;hit|=4;}
        return hit;
    }
    if(in_window)pos[1]=h;
    else {memcpy(pos,old,3*sizeof(float));hit|=2;}
    return hit;
}
unsigned dw4_lobby_collision_check_for(const dw4_lobby_collision *c,unsigned flags,const float old[3],float pos[3],float half_width,float up,float down,int wall,int floor)
{return check_i(c,flags,old,pos,half_width,up,down,wall,floor);}
unsigned dw4_lobby_collision_move_for(const dw4_lobby_collision *c,unsigned flags,const float old[3],float pos[3],float half_width,float up,float down)
{return check_i(c,flags,old,pos,half_width,up,down,1,1);}
unsigned dw4_lobby_collision_air_for(const dw4_lobby_collision *c,unsigned flags,const float old[3],float pos[3],float half_width,int wall,int floor)
{return air_i(c,flags,old,pos,half_width,wall,floor);}
unsigned dw4_lobby_collision_walk_for(const dw4_lobby_collision *c,unsigned flags,const float old[3],float pos[3],float half_width,float up,float down,int wall,int floor)
{return walk_i(c,flags,old,pos,half_width,up,down,wall,floor);}
unsigned dw4_lobby_collision_check(const dw4_lobby_collision *c,const float old[3],float pos[3],float half_width,float up,float down,int wall,int floor)
{return check_i(c,0,old,pos,half_width,up,down,wall,floor);}
unsigned dw4_lobby_collision_air(const dw4_lobby_collision *c,const float old[3],float pos[3],float half_width,int wall,int floor)
{return air_i(c,0,old,pos,half_width,wall,floor);}
unsigned dw4_lobby_collision_walk(const dw4_lobby_collision *c,const float old[3],float pos[3],float half_width,float up,float down,int wall,int floor)
{return walk_i(c,0,old,pos,half_width,up,down,wall,floor);}
