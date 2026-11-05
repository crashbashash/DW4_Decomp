#ifndef DW4_TITLESERVICES_H
#define DW4_TITLESERVICES_H
#include "dw4/titlehost.h"
#include "dw4/frontlayer.h"
#include "dw4/scriptservices.h"
#include "dw4/stageobjects.h"
typedef struct dw4_title_services dw4_title_services;
/* Borrow controller/layer until close; this owns only its receiver tokens. */
dw4_title_services *dw4_title_services_open(dw4_scriptservices *,uint64_t scope,
    dw4_title_host *,dw4_frontlayer *);
/* Production registration requires authored native controller/camera infos.
 * The prepared owner must outlive these borrowed receivers. */
dw4_title_services *dw4_title_services_open_prepared(dw4_scriptservices *,uint64_t,
    dw4_title_host *,dw4_frontlayer *,const dw4_stageobjects *);
void dw4_title_services_close(dw4_title_services *);
/* Samples camera time before DM and publishes current model eligibility. */
void dw4_title_services_tick(dw4_title_services *,uint64_t world_ns);
#endif
