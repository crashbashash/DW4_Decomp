#!/bin/sh
# Refresh data/ with the current Ghidra dumps from the analysed DW4 project.
#
# data/ is a committed SNAPSHOT of the dumps so the repo is readable and
# diffable without the 67 MB Ghidra project. The live copies stay where
# pyghidra-run writes them (ghidra-projects/dw4/); re-run this after a
# dump script to bring the snapshot up to date.
#
#   ./scripts/sync_data.sh [GHIDRA_PROJECT_DIR]
set -eu

REPO=$(cd "$(dirname "$0")/.." && pwd)
SRC=${1:-ghidra-projects/dw4}

if [ ! -d "$SRC" ]; then
    echo "sync_data: no such Ghidra project dir: $SRC" >&2
    exit 1
fi

mkdir -p "$REPO/data"

# tables / dumps written by scripts in scripts/
FILES="functions.json symbols.json strings.json script_api.json vtables.json reflection.json weapons.json
styled.json armor.json item_ids.json mods.json cores.json item_names.txt
lua_strings.txt afs_strings.txt lua_all_strings.txt lua_globals.txt
lua_filenames.txt lua_igb_paths.txt lua_stages.txt lua_sequences.txt
lua_missions.txt"

# Derived tables (not Ghidra dumps) that belong in data/ as well.
n=0
if [ -f "$REPO/orig/SLUS-20836/SLUS_208.36" ]; then
    python3 "$REPO/scripts/gen_class_hierarchy.py" >/dev/null \
        && n=$((n + 1)) || echo "sync_data: gen_class_hierarchy skipped" >&2
    python3 "$REPO/tools/sdk_bindings.py" --json "$REPO/data/sdk-bindings.json" >/dev/null \
        && n=$((n + 1)) || echo "sync_data: sdk_bindings skipped" >&2
    python3 "$REPO/scripts/seed_names_getvtable_slots.py" \
        --json "$REPO/data/vtables-getvtable.json" >/dev/null 2>&1 \
        && n=$((n + 1)) || echo "sync_data: getvtable map skipped" >&2
else
    echo "sync_data: no orig/SLUS-20836/SLUS_208.36; class-hierarchy.tsv not regenerated" >&2
fi

for f in $FILES; do
    [ -f "$SRC/$f" ] || { echo "sync_data: missing $f (skipped)" >&2; continue; }
    cp -p "$SRC/$f" "$REPO/data/$f"
    n=$((n + 1))
done


echo "sync_data: $n files -> $REPO/data ($(du -sh "$REPO/data" | cut -f1))"
