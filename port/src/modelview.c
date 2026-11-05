#include "dw4/modelview.h"
#include "dw4/wndepth.h"
#include "dw4/wnprojection.h"
#include "dw4/actoranim.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
struct image {const dw4_igb *g;dw4_scene *scene;uint32_t id;const char *name;dw4_tex texture;};
struct model {size_t controller,layer;dw4_scene *scene;uint32_t root,end;int32_t slot;const dw4_igb *igb;uint32_t database;int hud;};   /* hud: one of the player panels i_stpnl00..04 */
struct motion {char *name;dw4_actoranim *animation;struct motion *next;};
struct mesh {size_t model;uint32_t node,*tri,nt;size_t image;int skinned;struct motion *motions;};
struct dw4_modelview {
    dw4_modelview_vertex_uv vertex_uv;void *vertex_uv_user;   /* digit plates: a number geometry's vertices take their UV from the value */
    dw4_modelview_node_time node_time;void *node_time_user;   /* gauge nodes pose at their meter's time (see dw4_modelview_node_times) */
    const dw4_stageobjects *objects;const dw4_controllers *controllers;
    struct image *images;size_t nimage,missing;struct model *models;size_t nmodel;
    struct mesh *meshes;size_t nmesh;dw4_ui_draw *draw;size_t ndraw,drawcap;
    dw4_scene_node *nodes;size_t nodecap;
    /* dw4_modelview_open_world: the scene's demo camera for models without an authored one. */
    int world,have_camera,hide_labels,hide_hud;float view[16],projection[16];size_t *order;
    /* dw4_modelview_layer_split: 1 draws the models below layer `split`, 2 the models from it on, 3 none, 0 every model. */
    int part;size_t split;
};
struct projected {float clip[4],uv[2],normalized_xy[2];};
static float plane(const struct projected *p,unsigned side)
{return p->clip[3]+(side&1?-1:1)*p->clip[side/2];}
static int projected_triangle(dw4_modelview *v,const dw4_tex *tex,int blend,const uint8_t color[4],
    const struct projected input[3],const uint32_t viewport[4],const float depth_range[2],unsigned width,unsigned height,int perspective,int depth,int write,unsigned color_mask)
{
    struct projected a[16],b[16];unsigned n=3;memcpy(a,input,3*sizeof *a);
    if(perspective){
        unsigned common=63;
        for(unsigned i=0;i<3;i++){
            unsigned outside=0;
            for(unsigned side=0;side<6;side++)if(plane(input+i,side)<0)outside|=1u<<side;
            common&=outside;
        }
        if(common)return 0;
    }
    /* Retail WN vertices extend beyond the framebuffer's XY bounds; the GS
     * scissor clips pixels there. Clip perspective near/far before division,
     * retaining offscreen XY and its STQ interpolation. */
    for(unsigned side=4;perspective && side<6 && n;side++){
        unsigned count=0;
        for(unsigned i=0;i<n;i++){
            const struct projected *from=a+i,*to=a+(i+1)%n;float f=plane(from,side),t=plane(to,side);
            if(f>=0){if(count>=16)return -1;b[count++]=*from;}
            if((f<0)!=(t<0)){
                if(count>=16)return -1;
                float mix=f/(f-t);struct projected *p=b+count++;
                for(unsigned k=0;k<4;k++)p->clip[k]=from->clip[k]+mix*(to->clip[k]-from->clip[k]);
                for(unsigned k=0;k<2;k++)p->uv[k]=from->uv[k]+mix*(to->uv[k]-from->uv[k]);
                for(unsigned k=0;k<2;k++)p->normalized_xy[k]=from->normalized_xy[k]+mix*(to->normalized_xy[k]-from->normalized_xy[k]);
            }
        }
        n=count;memcpy(a,b,n*sizeof *a);
    }
    if(n<3)return 0;
    if(n-2>SIZE_MAX/sizeof(dw4_ui_draw)-v->ndraw)return -1;
    size_t required=v->ndraw+n-2;
    if(required>v->drawcap){dw4_ui_draw *rows=realloc(v->draw,required*sizeof *rows);if(!rows)return -1;v->draw=rows;v->drawcap=required;}
    for(unsigned i=1;i+1<n;i++){
        unsigned vertices[3]={0,i,i+1};dw4_ui_draw *d=v->draw+v->ndraw++;memset(d,0,sizeof *d);
        d->tex=tex;d->stq=1;d->blend=(uint8_t)blend;d->gs_raster=1;d->filter=2;
        d->depth_mode=(uint8_t)depth;d->depth_write=(uint8_t)write;
        d->color_mask=(uint8_t)color_mask;
        for(unsigned e=0;e<3;e++){
            const struct projected *p=a+vertices[e];if(p->clip[3]<=0)return -1;float q=1/p->clip[3];
            d->v[e][0]=(dw4_wn_viewport(p->normalized_xy[0],p->clip[3],viewport[2],1728.f+viewport[0]+viewport[2]*.5f)-1728.f)*width/640.f;
            d->v[e][1]=(dw4_wn_viewport(p->normalized_xy[1],p->clip[3],-(float)viewport[3],1824.f+448.f-viewport[1]-viewport[3]*.5f)-1824.f)*height/448.f;
            /* The source conversion already uses the positive GS origin.
             * Keep the existing native-resolution raster grid when scaling. */
            d->v[e][0]=floorf(d->v[e][0]*16)/16;
            d->v[e][1]=floorf(d->v[e][1]*16)/16;
            d->v[e][2]=p->uv[0]*q;d->v[e][3]=p->uv[1]*q;d->v[e][4]=q;memcpy(d->rgba[e],color,4);
            d->z[e]=dw4_wn_depth(p->clip[2],p->clip[3],depth_range[0],depth_range[1]);
        }
    }
    return 0;
}
static uint32_t field(const dw4_igb_record *r,unsigned ord)
{for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ord)return r->values[i].raw;return UINT32_MAX;}
static int record(const dw4_igb *g,uint32_t id,dw4_igb_record *r)
{return id<g->table_n && g->id_kind[id]==2 && dw4_igb_decode(g,g->id_off[id],r);}
static int image_catalog(dw4_modelview *v)
{
    for(size_t i=0;i<dw4_stageobjects_count(v->objects);i++){
        const dw4_stageobject *o=dw4_stageobjects_at(v->objects,i);int duplicate=0;
        for(size_t j=0;j<i;j++)if(dw4_stageobjects_at(v->objects,j)->scene==o->scene){duplicate=1;break;}
        if(duplicate)continue;
        const dw4_igb *g=(o)->igb;
        for(uint32_t id=0;id<g->table_n;id++){
            dw4_igb_record r={0};if(!record(g,id,&r))continue;
            if(!strcmp(r.class_name,"igImage")){
                struct image *rows=realloc(v->images,(v->nimage+1)*sizeof *rows);
                if(!rows){dw4_igb_record_free(&r);return -1;}v->images=rows;
                rows[v->nimage++]=(struct image){.g=g,.scene=o->scene,.id=id,.name=r.name};
            }dw4_igb_record_free(&r);
        }
    }return 0;
}
static int decode(struct image *im)
{
    if(im->texture.rgba)return 0;
    dw4_igb_record r={0},clut={0};if(!record(im->g,im->id,&r))return -1;
    uint32_t w=field(&r,2),h=field(&r,3),stride=field(&r,19),bits=field(&r,18),bytes=0,pbytes=0;
    const uint8_t *grid=dw4_igb_block(im->g,field(&r,13),&bytes),*pal=NULL;
    if(record(im->g,field(&r,17),&clut))pal=dw4_igb_block(im->g,field(&clut,5),&pbytes);
    dw4_igb_record_free(&r);dw4_igb_record_free(&clut);
    if(!w || !h || w>8192 || h>8192 || (bits!=4 && bits!=8) || stride<(w*bits+7)/8 ||
       (uint64_t)stride*h>bytes || !grid || !pal || pbytes<(bits==8?1024u:64u))return -1;
    uint8_t *pixels=malloc((size_t)w*h*4);if(!pixels)return -1;
    for(unsigned y=0;y<h;y++)for(unsigned x=0;x<w;x++){
        unsigned index=bits==8?grid[y*stride+x]:(grid[y*stride+x/2]>>((x&1)*4))&15;
        const uint8_t *p=pal+index*4;uint8_t *out=pixels+4*((size_t)y*w+x);memcpy(out,p,3);out[3]=(p[3]+1u)/2u;
    }im->texture=(dw4_tex){.rgba=pixels,.w=w,.h=h};return 0;
}
static size_t texture(dw4_modelview *v,const dw4_scene *scene,uint32_t id,const char *name)
{
    for(size_t i=0;i<v->nimage;i++)if(v->images[i].scene==scene && v->images[i].id==id && id){if(!decode(v->images+i))return i;}
    if(name)for(size_t i=0;i<v->nimage;i++)if(v->images[i].name && !strcmp(v->images[i].name,name)){if(!decode(v->images+i))return i;}
    return SIZE_MAX;
}
static int debug_texture(dw4_modelview *v)
{
    uint8_t *pixels=malloc(32*32*4);if(!pixels)return -1;
    for(unsigned y=0;y<32;y++)for(unsigned x=0;x<32;x++){
        uint8_t *p=pixels+4*(y*32+x);p[0]=p[2]=((x/8+y/8)&1)?255:0;p[1]=0;p[3]=128;
    }
    struct image *rows=realloc(v->images,(v->nimage+1)*sizeof *rows);if(!rows){free(pixels);return -1;}
    v->images=rows;v->missing=v->nimage++;rows[v->missing]=(struct image){.name="missing texture",.texture={.rgba=pixels,.w=32,.h=32}};return 0;
}
static size_t attached(const dw4_modelview *v,const dw4_scene *scene,uint32_t node)
{
    for(size_t i=0;i<dw4_stageobjects_attachments(v->objects);i++){
        const dw4_layer_attachment *a=dw4_stageobjects_attachment(v->objects,i);if(a->info->scene!=scene)continue;
        for(uint32_t n=node;n<scene->nnode;n=scene->node[n].parent)if(scene->node[n].id==a->root_id)return a->layer;
    }return SIZE_MAX;
}
/* The active instance owns its top switch; immutable template masks start
 * hidden. Ancestors above that copy are governed by the attached layer owner. */
static int visible(const struct model *m,uint32_t node)
{
    const dw4_scene *s=m->scene;
    while(node!=m->root && node<s->nnode){
        uint32_t parent=s->node[node].parent,index=0;if(parent>=s->nnode)return 0;
        for(uint32_t i=parent+1;i<node;i++)if(s->node[i].parent==parent)index++;
        const dw4_scene_node *n=s->node+parent;
        if(parent==m->root && n->switch_mask.off){
            uint32_t selected=n->switch_bits>1?(uint32_t)m->slot:0;
            if(index!=selected)return 0;
        }else if(n->switch_mask.off){
            const uint32_t *mask=n->switch_values?n->switch_values:dw4_scene_host(s,n->switch_mask);
            if(!mask || index>=n->switch_bits || !(mask[index>>5]&(1u<<(index&31))))return 0;
        }
        if(n->lod_ranges.off){const float *r=dw4_scene_host(s,n->lod_ranges);if(!r || index>=n->lod_count || r[index]>0 || (index+1<n->lod_count && r[index+1]<=0))return 0;}
        node=parent;
    }return node==m->root;
}
static dw4_modelview *open_layers(const dw4_stageobjects *objects,const dw4_controllers *controllers,char *error,size_t cap,int every_layer);
dw4_modelview *dw4_modelview_open(const dw4_stageobjects *objects,const dw4_controllers *controllers,char *error,size_t cap)
{return open_layers(objects,controllers,error,cap,0);}
/* Interface scenes (stagIS11..13) have no world: their windows are authored on the game and background layers (GM01, BG02)
 * rather than the WN window layers, so every attached layer is drawn. */
dw4_modelview *dw4_modelview_open_scene(const dw4_stageobjects *objects,const dw4_controllers *controllers,char *error,size_t cap)
{return open_layers(objects,controllers,error,cap,1);}
/* Demo scenes (stagML14): every layer, in layer order, with skinned meshes posed from the bank's motion database. A model pack
 * whose scene graph is not referenced by a layer path (the _common s_<species> packs) joins the layer its top igAttrSet names, the
 * rule the layer binder applies to authored roots (dw4_stageobjects_bind). */
dw4_modelview *dw4_modelview_open_world(const dw4_stageobjects *objects,const dw4_controllers *controllers,char *error,size_t cap)
{return open_layers(objects,controllers,error,cap,2);}
dw4_modelview *dw4_modelview_open_field(const dw4_stageobjects *objects,const dw4_controllers *controllers,char *error,size_t cap)
{return open_layers(objects,controllers,error,cap,3);}
void dw4_modelview_hide_labels(dw4_modelview *v,int hide){if(v)v->hide_labels=!!hide;}
void dw4_modelview_hide_hud(dw4_modelview *v,int hide){if(v)v->hide_hud=!!hide;}
void dw4_modelview_vertex_uvs(dw4_modelview *v,dw4_modelview_vertex_uv fn,void *user){if(v){v->vertex_uv=fn;v->vertex_uv_user=user;}}
void dw4_modelview_node_times(dw4_modelview *v,dw4_modelview_node_time fn,void *user){if(v){v->node_time=fn;v->node_time_user=user;}}
void dw4_modelview_layer_split(dw4_modelview *v,const char *layer,int part)
{
    if(!v)return;
    v->part=0;
    if(!layer || part<1 || part>2)return;
    for(size_t i=0;i<dw4_stageobjects_layers(v->objects);i++)
        if(!strcmp(dw4_stageobjects_layer(v->objects,i),layer)){v->split=i;v->part=part;return;}
    if(part==2)v->part=3; /* no such layer: part 1 has drawn every model */
}
void dw4_modelview_camera(dw4_modelview *v,const float view[16],const float projection[16])
{
    if(!v)return;
    v->have_camera=view && projection;
    if(v->have_camera){memcpy(v->view,view,sizeof v->view);memcpy(v->projection,projection,sizeof v->projection);}
}
static size_t named_layer(const dw4_modelview *v,const dw4_scene *s,uint32_t node)
{
    while(node<s->nnode && s->node[node].parent<s->nnode)node=s->node[node].parent;
    if(node>=s->nnode || !s->node[node].name || strcmp(s->node[node].class_name,"igAttrSet"))return SIZE_MAX;
    for(size_t i=0;i<dw4_stageobjects_layers(v->objects);i++)if(!strcmp(dw4_stageobjects_layer(v->objects,i),s->node[node].name))return i;
    return SIZE_MAX;
}
/* Layer order (BG..GM..PC..EF..WN..FONT) for the world variant; ties keep controller order. */
static int layer_order(dw4_modelview *v)
{
    v->order=malloc((v->nmodel?v->nmodel:1)*sizeof *v->order);if(!v->order)return -1;
    for(size_t i=0;i<v->nmodel;i++){
        size_t j=i;
        while(j && v->models[v->order[j-1]].layer>v->models[i].layer){v->order[j]=v->order[j-1];j--;}
        v->order[j]=i;
    }
    return 0;
}
/* The bank's skeletal motion for a skinned mesh, decoded once per name. */
static dw4_actoranim *mesh_motion(struct mesh *mesh,const struct model *model,const char *name,char *error,size_t cap)
{
    if(!name)return NULL;
    for(struct motion *m=mesh->motions;m;m=m->next)if(!strcmp(m->name,name))return m->animation;
    dw4_actoranim *animation=dw4_actoranim_open_motion_database(model->igb->data,(uint32_t)model->igb->size,model->scene,mesh->node,name,model->database,error,cap);
    if(!animation)return NULL;
    struct motion *m=calloc(1,sizeof *m);char *copy=malloc(strlen(name)+1);
    if(!m || !copy){free(m);free(copy);dw4_actoranim_close(animation);return NULL;}
    strcpy(copy,name);*m=(struct motion){copy,animation,mesh->motions};mesh->motions=m;return animation;
}
static dw4_modelview *open_layers(const dw4_stageobjects *objects,const dw4_controllers *controllers,char *error,size_t cap,int every_layer)
{
    if(!objects || !controllers)return NULL;
    dw4_modelview *v=calloc(1,sizeof *v);if(!v)return NULL;v->objects=objects;v->controllers=controllers;
    if(image_catalog(v) || debug_texture(v))goto bad;
    for(size_t i=0;i<dw4_controllers_count(controllers);i++){
        const dw4_stageobject *info;int32_t slot;dw4_controllers_model(controllers,i,&info,&slot);
        const dw4_stageobject *bank=NULL;
        for(size_t j=0;j<dw4_stageobjects_count(objects);j++){
            const dw4_stageobject *o=dw4_stageobjects_at(objects,j);
            if(o->scene==info->scene && !strcmp(dw4_stageobject_class(o),"beAction2Info") && dw4_stageobject_name(o) && !strcmp(dw4_stageobject_name(o),dw4_stageobject_name(info))){bank=o;break;}
        }
        if(!bank)continue;
        dw4_igb_record r={0};if(!record((bank)->igb,bank->id,&r))goto bad;
        uint32_t id=field(&r,7),database=field(&r,8);dw4_igb_record_free(&r);dw4_scene *s=bank->scene;uint32_t root=0;
        while(root<s->nnode && s->node[root].id!=id)root++;
        if(root==s->nnode)continue;
        /* The lobby HUD (lobbyui) owns the single-player panels i_stpnl00..04 and draws them with real
         * record values; drawing their controller instances here too stacks a placeholder HUD under it. */
        if(every_layer!=3 && !strncmp(dw4_stageobject_name(info),"i_stpnl0",8) && dw4_stageobject_name(info)[8]>='0' && dw4_stageobject_name(info)[8]<='4' && !dw4_stageobject_name(info)[9])continue;
        size_t layer=attached(v,s,root);
        if(layer==SIZE_MAX && every_layer==2)layer=named_layer(v,s,root);
        const char *name=layer==SIZE_MAX?NULL:dw4_stageobjects_layer(objects,layer);
        if(!name || ((!every_layer || every_layer==3) && strncmp(name,"WN",2)))continue;
        uint32_t end=root+1;while(end<s->nnode && s->node[end].depth>s->node[root].depth)end++;
        struct model *models=realloc(v->models,(v->nmodel+1)*sizeof *models);if(!models)goto bad;v->models=models;
        const char *pn=dw4_stageobject_name(info);if(!pn)pn="";
        size_t model=v->nmodel++;models[model]=(struct model){i,layer,s,root,end,slot,(bank)->igb,database,!strncmp(pn,"i_stpnl0",8) && pn[8]>='0' && pn[8]<='4' && !pn[9]};
        for(uint32_t n=root;n<end;n++){
            uint32_t m=dw4_scene_node_mesh(s,n);if(m==UINT32_MAX)continue;
            struct mesh mesh={.model=model,.node=n,.image=texture(v,s,dw4_scene_node_texture(s,n),dw4_scene_node_texture_name(s,n))};
            if(every_layer==2)for(uint32_t a=n;a<s->nnode;a=s->node[a].parent)if(!strcmp(s->node[a].class_name,"igBlendMatrixSelect")){mesh.skinned=1;break;}
            const char *why=NULL;
            if(mesh.image==SIZE_MAX){
                const char *texture_name=dw4_scene_node_texture_name(s,n);
                fprintf(stderr,"UI texture unavailable: %s (image %u), model %s, mesh %s [%u]\n",texture_name?texture_name:"unnamed",dw4_scene_node_texture(s,n),dw4_stageobject_name(info),s->node[n].name?s->node[n].name:"unnamed",n);
                mesh.image=v->missing;
            }
            if(dw4_scene_tris(s,s->mesh+m,&mesh.tri,&mesh.nt,&why)){
                snprintf(error,cap,"UI model %s mesh %u unavailable: %s",dw4_stageobject_name(info),n,why?why:"invalid triangles");goto bad;
            }
            struct mesh *rows=realloc(v->meshes,(v->nmesh+1)*sizeof *rows);if(!rows){free(mesh.tri);goto bad;}v->meshes=rows;rows[v->nmesh++]=mesh;
        }
    }
    if(every_layer==2){v->world=1;if(layer_order(v))goto bad;}
    return v;
bad:if(!error[0])snprintf(error,cap,"authored UI model preparation failed");dw4_modelview_close(v);return NULL;
}
void dw4_modelview_forget_gpu(const dw4_modelview *v,dw4_gl_layer *gpu)
{
    if(v && gpu)for(size_t i=0;i<v->nimage;i++)dw4_gl_layer_texture_forget(gpu,&v->images[i].texture);
}
void dw4_modelview_close(dw4_modelview *v)
{
    if(!v)return;
    for(size_t i=0;i<v->nimage;i++)free((void *)v->images[i].texture.rgba);
    for(size_t i=0;i<v->nmesh;i++){
        free(v->meshes[i].tri);
        for(struct motion *m=v->meshes[i].motions,*next;m;m=next){next=m->next;dw4_actoranim_close(m->animation);free(m->name);free(m);}
    }
    free(v->images);free(v->models);free(v->meshes);free(v->draw);free(v->nodes);free(v->order);free(v);
}
/* igBillboard: the node and everything below it face the camera. With row vectors, m = C * B (C: mesh relative to the billboard
 * node, B: the billboard node's world matrix); the facing matrix keeps the node's world origin and C's own shape but replaces
 * B's rotation with the inverse of the view rotation, so the geometry has no rotation in camera space. */
static int billboard_matrix(const dw4_scene *s,uint32_t node,const float m[16],const float view[16],float out[16])
{
    uint32_t b;
    for(b=node;b<s->nnode;b=s->node[b].parent)if(s->node[b].class_name && !strcmp(s->node[b].class_name,"igBillboard"))break;
    if(b>=s->nnode)return 0;
    float bw[16];if(dw4_scene_node_world(s,b,bw))return 0;
    /* inverse of the upper 3x3 of bw (rotation and scale), then C = m * inv(bw) restricted to the 3x3 block */
    float a=bw[0],bb=bw[1],c=bw[2],d=bw[4],e=bw[5],f=bw[6],g=bw[8],h=bw[9],i=bw[10];
    float det=a*(e*i-f*h)-bb*(d*i-f*g)+c*(d*h-e*g);if(fabsf(det)<1e-12f)return 0;
    float inv[9]={(e*i-f*h)/det,(c*h-bb*i)/det,(bb*f-c*e)/det,(f*g-d*i)/det,(a*i-c*g)/det,(c*d-a*f)/det,(d*h-e*g)/det,(bb*g-a*h)/det,(a*e-bb*d)/det};
    float cl[9];  /* C3 = M3 * inv(B3) */
    for(unsigned r=0;r<3;r++)for(unsigned k=0;k<3;k++)cl[3*r+k]=m[4*r]*inv[k]+m[4*r+1]*inv[3+k]+m[4*r+2]*inv[6+k];
    /* translation of the mesh node relative to the billboard origin, in the billboard's frame: (m_t - b_t) * inv(B3) */
    float rel[3]={m[12]-bw[12],m[13]-bw[13],m[14]-bw[14]},ct[3];
    for(unsigned k=0;k<3;k++)ct[k]=rel[0]*inv[k]+rel[1]*inv[3+k]+rel[2]*inv[6+k];
    /* view rotation inverse = transpose (the view is a rigid transform) */
    float rv[9];for(unsigned r=0;r<3;r++)for(unsigned k=0;k<3;k++)rv[3*r+k]=view[4*k+r];
    memset(out,0,16*sizeof *out);
    for(unsigned r=0;r<3;r++)for(unsigned k=0;k<3;k++)out[4*r+k]=cl[3*r]*rv[k]+cl[3*r+1]*rv[3+k]+cl[3*r+2]*rv[6+k];
    float off[3];for(unsigned k=0;k<3;k++)off[k]=ct[0]*rv[k]+ct[1]*rv[3+k]+ct[2]*rv[6+k];
    for(unsigned k=0;k<3;k++)out[12+k]=bw[12+k]+off[k];
    out[15]=1;return 1;
}
/* WN00 models that stand at a world position and are projected with the scene camera: the point-message cursor and the floating combat numbers (hypothesis #2798 for the latter). */
static int follows_world(const char *name){
    static const char *const names[]={"i_pointcur","i_pcnumic","i_dmgnum","i_expnum","i_healnum","i_pcdmgnum","i_bitnum","i_getitempnl01","i_getitempnl02","i_getitempnl03"};   /* the got-item panels (PLAYER SETEFFECT) follow the picking player */
    for(unsigned i=0;i<sizeof names/sizeof *names;i++)if(!strcmp(name,names[i]))return 1;
    return 0;
}
static int follow_label(dw4_modelview *v,const struct model *model){const dw4_stageobject *fi=NULL;int32_t fs;dw4_controllers_model(v->controllers,model->controller,&fi,&fs);return fi&&fi->object.off&&dw4_stageobject_name(fi)&&!strcmp(dw4_stageobject_name(fi),"i_pointcur");}
int dw4_modelview_draw_clocks(dw4_modelview *v,unsigned width,unsigned height,const dw4_ui_draw **out,size_t *count,char *error,size_t cap,
    dw4_modelview_clock clock,void *user)
{
    if(!v || !width || !height || !out || !count)return -1;
    v->ndraw=0;
    for(size_t k=0;k<v->nmodel;k++){
        size_t i=v->order?v->order[k]:k;
        struct model *model=v->models+i;const dw4_modelctrl *ctrl=dw4_controllers_model(v->controllers,model->controller,NULL,NULL);
        if(!dw4_modelctrl_drawable(ctrl) || !dw4_stageobjects_layer_visible(v->objects,model->layer))continue;
        if(v->part==3 || (v->part==1 && model->layer>=v->split) || (v->part==2 && model->layer<v->split))continue;
        /* Sampling a draw must not rebase another instance or the world graph.
         * Arena/geometry/sequence buffers remain borrowed; only node state is
         * copied, and no mutable switch allocation is changed here. */
        dw4_scene snapshot=*model->scene;
        if(snapshot.nnode>v->nodecap){
            dw4_scene_node *nodes=realloc(v->nodes,(size_t)snapshot.nnode*sizeof *nodes);if(!nodes)goto bad;
            v->nodes=nodes;v->nodecap=snapshot.nnode;
        }
        memcpy(v->nodes,snapshot.node,(size_t)snapshot.nnode*sizeof *v->nodes);snapshot.node=v->nodes;
        struct model sampled=*model;sampled.scene=&snapshot;dw4_scene *s=&snapshot;
        dw4_modelctrl_actor actor;dw4_modelctrl_actor_state(ctrl,&actor);
        int64_t ns=dw4_modelctrl_time(ctrl);
        if(clock){const dw4_stageobject *info;int32_t slot;dw4_controllers_model(v->controllers,model->controller,&info,&slot);
            ns=clock(user,info,slot,ns);}
        for(uint32_t n=model->root;n<model->end;n++)if(s->node[n].has_seq) {
            int64_t time=ns;
            if(v->node_time)for(uint32_t a=n;a<s->nnode && a>=model->root;a=s->node[a].parent){   /* a gauge's nodes follow the meter that owns their ancestor */
                int64_t mt;if(v->node_time(v->node_time_user,s->node[a].id,model->slot,&mt)){time=mt;break;}   /* the slot: panel graphs share transforms between the slot copies, so a node id alone does not name its meter */
                if(a==model->root)break;
            }
            dw4_scene_node_drive(s,n,0,time);
        }
        dw4_scene_set_engine_time(s,0);
        /* World instances: the RAM slot's beModelCtrlNode2 takes the actor matrix (the lobby's native instance rule), replacing the
         * authored layout offset of each slot copy; window models keep their offsets plus the actor position. */
        /* The point-message cursor (i_pointcur, a WN00 model at a world position) is projected with the scene camera so the arrow
         * stands over its target; every other window model keeps its authored screen layout. */
        int follow=0;{const dw4_stageobject *fi=NULL;int32_t fs;dw4_controllers_model(v->controllers,model->controller,&fi,&fs);
            follow=fi && fi->object.off && dw4_stageobject_name(fi) && follows_world(dw4_stageobject_name(fi));}
        if(v->hide_labels && follow_label(v,model))continue;
        if(v->hide_hud && model->hud)continue;
        if(model->hud){   /* a panel's slot copy carries an authored layout offset in its beModelCtrlNode2 (the portrait icon: 15 x slot); the instance's own position (GENERATE/MOVETRANS) is its place (hypothesis, #2923) */
            uint32_t root=model->root,selected=s->node[root].switch_mask.off && s->node[root].switch_bits>1?(uint32_t)model->slot:0,index=0,child;
            for(child=root+1;child<model->end;child++)if(s->node[child].parent==root && index++==selected)break;
            if(child<model->end && !strcmp(s->node[child].class_name,"beModelCtrlNode2"))s->node[child].m[12]=s->node[child].m[13]=s->node[child].m[14]=0;
        }
        int placed=0;
        if(v->world){
            uint32_t instance=model->root;
            if(s->node[instance].switch_mask.off){
                uint32_t selected=s->node[instance].switch_bits>1?(uint32_t)model->slot:0,index=0,child;
                for(child=instance+1;child<model->end;child++)if(s->node[child].parent==instance && index++==selected)break;
                instance=child;
            }
            if(instance<model->end && !strcmp(s->node[instance].class_name,"beModelCtrlNode2")){
                dw4_modelctrl_matrix(ctrl,s->node[instance].m);s->node[instance].has_matrix=1;placed=1;
            }
        }
        for(size_t j=0;j<v->nmesh;j++)if(v->meshes[j].model==i){
            struct mesh *mesh=v->meshes+j;if(!visible(&sampled,mesh->node))continue;
            float m[16],du=0,dv=0;if(dw4_scene_node_world(s,mesh->node,m))goto bad;
            float color[4]={1,1,1,1};
            for(uint32_t n=mesh->node;n<s->nnode;n=s->node[n].parent)if(s->node[n].has_color){memcpy(color,s->node[n].color,sizeof color);break;}
            color[3]*=dw4_modelctrl_alpha(ctrl);
            uint32_t src=0,dst=0;int blend=1;
            if(dw4_scene_node_blend(s,mesh->node,&src,&dst) && src==4 && dst==1)blend=2;
            dw4_scene_node_uv_offset(s,mesh->node,&du,&dv);const dw4_scene_mesh *sm=s->mesh+dw4_scene_node_mesh(s,mesh->node);
            const float *pos=dw4_scene_host(s,sm->positions),*uv=dw4_scene_host(s,sm->uvs);if(!pos || !uv)goto bad;
            if(mesh->skinned){
                /* The controller's current motion and its local time, as the lobby poses its skinned instances. */
                dw4_actoranim *motion=mesh_motion(mesh,model,actor.motion,error,cap);const float *normals;
                if(!motion){if(!error[0])snprintf(error,cap,"model mesh %u: motion %s unavailable",mesh->node,actor.motion?actor.motion:"<none>");return -1;}
                dw4_actoranim_loop(motion,actor.motion_loop);dw4_actoranim_blend(motion,0,0);
                if(actor.previous_motion && actor.blend_ns>actor.motion_ns){
                    dw4_actoranim *from=mesh_motion(mesh,model,actor.previous_motion,error,cap);
                    if(!from || dw4_actoranim_blend_motion(motion,from,actor.previous_motion_ns*1e-9,1-(float)actor.motion_ns/actor.blend_ns))goto bad;
                }
                if(dw4_actoranim_pose(motion,model->scene,mesh->node,actor.motion_ns*1e-9,&pos,&normals) || !pos)goto bad;
            }
            const float *view=NULL,*projection=NULL,*depth_range=NULL;const uint32_t *viewport=NULL;uint32_t full[4]={0,0,640,448};float full_depth[2]={0,1};
            for(uint32_t n=mesh->node;n<s->nnode;n=s->node[n].parent){
                if(!view && s->node[n].has_view)view=s->node[n].view;
                if(!projection && s->node[n].has_projection)projection=s->node[n].projection;
                if(!viewport && s->node[n].has_viewport){viewport=s->node[n].viewport;depth_range=s->node[n].viewport_z;}
            }
            if(!view && !projection && (v->world || follow) && v->have_camera){view=v->view;projection=v->projection;}
            if(!viewport)viewport=full;
            if(!depth_range)depth_range=full_depth;
            float billboard[16];
            if((v->world || follow) && view && billboard_matrix(s,mesh->node,m,view,billboard))memcpy(m,billboard,sizeof m);
            int depth=1,write=1,have_depth=0,have_write=0;
            for(uint32_t n=mesh->node;n<s->nnode;n=s->node[n].parent){
                if(!have_depth && s->node[n].has_depth_state){depth=s->node[n].depth_enabled?1:2;have_depth=1;}
                if(!have_write && s->node[n].has_depth_write){write=s->node[n].depth_write;have_write=1;}
            }
            if(depth==2)write=0; /* Disabled igDepthState also suppresses writes. */
            float normalized_projection[16];
            if(projection)dw4_wn_projection_normalize(projection,normalized_projection);
            unsigned color_mask=0;
            for(uint32_t n=mesh->node;n<s->nnode;n=s->node[n].parent)
                if(s->node[n].has_color_mask){color_mask=s->node[n].color_mask;break;}
            uint8_t rgba[4];for(unsigned c=0;c<4;c++)rgba[c]=(uint8_t)fminf(128,fmaxf(0,color[c]*(c==3?128:127)));
            if(mesh->nt>SIZE_MAX/sizeof(dw4_ui_draw)-v->ndraw)goto bad;
            size_t required=v->ndraw+mesh->nt;
            if(required>v->drawcap){
                dw4_ui_draw *rows=realloc(v->draw,required*sizeof *rows);if(!rows)goto bad;
                v->draw=rows;v->drawcap=required;
            }
            for(uint32_t t=0;t<mesh->nt;t++){
                if(view && projection){
                    struct projected triangle[3];
                    for(unsigned e=0;e<3;e++){
                        uint32_t p=mesh->tri[3*t+e];float x=pos[p*3],y=pos[p*3+1],z=pos[p*3+2],world[4],camera[4];
                        for(unsigned k=0;k<4;k++)world[k]=x*m[k]+y*m[4+k]+z*m[8+k]+m[12+k];
                        if(!placed)for(unsigned k=0;k<3;k++)world[k]+=actor.position[k];
                        for(unsigned k=0;k<4;k++)camera[k]=world[0]*view[k]+world[1]*view[4+k]+world[2]*view[8+k]+world[3]*view[12+k];
                        for(unsigned k=0;k<4;k++)triangle[e].clip[k]=camera[0]*projection[k]+camera[1]*projection[4+k]+camera[2]*projection[8+k]+camera[3]*projection[12+k];
                        dw4_wn_projection_xy(camera,normalized_projection,triangle[e].normalized_xy);
                        triangle[e].uv[0]=uv[p*2]+du;triangle[e].uv[1]=uv[p*2+1]+dv;
                        if(v->vertex_uv)v->vertex_uv(v->vertex_uv_user,s->node[mesh->node].id,dw4_scene_id_of(s,s->node[mesh->node].geometry),p,triangle[e].uv);
                    }
                    int perspective=projection[3]!=0 || projection[7]!=0 || projection[11]!=0;
                    if(projected_triangle(v,&v->images[mesh->image].texture,blend,rgba,triangle,viewport,depth_range,width,height,perspective,depth,write,color_mask))goto bad;
                    continue;
                }
                dw4_ui_draw *d=v->draw+v->ndraw++;memset(d,0,sizeof *d);d->tex=&v->images[mesh->image].texture;d->stq=1;d->blend=(uint8_t)blend;
                /* Legacy direct-XY fallback has no authored projection/depth
                 * range. Keep its prior overlay behavior until that contract exists. */
                d->depth_mode=d->depth_write=0;d->gs_raster=1;d->filter=2;
                d->color_mask=(uint8_t)color_mask;
                for(unsigned e=0;e<3;e++){
                    uint32_t p=mesh->tri[3*t+e];float x=pos[p*3],y=pos[p*3+1],z=pos[p*3+2];
                    d->v[e][0]=(320+x*m[0]+y*m[4]+z*m[8]+m[12]+actor.position[0])*width/640.f;
                    d->v[e][1]=(224-x*m[1]-y*m[5]-z*m[9]-m[13]-actor.position[1])*height/448.f;
                    d->v[e][0]=floorf(d->v[e][0]*16)/16;d->v[e][1]=floorf(d->v[e][1]*16)/16;
                    d->v[e][2]=uv[p*2]+du;d->v[e][3]=uv[p*2+1]+dv;d->v[e][4]=1;
                    if(v->vertex_uv)v->vertex_uv(v->vertex_uv_user,s->node[mesh->node].id,dw4_scene_id_of(s,s->node[mesh->node].geometry),p,&d->v[e][2]);
                    d->z[e]=x*m[2]+y*m[6]+z*m[10]+m[14]+actor.position[2];
                    for(unsigned c=0;c<4;c++)d->rgba[e][c]=(uint8_t)fminf(128,fmaxf(0,color[c]*(c==3?128:127)));
                }
            }
        }
    }*out=v->draw;*count=v->ndraw;return 0;
bad:snprintf(error,cap,"authored UI model sampling failed");return -1;
}
int dw4_modelview_draw(dw4_modelview *v,unsigned width,unsigned height,const dw4_ui_draw **out,size_t *count,char *error,size_t cap)
{return dw4_modelview_draw_clocks(v,width,height,out,count,error,cap,NULL,NULL);}
