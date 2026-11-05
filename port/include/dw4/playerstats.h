/* GAMERAM 3fab90 and its growth/equipment helpers. */
#ifndef DW4_PLAYERSTATS_H
#define DW4_PLAYERSTATS_H
#include "dw4/database.h"
#include "dw4/playertransactions.h"
/* The callback receiver is a borrowed dw4_databases owner. Recalculate only on
 * private staging: callers publish with dw4_property_commit_values on success.
 * WAZALIST uses kind 9, record=selected row, revision=base row (retail +20).
 * HP/MP follow retail refill/clamp rules; no actor/world update is performed. */
int dw4_playerstats_recalculate(void *,dw4_property_folder *);
/* RECALCPLAYER with an explicit false argument (3fab90 flag clear): stats exclude every
 * equipment bonus, WAZALIST/NEXTEXP are refreshed, and the delay/accuracy/extras and
 * element/weapon/model sections are left untouched. XDATA pricing relies on it. */
int dw4_playerstats_recalculate_base(void *,dw4_property_folder *);
int dw4_playerstats_item_attribute(void *,const dw4_item_record *,const char *,int32_t *);
/* Retail 447ed0: HANBAI (sell=0) or KAITORI (sell=1) including enhancement/grade surcharges.
 * 0 found; -1 invalid item, missing column or a pocket grade outside 0..5. */
int dw4_playerstats_item_price(void *,const dw4_item_record *,int sell,int32_t *);
int dw4_playerstats_item_bool(void *,const dw4_item_record *,const char *,int32_t *);
/* Accepted equipment selections with production database/stat dependencies. */
int dw4_playertransactions_equip_database(dw4_playerrecords *,int32_t,const char *,
    size_t,int32_t,const dw4_databases *);
/* Evolve list preview (4435c0 with 3fa3b0/3fa850): a species' saved form as out[0]=MHP, out[1]=MMP,
 * out[2..6]=STR,AC,INT,MND,DEX and out[7..15]=its nine BASE_SKILL levels, from BASE_LEVEL and that
 * species' BASE_UPCNT slice (never the current LEVEL/UPCNT, even for the current species). */
int dw4_playerstats_form(const dw4_databases *,const dw4_property_folder *,int32_t species,int32_t out[16]);
#endif
