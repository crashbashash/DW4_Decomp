#!/usr/bin/env python3
"""gs_draw_state.py — per-draw render state out of a PCSX2 `.gs` dump.

Groups the dump's draw packets by their effective state (TEX0 + PRIM) and reports, per group:
the vertex count, the per-vertex RGBA census (the key question: does the colour vary, i.e. is the
draw lit, or is it a single constant RGBA, i.e. unlit?), and the ALPHA/TEST/ZBUF/FRAME/TEX1/CLAMP
registers in force.  This is the ground-truth the port's per-material state should reproduce.

    python3 scripts/gs_draw_state.py ../local/dumps/goblin_pass_ref.gs.zst
"""
import collections
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
import gsdump  # noqa: E402

# GIF register addresses (low byte of the A_D channel)
RG = {"PRIM": 0x00, "RGBAQ": 0x01, "ST": 0x02, "UV": 0x03, "XYZF2": 0x04,
      "TEX0_1": 0x06, "TEX0_2": 0x07, "CLAMP_1": 0x08, "CLAMP_2": 0x09,
      "FOG": 0x0a, "TEX1_1": 0x14, "TEX1_2": 0x15, "TEX2_1": 0x16, "TEX2_2": 0x17,
      "XYOFFSET_1": 0x18, "XYOFFSET_2": 0x19, "PRMODECONT": 0x1a, "TEXCLUT": 0x1c,
      "SCISSOR_1": 0x40, "SCISSOR_2": 0x41, "ALPHA_1": 0x42, "ALPHA_2": 0x43,
      "DTHE": 0x45, "COLCLAMP": 0x46, "TEST_1": 0x47, "TEST_2": 0x48,
      "FBA_1": 0x4a, "FBA_2": 0x4b, "FRAME_1": 0x4c, "FRAME_2": 0x4d,
      "ZBUF_1": 0x4e, "ZBUF_2": 0x4f}

# freeze-state key for the CTXT0 instance of each address (CTXT1 = the _2 twin, same key +1 slot)
_FREEZE_0 = {0x06: "CTXT0.TEX0", 0x08: "CTXT0.CLAMP", 0x14: "CTXT0.TEX1",
             0x18: "CTXT0.XYOFFSET", 0x40: "CTXT0.SCISSOR", 0x42: "CTXT0.ALPHA",
             0x47: "CTXT0.TEST", 0x4a: "CTXT0.FBA", 0x4c: "CTXT0.FRAME", 0x4e: "CTXT0.ZBUF",
             0x00: "PRIM", 0x01: "m_v.RGBAQ", 0x02: "m_v.ST", 0x03: "m_v.UV",
             0x0a: "m_v.FOG", 0x1a: "PRMODECONT", 0x1c: "TEXCLUT", 0x45: "DTHE",
             0x46: "COLCLAMP"}
_FREEZE_1 = {0x07: "CTXT1.TEX0", 0x09: "CTXT1.CLAMP", 0x15: "CTXT1.TEX1",
             0x19: "CTXT1.XYOFFSET", 0x41: "CTXT1.SCISSOR", 0x43: "CTXT1.ALPHA",
             0x48: "CTXT1.TEST", 0x4b: "CTXT1.FBA", 0x4d: "CTXT1.FRAME", 0x4f: "CTXT1.ZBUF"}


def freeze_base(fs):
    """The register map at frame start, keyed by GIF address.

    A_D only rewrites a handful of registers (here: TEX0 and a few), so the rest -- TEX1 in
    particular, which decides the filter -- must come from the freeze state.  Missing keys are left
    absent rather than invented as 0."""
    base = {}
    for addr, key in _FREEZE_0.items():
        if key in fs:
            base[addr] = fs[key]
    for addr, key in _FREEZE_1.items():
        if key in fs:
            base[addr] = fs[key]
    return base


def alpha_fields(v):
    return dict(A=(v >> 0) & 3, B=(v >> 2) & 3, C=(v >> 4) & 3, D=(v >> 6) & 3, FIX=(v >> 32) & 0xff)


def test_fields(v):
    return dict(ATE=(v >> 0) & 1, ATST=(v >> 1) & 7, AREF=(v >> 4) & 0xff,
                AFAIL=(v >> 12) & 3, ZTE=(v >> 16) & 1, ZTST=(v >> 17) & 3)


def main(path):
    d = gsdump.read_dump(path)
    fs = gsdump.read_state(d)
    base = freeze_base(fs)
    groups = collections.OrderedDict()
    for dr in gsdump.draws(d):
        st = dict(base)
        st.update(dr["state"])
        key = (st.get(RG["TEX0_1"]), st.get("PRIM_EFF"))
        g = groups.get(key)
        if g is None:
            g = groups[key] = {"n": 0, "ndraw": 0, "rgba": [255, 255, 255, 255], "rgba_hi": [0, 0, 0, 0],
                               "uniq": set(), "state": dict(st)}
            # first sight of this state: keep the full register snapshot
        g["n"] += dr["n"]
        g["ndraw"] += 1
        for v in dr["verts"]:
            r = v["RGBA"]
            for c in range(4):
                g["rgba"][c] = min(g["rgba"][c], r[c])
                g["rgba_hi"][c] = max(g["rgba_hi"][c], r[c])
            if len(g["uniq"]) < 4096:
                g["uniq"].add(r)
        # merge newly-seen registers so the snapshot is complete
        for k, v in st.items():
            g["state"].setdefault(k, v)

    print("dump %s : freeze PRIM %#x RGBAQ %s" % (
        path, fs["PRIM"], fs["m_v.RGBAQ"]))
    print("groups: %d (TEX0 x PRIM_EFF)\n" % len(groups))
    for i, ((t0, prim), g) in enumerate(groups.items()):
        if t0 is None:
            continue
        tf = gsdump.tex0_fields(t0)
        pf = gsdump.prim_fields(prim) if prim is not None else {"PRIM": -1, "TME": 0, "ABE": 0, "IIP": 0}
        s = g["state"]
        ctx = pf.get("CTXT", 0)
        a = alpha_fields(s.get(RG["ALPHA_1"] + ctx, 0))
        t = test_fields(s.get(RG["TEST_1"] + ctx, 0))
        e1 = gsdump.tex1_fields(s.get(RG["TEX1_1"] + ctx, 0))
        const = (g["rgba"] == g["rgba_hi"])
        print("[%2d] TEX0 %#018x TBP %#06x %dx%d PSM %d | PRIM %#x type %s TME %d ABE %d IIP %d"
              % (i, t0, tf["TBP0"], tf["TW"], tf["TH"], tf["PSM"], prim, pf["PRIM"],
                 pf["TME"], pf["ABE"], pf["IIP"]))
        print("     verts %d in %d packet(s) | #distinct RGBA %d  range R%d..%d G%d..%d B%d..%d A%d..%d%s"
              % (g["n"], g["ndraw"], len(g["uniq"]),
                 g["rgba"][0], g["rgba_hi"][0], g["rgba"][1], g["rgba_hi"][1],
                 g["rgba"][2], g["rgba_hi"][2], g["rgba"][3], g["rgba_hi"][3],
                 "  ** CONSTANT (unlit) **" if const else "  (varies -> lit/gouraud)"))
        print("     ALPHA A%d B%d C%d D%d FIX %d | TEST ATE %d ATST %d AREF %#x AFAIL %d ZTE %d ZTST %d"
              % (a["A"], a["B"], a["C"], a["D"], a["FIX"], t["ATE"], t["ATST"], t["AREF"],
                 t["AFAIL"], t["ZTE"], t["ZTST"]))
        print("     TEX1 MMAG %d MMIN %d MXL %d | TEXCLUT %s | ZBUF %s | FBA %s | COLCLAMP %s | DTHE %s"
              % (e1["MMAG"], e1["MMIN"], e1["MXL"], s.get(RG["TEXCLUT"]),
                 s.get(RG["ZBUF_1"] + ctx), s.get(RG["FBA_1"] + ctx), s.get(RG["COLCLAMP"]),
                 s.get(RG["DTHE"])))
        print()
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1]))
