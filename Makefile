# DW4_Decomp — matching-decompilation build
#
# Goal: rebuild the retail `game.elf` from C, using the ORIGINAL compiler, and
# verify every function byte-for-byte. Where a function has no C yet, its retail
# bytes come from the retail image (the "Ship of Theseus" build), so the tree always
# compiles as a whole while functions are decompiled one at a time. `asm/` is the
# per-function view of those bytes: generated from your executable by tools/split.py
# and never committed (`asm-ensure` below writes it when it is missing or stale).
#
# The compiler is proprietary and NOT in this repo. Put your copies under `local/`
# (gitignored) or point the build at wherever you keep them:
#
#   DW4_WIBO=local/wibo \
#   DW4_MWCC=local/mwcps2/3.0-011126/mwccps2.exe \
#   DW4_ELF=orig/SLUS-20836/SLUS_208.36 \
#   make check
#
# Toolchain identity: MWCCPS2 3.0 (build 011126), driven by wibo (NOT Wine —
# Wine dies on the FLEXlm license check). See docs/engine/toolchain.md.

WIBO   ?= local/wibo
MWCC   ?= local/mwcps2/3.0-011126/mwccps2.exe
# NOT named AS: Make defines AS=as as a built-in, so `AS ?=` keeps the HOST
# assembler (x86) and it fails with "alignment not a power of 2" / silent word
# truncation on MIPS input. Use a name Make has never heard of.
CROSS_AS ?= mipsel-linux-gnu-as
ELF    ?= orig/SLUS-20836/SLUS_208.36
FLAGS  ?= -O3 -Iinclude

# The tables live in config/<GAMEID>/ and the retail executable in orig/<GAMEID>/.
GAMEID := SLUS-20836

BUILD  := build
ASM    := asm
SRC    := src
CONFIG := config/$(GAMEID)

ASM_SRC := $(wildcard $(ASM)/*.s)
# .cpp units exist for the templates that need C++ mode (only C++ has `bool`);
# MWCC picks the language from the extension, so no extra flag is needed. A
# function never has both a .c and a .cpp — automatch writes exactly one.
# A function's file may live in any module folder under `src/` (and unnamed ones
# under `src/unmatched/`), so the unit list is the recursive walk, not `src/*.c`.
# A unit's symbol is its filename; tools/srctree.py owns that rule on the Python
# side, and the object path mirrors the source path so two modules keep two objects.
C_SRC   := $(shell find $(SRC) -name '*.c')
CPP_SRC := $(shell find $(SRC) -name '*.cpp')
ASM_OBJ := $(patsubst $(ASM)/%.s,$(BUILD)/asm/%.o,$(ASM_SRC))
C_OBJ   := $(patsubst $(SRC)/%.c,$(BUILD)/src/%.o,$(C_SRC)) \
           $(patsubst $(SRC)/%.cpp,$(BUILD)/src/%.o,$(CPP_SRC))

export MWCIncludes := $(SRC)

.PHONY: iso all symbols asm asm-ensure executable objdiff objs objs-build check report verify link progress clean help rules hygiene check-fresh link-fresh vtable-slots-check struct-report inventory-check lua-roundtrip

# The default target builds AND compares, the way a matching build should: a plain
# `make` answers "does this tree still reproduce retail?". `make objs` is the
# compile-only step if you only want objects.
all: check

help:
	@echo "make          — build and compare against retail (split round-trip + every src/ function)"
	@echo "make symbols  — (re)generate $(CONFIG)/symbols.txt from data/functions.json"
	@echo "make asm      — (re)generate the retail split in $(ASM)/  (generated, never committed; check and report do this when it is stale)"
	@echo "make objs     — assemble $(ASM)/ and compile $(SRC)/ into $(BUILD)/"
	@echo "make check    — verify the split round-trips AND every C function matches retail"
	@echo "make verify VA=0x... SRC=src/<name>.c  — one function, relocation-aware, verbose"
	@echo "make objdiff  — objdiff.json and the objects for the objdiff diff tool"
	@echo "make report   — coverage only (how much is decompiled)"
	@echo "make progress — regenerate PROGRESS.md + docs/progress.json (no game or compiler needed)"
	@echo "make typed    — typed-coverage report: how much of src/ speaks in recovered structs"
	@echo "make typed-check — fail if typed coverage differs from config/typed-coverage.json (CI runs this)"
	@echo "make typed-scope — typed share of the game layer (config/typed-scope*.tsv)"
	@echo "make reflected-check — compile include/dw4/reflected.h with the host compiler and verify every field offset, struct size and field type"
	@echo "make vtable-slots-check — fail if a local dummy-vtable view names a slot vfunc_NN at a position other than NN"
	@echo "make struct-report — report (not a gate) local struct views that disagree with each other or with reflected.h"
	@echo "make link     — relink the whole section (C + retail remainder) and compare"
	@echo "make iso [DISC=path] — publishing step, not part of the build: the relinked executable in a copy of your disc, in build/$(GAMEID)/"
	@echo "make hygiene — fail on host-identifying details in the tree (docs/host-details-policy.md)"
	@echo "make inventory-check — fail if code the symbol map does not own grew past the recorded debt, or data/inventory-scan.tsv is stale"
	@echo "make lua-roundtrip — recompile every lua/ chunk with stock Lua 4.0.1 luac and fail if fewer match retail than config/lua-roundtrip-baseline.json"
	@echo "make clean"

# Hard rule: nothing that identifies a developer's machine or account is committed. Also enforced by the
# .githooks pre-commit/commit-msg hooks (scripts/install_git_hooks.sh) and the hygiene CI workflow.
hygiene:
	python3 testing/test_check_host_details.py
	python3 testing/test_buildcache.py
	python3 scripts/check_host_details.py --tree
	python3 scripts/check_doc_function_names.py

# The function inventory (docs/engine/function-inventory.md): scripts/inventory_scan.py walks every
# `data` unit of config/SLUS-20836/layout.txt for instruction-shaped bodies and writes data/inventory-scan.tsv;
# this target fails when that table is stale or its byte total exceeds `inventory.unsymbolised_bytes`
# in config/debt-baseline.json. Refresh the table with `python3 scripts/inventory_scan.py --write`.
inventory-check:
	python3 -m unittest discover -s testing -p 'test_inventory_scan.py'
	python3 scripts/inventory_scan.py --check

# The decompiled Lua against its bytecode (docs/engine/lua-decompilation.md): every lua/ chunk recompiled
# with the luac tools/download_tools.py builds, compared with the chunk in the script pack. Not part of
# `make check`: it needs the script pack (AFS, below), not the executable.
lua-roundtrip:
	python3 scripts/lua_roundtrip.py --afs $(AFS)

symbols:
	python3 tools/split.py --symbols --symbols-only

$(CONFIG)/symbols.txt:
	python3 tools/split.py --symbols --symbols-only

asm: $(CONFIG)/symbols.txt
	python3 tools/split.py

# asm/ is generated and gitignored: written when it is missing, or when the executable, the
# symbol map or tools/split.py changed since it was generated.
asm-ensure: executable $(CONFIG)/symbols.txt
	python3 tools/split.py --ensure --elf "$(ELF)"

# Checks the executable's hash, or extracts it from a disc image in orig/<GAMEID>/.
executable:
	python3 tools/project.py executable --version $(GAMEID) --elf "$(ELF)"

# ASM_SRC is read when the Makefile is parsed, so the objects are built by a second make
# that sees the generated tree.
objs: asm-ensure
	$(MAKE) objs-build

objs-build: $(ASM_OBJ) $(C_OBJ)

$(BUILD)/asm/%.o: $(ASM)/%.s
	@mkdir -p $(dir $@)
	$(CROSS_AS) -o $@ $<

$(BUILD)/src/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(WIBO) $(MWCC) -c $(FLAGS) $< -o $@

$(BUILD)/src/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(WIBO) $(MWCC) -c $(FLAGS) $< -o $@

# Results are cached by content in build/cache/ (tools/buildcache.py): a rerun only recompiles what changed.
# `make check-fresh` / `make link-fresh` ignore the cache; run them once before publishing a milestone.
check: asm-ensure
	python3 tools/check.py --wibo "$(WIBO)" --mwcc "$(MWCC)" --elf "$(ELF)" --flags="$(FLAGS)"

check-fresh: asm-ensure
	python3 tools/check.py --no-cache --wibo "$(WIBO)" --mwcc "$(MWCC)" --elf "$(ELF)" --flags="$(FLAGS)"

# --- the derived-rule fixtures (no toolchain; the pack paths are pointed at your copies) ----
# The texture pack's pool order and the model pack's offline geometry chain are re-derived from
# the pack and diffed against their committed tables under docs/engine/.  See
# docs/engine/texture-packs.md and docs/engine/model-format.md.
AFS ?= ../local/extracted/NDMW.AFS
TEXTURE_ENTRY ?= 625
MODEL_ENTRY ?= 621
CHAR_MODEL_ENTRY ?= 861
rules:
	python3 scripts/verify_texpack_layout.py --afs $(AFS) --entry $(TEXTURE_ENTRY)
	python3 scripts/verify_models_layout.py --afs $(AFS) --entry $(MODEL_ENTRY)
	python3 scripts/verify_models_layout.py --afs $(AFS) --entry $(CHAR_MODEL_ENTRY) \
	    --table docs/engine/model-pack-861-attributes.tsv
	python3 scripts/verify_field_kinds.py --afs $(AFS)
	python3 tools/check_regions.py
	python3 scripts/seed_names_getvtable_slots.py --check --out config/SLUS-20836/names/GetVTableSlots.tsv
	python3 scripts/data_owners.py --check
	python3 scripts/module_map.py --check
	python3 scripts/vu1_microcode.py --check
	python3 scripts/gen_platform_seam.py --check

# one function, with relocation handling and a per-instruction diff
#   make verify VA=0x246780 SRC=src/FUN_00246780.c
verify:
	python3 tools/verify.py $(VA) $(SRC) --flags="$(FLAGS)" --verbose

# --- the relink: every layout unit -> objects -> one section -> compare --------
# Uses GNU ld with a generated script (one address per unit is NOT used: ld treats
# `.` inside a section as offset from its start). Needs -G0 and _gp, both for the
# GP-relative relocations in the C objects.
link:
	python3 tools/layout.py >/dev/null
	python3 tools/linkgen.py --all
	mipsel-linux-gnu-ld -T build/link.ld -G0 --no-warn-mismatch -o build/game.elf
	python3 tools/linkcheck.py build/game.elf
	python3 tools/project.py image --version $(GAMEID) build/game.elf

iso: link
	python3 tools/make_iso.py --version $(GAMEID) $(if $(DISC),--disc "$(DISC)")

link-fresh:
	python3 tools/layout.py >/dev/null
	python3 tools/linkgen.py --all --no-cache
	mipsel-linux-gnu-ld -T build/link.ld -G0 --no-warn-mismatch -o build/game.elf
	python3 tools/linkcheck.py build/game.elf
	python3 tools/project.py image --version $(GAMEID) build/game.elf

# objdiff.json and the base and target objects for the diff tool. The tool runs
# `make objdiff <object>`, so the pattern rule accepts the object it names.
objdiff: asm-ensure
	python3 tools/project.py objdiff --version $(GAMEID)
	$(MAKE) -f $(BUILD)/$(GAMEID)/objdiff.mk -j$(shell nproc) objects

$(BUILD)/$(GAMEID)/obj/%.o: objdiff
	@:

report: asm-ensure
	python3 tools/check.py --wibo "$(WIBO)" --mwcc "$(MWCC)" --elf "$(ELF)" \
		--flags="$(FLAGS)" --split-only

# The published progress numbers: PROGRESS.md, docs/progress.json and the block at the top of
# README.md. Needs neither the game nor the compiler — it counts what is committed. CI runs this
# on every push (see .github/workflows/progress.yml).
progress:
	python3 tools/progress.py

# Typed coverage: the inward metric. `typed-check` compares against
# the recorded baseline in config/typed-coverage.json -- the gate is on the *count* of recovered
# accesses, never the percentage, because the m2c loop keeps adding matched (and so untyped) C and
# the ratio can fall while the count only grows. After a batch that adds coverage, re-record it:
#   make typed-baseline && git add config/typed-coverage.json
typed:
	python3 tools/typed_coverage.py --by-class

typed-check:
	python3 tools/typed_coverage.py --check

typed-baseline:
	python3 tools/typed_coverage.py --update-baseline

# The generated structs must be plain C any host compiler reads with the same layout.
reflected-check:
	python3 scripts/check_reflected_layout.py
	python3 scripts/check_scope_headers.py

# Local dummy-vtable views name a slot `vfunc_NN` only when it is the NN-th declared virtual
# (slot 0 is the word at vtable +0x08; docs/engine/rtti-and-vtables.md, "Naming slots in local views").
vtable-slots-check:
	python3 -m unittest discover -s testing -p 'test_check_vtable_slots.py'
	python3 scripts/check_vtable_slots.py

# Report (not a gate): local struct views that disagree with each other or with reflected.h,
# and offset-named members whose number is not their offset (scripts/check_struct_conflicts.py).
struct-report:
	python3 -m unittest discover -s testing -p 'test_check_struct_conflicts.py'
	python3 scripts/check_struct_conflicts.py

typed-scope:
	python3 tools/typed_scope.py --by-class

clean:
	rm -rf $(BUILD)
