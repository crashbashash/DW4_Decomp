/* src/game/beNDMWItemBaseDatabase.cpp — the beNDMWItemBase database accessors, one
 * translation unit in retail address order (finding #924):
 *   0x00447bc0  beNDMWItemBase_RequestDataBase        ask the status messenger for the item DATABASE
 *   0x00447c10  beNDMWItemBase_GetRecordInt           record value lookups through the
 *   0x00447c60  beNDMWItemBase_GetRecordBool            database-for-status virtual
 *   0x00447cb0  beNDMWItemBase_GetRecordString
 *   0x00448640  Gap__Bec__beNDMWItemAbilityChip__vfunc_21  the "abChip" database selector
 *
 * The retail unit at 0x00447bc0 was C++ with exceptions on (its four functions keep
 * exception index records, config/SLUS-20836/exceptions.txt).  RequestDataBase and the AbilityChip
 * selector used to live in beNDMWItemBaseDatabase.c; they now compile here as C++ under
 * that profile, which also reproduces RequestDataBase's record.  The AbilityChip selector
 * belongs to a separate retail unit (beNDMWItemAbilityChip_448640 in config/SLUS-20836/units.tsv);
 * the build resolves each function's profile by address.  The whole unit keeps C linkage.
 *
 * Return contracts are explicit.  The selector's empty assembler directive retains
 * JAL/return rather than a tail transfer without emitting a word (matching construct).
 * The dispatch-only class models raw vtable slot 92; it does not claim the original
 * class declaration or field layout.
 */
#include "dw4/reflected.h"
extern "C" {
/* "DATABASE", "GETDATABASE" and "abChip" (strings read from the ELF). */
extern char s_DATABASE_0051d550[], s_GETDATABASE_0051d560[], s_abChip_0051d598[];
void beMessenger_SendNamed(void *, const char *, const char *, int, const char *);
void *beMessenger_GetObject(void *, int);
long long beDataBase_GetRecordInt(beDataBase *, int, const char *);
unsigned long long beDataBase_GetRecordBool(beDataBase *, int, const char *);
char *beDataBase_GetRecordString(beDataBase *, int, const char *);
beDataBase *beNDMWItemBase_RequestDataBase(beNDMWItemBase *, beNDMWStatus *, const char *);
long long beNDMWItemBase_GetRecordInt(beNDMWItemBase *, beNDMWStatus *, const char *);
unsigned long long beNDMWItemBase_GetRecordBool(beNDMWItemBase *, beNDMWStatus *, const char *);
char *beNDMWItemBase_GetRecordString(beNDMWItemBase *, beNDMWStatus *, const char *);
beDataBase *Gap__Bec__beNDMWItemAbilityChip__vfunc_21(beNDMWItemAbilityChip *, beNDMWStatus *);
}
/* Dispatch-only ABI projection. MW's two-word vtable prefix plus 21 slots gives 92. */
class ItemDatabaseDispatch {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual beDataBase *databaseForStatus(beNDMWStatus *);
};

/* 0x00447bc0: send "DATABASE <name>" / "GETDATABASE" to the status messenger and return
 * the database object it answers with. */
beDataBase *beNDMWItemBase_RequestDataBase(beNDMWItemBase *self, beNDMWStatus *status,
                                           const char *name) {
    void *messenger = (void *)status->_messenger;
    beMessenger_SendNamed(messenger, s_DATABASE_0051d550, name, 0, s_GETDATABASE_0051d560);
    return (beDataBase *)beMessenger_GetObject(messenger, 0);
}

/* 0x00447c10 */
long long beNDMWItemBase_GetRecordInt(beNDMWItemBase *self, beNDMWStatus *status, const char *key) {
    return beDataBase_GetRecordInt(((ItemDatabaseDispatch *)self)->databaseForStatus(status),
                                   self->_recNo, key);
}

/* 0x00447c60 */
unsigned long long beNDMWItemBase_GetRecordBool(beNDMWItemBase *self, beNDMWStatus *status,
                                                const char *key) {
    return beDataBase_GetRecordBool(((ItemDatabaseDispatch *)self)->databaseForStatus(status),
                                    self->_recNo, key);
}

/* 0x00447cb0 */
char *beNDMWItemBase_GetRecordString(beNDMWItemBase *self, beNDMWStatus *status, const char *key) {
    return beDataBase_GetRecordString(((ItemDatabaseDispatch *)self)->databaseForStatus(status),
                                      self->_recNo, key);
}

/* 0x00448640: the ability-chip item's database is the "abChip" table. */
beDataBase *Gap__Bec__beNDMWItemAbilityChip__vfunc_21(beNDMWItemAbilityChip *self,
                                                      beNDMWStatus *status) {
    beDataBase *result = beNDMWItemBase_RequestDataBase((beNDMWItemBase *)self, status, s_abChip_0051d598);

    asm {
        .set reorder
    }

    return result;
}
