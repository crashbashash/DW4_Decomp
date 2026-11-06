/* ReadFile(path): the Alchemy .igb loader driver. Logs "readFile(%s)", notes the clock, then runs
 * the section readers in file order (header, then the version-dependent tables, then the object
 * sections). Every reader returns an igResult through a hidden result pointer; the global at
 * 0x4fb418 holds the failure code, and a reader that yields it sends the loader to its error path
 * FUN_002e9470. After the last reader the load time is logged once through the assert/log hook
 * (string 0x4f9b90); an old-format file that still has external references is reported once
 * through the same hook (string 0x4f9af0). Evidence: asm/igIGBFile_ReadFile.s; strings 0x4f9ad8,
 * 0x4f9af0, 0x4f9b90. Field names are hypotheses from those strings and from the sibling readers
 * (src/unmatched/igIGBFile_Read*.cpp). Matching constructs: every reader result is an unnamed
 * temporary (the compiler gives each its own stack word, laid out downwards by the combat MWCC
 * build); failed() is called on the temporary so the compare goes through its address. Needs the
 * compiler local/mwcps2/combat/mwccps2.exe (sha256
 * acf1088553362dddef7eee2d269848b03208e29fd26caa441848e57b6299786a), flags -O3 -Iinclude (the
 * project default). */

/* The loader's result code: 0x4fb410 holds success, 0x4fb418 failure. */
extern "C" int DAT_004fb418[4];
struct igResult {
  int code;
  bool failed() const { return code == DAT_004fb418[0]; }
};

extern "C" {
extern int DAT_004f9ad8[4];             /* "readFile(%s)" */
extern int DAT_004f9af0[4];             /* "...unable to read this oldversion of igb file format with external references..." */
extern int DAT_004f9b90[4];             /* "Total Time to load %s - %f seconds" */
extern char DAT_00586e20[64];           /* scratch buffer the log line is formatted into */
extern unsigned char GPR_00554c08;      /* "already reported the old-format file" latch */
extern unsigned char GPR_00554c0c;      /* "already reported the load time" latch */
int sprintf(...);
int FUN_00230728(...);                  /* elapsed time between two clock reads */
int FUN_00308240(...);                  /* assert/log hook: 1 = ok, 2 = do not report again */
int FUN_00308320(...);
igResult FUN_002e5f70(void *, int);
igResult igIGBFile_ReadHeader(void *);
igResult FUN_002e6330(void *);
igResult FUN_002e63e0(void *);
igResult FUN_002e6f50(void *);
igResult FUN_002e7390(void *);
igResult FUN_002e7640(void *);
igResult FUN_002e78b0(void *);
igResult FUN_002e79a0(void *);
igResult FUN_002e7ed0(void *);
igResult FUN_002e7f20(void *);
igResult FUN_002e82a0(void *);
igResult FUN_002e8670(void *);
igResult FUN_002e8880(void *);
igResult FUN_002e8d40(void *);
igResult FUN_002e8e50(void *);
igResult FUN_002e91e0(void *);
igResult FUN_002e94b0(void *);
void FUN_002e8a10(void *);
void FUN_002e8a40(void *);
int FUN_002e9470(void *);               /* error path: tears the half-read file down */
}

/* The engine clock; now() is the method at vtable offset 100. */
class Clock {
public:
  virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19(); virtual void c20(); virtual void c21(); virtual void c22();
  virtual int now();
};
extern Clock *DAT_005871d8[4];

struct Device { int pad[3]; int name; };   /* name at +12 is what the old-format report prints */

struct File {
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
  virtual igResult v30();             /* +120 */
  virtual void v31();
  virtual void v32();
  virtual igResult readTail();        /* +132 */
  int pad4;
  int result;                         /* +8, returned on success */
  char pad12[36];
  unsigned char loading;              /* +48 */
  unsigned char loaded;               /* +49 */
  char pad50[6];
  unsigned char f56;
  char pad57[43];
  int version;                        /* +100, igb format version (the header reader caps it at 7) */
  Device *device;                     /* +104 */
  char pad108[105];
  unsigned char hasExternalRefs;      /* +213 */
  unsigned char f214;                 /* +214, selects the sectioned object reader */
  char pad215[62];
  unsigned char f277;
  char pad278[14];
  unsigned char f292;
};

extern "C" int igIGBFile_ReadFile(File *self, int path) {
  int startTime;
  sprintf(DAT_00586e20, DAT_004f9ad8, path);
  startTime = DAT_005871d8[0]->now();
  self->loaded = 0;
  self->loading = 1;
  self->f56 = 0;
  if (FUN_002e5f70(self, path).failed()) return FUN_002e9470(self);
  if (igIGBFile_ReadHeader(self).failed()) return FUN_002e9470(self);
  if (self->version < 5 && self->hasExternalRefs) {
    if (!GPR_00554c08) {
      int answer = FUN_00308320(DAT_004f9af0, self->device->name, self->device->name);
      if (answer != 1 && answer == 2) GPR_00554c08 = 1;
    }
    return FUN_002e9470(self);
  }
  if (self->version >= 3) {
    if (FUN_002e7f20(self).failed()) return FUN_002e9470(self);
    if (FUN_002e82a0(self).failed()) return FUN_002e9470(self);
  }
  if (FUN_002e6330(self).failed()) return FUN_002e9470(self);
  if (FUN_002e63e0(self).failed()) return FUN_002e9470(self);
  if (FUN_002e6f50(self).failed()) return FUN_002e9470(self);
  if (self->version >= 5) {
    if (FUN_002e8e50(self).failed()) return FUN_002e9470(self);
  }
  if (self->f292) {
    if (FUN_002e91e0(self).failed()) return FUN_002e9470(self);
  }
  if (self->f214) {
    if (FUN_002e7390(self).failed()) return FUN_002e9470(self);
    if (FUN_002e7640(self).failed()) return FUN_002e9470(self);
    if (FUN_002e78b0(self).failed()) return FUN_002e9470(self);
  } else {
    if (FUN_002e79a0(self).failed()) return FUN_002e9470(self);
  }
  if (self->version >= 5) {
    if (FUN_002e8d40(self).failed()) return FUN_002e9470(self);
  }
  if (FUN_002e8670(self).failed()) return FUN_002e9470(self);
  if (self->readTail().failed()) return FUN_002e9470(self);
  if (self->version < 3) {
    if (FUN_002e7f20(self).failed()) return FUN_002e9470(self);
  }
  if (self->version < 5) {
    if (FUN_002e8d40(self).failed()) return FUN_002e9470(self);
  }
  if (self->version < 5) {
    if (FUN_002e8e50(self).failed()) return FUN_002e9470(self);
  }
  if (FUN_002e8880(self).failed()) return FUN_002e9470(self);
  if (FUN_002e7ed0(self).failed()) return FUN_002e9470(self);
  FUN_002e94b0(self);
  if (self->f277 == 1) {
    if (self->v30().failed()) return FUN_002e9470(self);
  }
  FUN_002e8a10(self);
  FUN_002e8a40(self);
  self->loaded = 1;
  self->loading = 0;
  if (!GPR_00554c0c) {
    int answer = FUN_00308240(DAT_004f9b90, path, FUN_00230728(DAT_005871d8[0]->now(), startTime));
    if (answer != 1 && answer == 2) GPR_00554c0c = 1;
  }
  return self->result;
}
