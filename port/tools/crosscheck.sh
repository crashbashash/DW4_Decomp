#!/bin/sh
# crosscheck.sh — verify the C reader against the repository's Python decoders.
#
# The C layer (src/) and the recovered decoders (DW4_Decomp/scripts/igb_dir.py,
# igb_inst.py) implement the same layout, so they must agree on every count, offset
# and name.  This runs both over the real archives and diffs the numbers; it is the
# asset layer's regression test, and the reason the CLI prints facts rather than prose.
#
#   tools/crosscheck.sh            manifest + one model pack (fast)
#   tools/crosscheck.sh --full     adds the stage manifest and a generator pack
set -e

# Both sides are compared as sorted text: pin the collation so the result does not depend on the caller's locale.
LC_ALL=C; export LC_ALL

here=$(dirname "$0")
port=$(cd "$here/.." && pwd)
repo=${DW4_DECOMP:-$port/..}
roms=${DW4_ROMS:-$port/../../local/extracted}
tool=$port/build/dw4asset
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

if [ ! -x "$tool" ]; then
    echo "crosscheck: build first (make)" >&2
    exit 2
fi
if [ ! -f "$repo/scripts/igb_inst.py" ]; then
    echo "crosscheck: set DW4_DECOMP to the decompilation checkout" >&2
    exit 2
fi
if [ ! -f "$roms/NDMW.AFS" ]; then
    echo "crosscheck: set DW4_ROMS to a directory holding NDMW.AFS / NDMW.IGB" >&2
    exit 2
fi

# The record line the C tool prints:
#   "records: chain +0x.. N record(s), B bytes, +A .. +Z"
c_facts() {
    "$tool" igb "$@" |
        sed -n -e 's/.*records: chain +0x\([0-9a-f]*\), \([0-9]*\) record(s), \([0-9]*\) bytes, +0x\([0-9a-f]*\) \.\. +0x\([0-9a-f]*\).*/\1 \2 \3 \4 \5/p' \
               -e 's/  header\[3\] classes \([0-9]*\)   walked \([0-9]*\).*/classes \1 \2/p'
}

# The same facts from the Python decoder, for a blob offset inside an AFS entry.
p_facts() {
    python3 "$repo/scripts/igb_inst.py" "$roms/NDMW.AFS" --blob "$1" | sed -n \
        -e 's/type directory: \([0-9]*\) classes, +0x\([0-9a-f]*\) \.\. +0x\([0-9a-f]*\).*/classes \1 dir \2 \3/p' \
        -e 's/records: \([0-9]*\), \([0-9]*\) bytes, +0x\([0-9a-f]*\) \.\. +0x\([0-9a-f]*\).*/records \1 \2 \3 \4/p'
}

entry_blob() {
    python3 - "$roms/NDMW.AFS" "$1" <<'PY'
import struct, sys
d = open(sys.argv[1], 'rb').read(8 + 8 * 2048)
print('0x%x' % struct.unpack_from('<I', d, 8 + 8 * int(sys.argv[2]))[0])
PY
}

check_entry() {
    index=$1
    off=$(entry_blob "$index")
    echo "== NDMW.AFS entry $index (blob $off)"
    c=$(c_facts --afs "$roms/NDMW.AFS" --entry "$index")
    p=$(p_facts "$off")
    c_cls=$(echo "$c" | sed -n 's/^classes \([0-9]*\) [0-9]*$/\1/p')
    c_rec=$(echo "$c" | sed -n 's/^[0-9a-f]* \([0-9]*\) \([0-9]*\) \([0-9a-f]*\) \([0-9a-f]*\)$/\1 \2 \3 \4/p')
    p_cls=$(echo "$p" | sed -n 's/^classes \([0-9]*\) .*/\1/p')
    p_rec=$(echo "$p" | sed -n 's/^records \([0-9]*\) \([0-9]*\) \([0-9a-f]*\) \([0-9a-f]*\)$/\1 \2 \3 \4/p')
    if [ "$c_cls" != "$p_cls" ] || [ "$c_rec" != "$p_rec" ]; then
        echo "   MISMATCH: C says '$c_cls / $c_rec', python says '$p_cls / $p_rec'" >&2
        exit 1
    fi
    echo "   agree: $c_cls classes, records $c_rec"
}

# The id remap table and the content-pool blocks (findings #460/#464).  The C reader and
# the repository's igb_ids.py + igb_pool.py must agree on the table location, the id
# split (objects vs pool blocks) and the pool accounting.
check_refs() {
    index=$1
    off=$(entry_blob "$index")
    echo "== refs (id remap table + pool blocks) entry $index"
    ctab=$("$tool" refs --afs "$roms/NDMW.AFS" --entry "$index" |
        sed -n 's/.*table +0x\([0-9a-f]*\): \([0-9]*\) id(s), \([0-9]*\) object(s), \([0-9]*\) block(s).*/\1 \2 \3 \4/p')
    cpool=$("$tool" refs --afs "$roms/NDMW.AFS" --entry "$index" |
        sed -n 's/.*pool +0x\([0-9a-f]*\): \([0-9]*\) of \([0-9]*\) bytes accounted.*/\1 \2 \3/p' | cut -d' ' -f1,2)
    ptab=$(python3 "$repo/scripts/igb_ids.py" "$roms/NDMW.AFS" --blob "$off" |
        sed -n 's/.*table @+0x\([0-9a-f]*\): \([0-9]*\) ids (\([0-9]*\) objects + \([0-9]*\) memory blocks).*/\1 \2 \3 \4/p')
    ppool=$(python3 "$repo/scripts/igb_pool.py" "$roms/NDMW.AFS" --blob "$off" |
        sed -n 's/.*pool @+0x\([0-9a-f]*\), \([0-9]*\) bytes; \([0-9]*\) pool blocks, id sizes sum to \([0-9]*\).*/\1 \2 \3 \4/p' | cut -d' ' -f1,4)
    c="$ctab $cpool"
    p="$ptab $ppool"
    if [ "$c" != "$p" ]; then
        echo "   MISMATCH: C says '$c', python says '$p'" >&2
        exit 1
    fi
    echo "   agree: table_off ids objects blocks pool_off pool_sum = $c"
}

echo "== NDMW.IGB (the manifest as an igBinary container)"
"$tool" igb "$roms/NDMW.IGB" | grep -E "classes|records:" | sed 's/^/   /'
"$tool" igb "$roms/NDMW.IGB" | grep -q "2297 record(s)" || {
    echo "   expected the manifest's 2297-record chain" >&2; exit 1; }
echo "   ok"

echo "== NDMW.IGB manifest table (name -> archive entry), C vs Python"
"$tool" manifest "$roms/NDMW.IGB" --all | sort > "$tmp/c.tsv"
python3 - "$repo" "$roms/NDMW.IGB" "$tmp/py.tsv" <<'PY'
import json, os, subprocess, sys, tempfile
repo, igb, out = sys.argv[1], sys.argv[2], sys.argv[3]
with tempfile.NamedTemporaryFile(suffix='.json', delete=False) as f:
    js = f.name
subprocess.run([sys.executable, os.path.join(repo, 'scripts', 'igb_inst.py'), igb,
                '--blob', '0', '--class', 'igAdxAfsFile',
                '--reflection', os.path.join(repo, 'data', 'reflection.json'),
                '--json', js], check=True, stdout=subprocess.DEVNULL)
rows = []
for r in json.load(open(js)):
    val = {n: v for n, v, _t in r['fields']}
    name = (val.get('_name') or '').rstrip('\x00')
    if val.get('_ptNumber') is None:
        continue
    rows.append('%s\t%d\t%d' % (name, val['_ptNumber'], val['_fileNumber']))
open(out, 'w').write('\n'.join(sorted(rows)) + '\n')
os.unlink(js)
PY
if ! diff -q "$tmp/c.tsv" "$tmp/py.tsv" >/dev/null; then
    echo "   MISMATCH:" >&2
    diff "$tmp/c.tsv" "$tmp/py.tsv" | head -10 >&2
    exit 1
fi
echo "   agree: $(wc -l < "$tmp/c.tsv" | tr -d ' ') names"
"$tool" manifest "$roms/NDMW.IGB" | sed -n '2,4p' | sed 's/^/   /'

echo "== the mounted tree (manifest + both archives)"
"$tool" mount "$roms" check | sed 's/^/   /'
"$tool" mount "$roms" check | grep -q "2079 named files with an entry, all resolve" || {
    echo "   expected every named file to resolve" >&2; exit 1; }

echo "== a stage's [pt.entry] pack references, resolved"
"$tool" mount "$roms" refs stag0102.igb | sed 's/^/   /'
"$tool" mount "$roms" refs stag0102.igb | grep -q "entry 620       494084 bytes" || {
    echo "   expected [0.620] -> NDMW.AFS entry 620 (494084 bytes)" >&2; exit 1; }
"$tool" mount "$roms" refs stag0102.igb | grep -q "entry 621      5060706 bytes" || {
    echo "   expected [0.621] -> NDMW.AFS entry 621 (5060706 bytes)" >&2; exit 1; }
# stag0201's packs are the ones the live model-residency experiment swapped in
"$tool" mount "$roms" refs stag0201.igb | grep -q "entry 642      5173220 bytes" || {
    echo "   expected [0.642] -> NDMW.AFS entry 642 (5173220 bytes)" >&2; exit 1; }
echo "   ok"

echo "== name -> bytes (find stag0102.igb == AFS entry 140)"
"$tool" find "$roms/NDMW.IGB" "$roms" stag0102.igb "$tmp/found.bin" | sed 's/^/   /'
"$tool" cat "$roms/NDMW.AFS" 140 "$tmp/direct.bin" > /dev/null
cmp "$tmp/found.bin" "$tmp/direct.bin" || { echo "   bytes differ" >&2; exit 1; }
echo "   identical to the direct entry"

echo "== the media path (Sofdec .sfd -> ffmpeg)"
"$tool" media "$roms" list | sed 's/^/   /'
[ "$("$tool" media "$roms" list | wc -l | tr -d ' ')" = "3" ] || {
    echo "   expected the 3 .sfd movies" >&2; exit 1; }
"$tool" media "$roms" probe aeu_opening.sfd 2>&1 | grep -q "adpcm_adx" || {
    echo "   expected ADX audio in the Sofdec container" >&2; exit 1; }
"$tool" media "$roms" probe aeu_opening.sfd 2>&1 | grep -q "mpeg1video" || {
    echo "   expected MPEG-1 video in the Sofdec container" >&2; exit 1; }
"$tool" media "$roms" convert aeu_opening.sfd "$tmp/clip.mp4" -t 2 >/dev/null
ffprobe -hide_banner "$tmp/clip.mp4" 2>&1 | grep -q "h264" || {
    echo "   expected the converted clip to be h264" >&2; exit 1; }
echo "   ok: Sofdec -> h264/AAC"

echo "== the sound pack (CRI ps2_ banks -> VAG ADPCM -> WAV, exact vs ffmpeg)"
"$tool" sfp --afs "$roms/NDMW.AFS" --entry 620 | sed 's/^/   /'
"$tool" sfp --afs "$roms/NDMW.AFS" --entry 620 | grep -q "6 sound bank(s)" || {
    echo "   expected the 6 banks of NDMW.AFS entry 620" >&2; exit 1; }
"$tool" cat "$roms/NDMW.AFS" 620 "$tmp/sound620.bin" > /dev/null
python3 "$port/tools/verify_sound.py" "$tool" "$tmp/sound620.bin" | sed 's/^/   /'

echo "== the texture decoder (pixel-exact against a reference)"
python3 "$port/tools/verify_texture.py" "$tool" | sed 's/^/   /'

echo "== the texture-pack reader (ids, block offsets and pixels, C vs Python)"
python3 "$port/tools/verify_texpack.py" --tool "$tool" --afs "$roms/NDMW.AFS" \
    --repo "$repo" | sed 's/^/   /'

echo "== the scene loader (arena + handles; engine route, C vs C, C vs Python)"
python3 "$port/tools/verify_scene.py" --tool "$tool" --roms "$roms" \
    --repo "$repo" | sed 's/^/   /'

echo "== the rasteriser (nothing drawn is the failure mode; runs are deterministic)"
# The stage-framing half needs a live scene capture (placement is not in the pack).  Point
# DW4_SCENE at a `capture_scene.py` TSV to exercise it; otherwise only the pack camera is checked.
scene_arg=""
[ -n "$DW4_SCENE" ] && [ -f "$DW4_SCENE" ] && scene_arg="--scene $DW4_SCENE"
livedump_arg=""
[ -n "$DW4_LIVEDUMP" ] && [ -f "$DW4_LIVEDUMP" ] && livedump_arg="--livedump $DW4_LIVEDUMP"
python3 "$port/tools/verify_render.py" --tool "$tool" --roms "$roms" $scene_arg $livedump_arg \
    | sed 's/^/   /'

echo "== the model reader (stream table, counts and OBJ bytes, C vs Python)"
python3 "$port/tools/verify_models.py" --tool "$tool" --afs "$roms/NDMW.AFS" \
    --repo "$repo" | sed 's/^/   /'

echo "== the skinning path (runtime blend stream + matrix palette, C vs Python)"
python3 "$port/tools/verify_skin.py" --tool "$tool" \
    ${DW4_LIVEDUMP:+--ram "$DW4_LIVEDUMP"} \
    --script "$port/../scripts/live_skin.py" | sed 's/^/   /'

check_entry 621
check_refs 622
check_refs 183

if [ "$1" = "--full" ]; then
    check_entry 140
    check_entry 622
    check_refs 621
    check_refs 140
fi

echo "crosscheck: all agreed"
