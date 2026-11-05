#!/usr/bin/env python3
"""Compare exported STATUS submissions with a private retail GS dump.

Export with test_statusviews ROMS ROOT.png EXISTING_DIRECTORY. Root 0 uses
fresh Dorumon `aa`, matching the documented retail reference. This comparison
checks native vertices against retail candidates, not full-frame equivalence.
Unmatched vertices remain failures, including unsynchronized animation. Use
--report-only to retain a diagnostic without asserting overall parity.
"""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import sys

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "scripts"))
import gsdump


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--dump", required=True)
    p.add_argument("--native-dir", type=Path, required=True)
    p.add_argument("--root", "--frame", dest="root", type=int, default=0,
                   help="exported frame number; frames.tsv identifies player/view")
    p.add_argument("--json", type=Path)
    p.add_argument("--retail-vsync",type=int,
                   help="restrict retail candidates to one interval between dump vsync records")
    p.add_argument("--depth",action="store_true",help="also require hardware Z within one unit, exact depth test/write, color write mask and nearest/linear sampling")
    p.add_argument("--report-only", action="store_true")
    a = p.parse_args()
    assert a.root >= 0, "negative frame number"
    assert a.retail_vsync is None or a.retail_vsync>=0,"negative retail vsync interval"
    dump = gsdump.read_dump(a.dump)
    state = gsdump.read_state(dump)
    offset = state["CTXT0.XYOFFSET"]
    ox, oy = (offset & 65535) / 16, ((offset >> 32) & 65535) / 16
    textures, retail = {}, {}
    for draw in gsdump.draws(dump):
        if a.retail_vsync is not None and draw['vsync']!=a.retail_vsync:
            continue
        if not draw["state"]["PRIM_EFF"] & 16: # PRIM.TME, independent of ABE
            continue
        tex0 = draw["state"].get(6, state["CTXT0.TEX0"])
        if tex0 not in textures:
            # This decoder supports PSMT8. Unsupported retail textures cannot
            # establish matches, and remain absent rather than being fabricated.
            if gsdump.tex0_fields(tex0)["PSM"] != 19:
                textures[tex0] = None
            else:
                rgba, w, h, _ = gsdump.texture_rgba(dump, tex0)
                textures[tex0] = (hashlib.sha256(rgba).hexdigest(), w, h)
        key = textures[tex0]
        if key is None:
            continue
        for v in draw["verts"]:
            if "ST" not in v or not v["ST"][2]:
                continue
            s, t, q = v["ST"]
            test=draw['state'].get(0x47,state['CTXT0.TEST'])
            zbuf=draw['state'].get(0x4e,state['CTXT0.ZBUF'])
            mode=2 if (test>>17)&3==1 else 1 if (test>>17)&3==2 else -1
            tex1=gsdump.tex1_fields(draw['state'].get(0x14,state['CTXT0.TEX1']))
            filtering=1 if (tex1['MMAG'],tex1['MMIN'])==(0,0) else 2 if (tex1['MMAG'],tex1['MMIN'])==(1,1) else -1
            frame=draw['state'].get(0x4c,state['CTXT0.FRAME'])>>32
            mask=sum(1<<k for k in range(4) if (frame>>(8*k))&255==255)
            if any((frame>>(8*k))&255 not in (0,255) for k in range(4)):mask=-1
            retail.setdefault(key, []).append((v["XYZ"][0] / 16 - ox,
                v["XYZ"][1] / 16 - oy, s / q, t / q, q, *v["RGBA"],v['Z'],mode,1-((zbuf>>32)&1),filtering,mask))
    rows = list(csv.DictReader((a.native_dir / f"root-{a.root}.tsv").open(), delimiter="\t"))
    assert rows, "empty native submission"
    assert 'q' in rows[0], "regenerate native exports to include reciprocal Q"
    assert not a.depth or all(k in rows[0] for k in ('z','depth','depth_write','filter','color_mask')),"regenerate native depth/filter exports"
    report = {"scope": "native-to-retail vertex candidates; full-frame parity unproven",
              "position_tolerance_px": .126, "uv_tolerance": .002,
              "q_relative_tolerance": .00002, "q_absolute_tolerance": 1e-8, "groups": {}}
    report['retail_vsync']=a.retail_vsync
    report['depth_checked']=a.depth
    report['color_mask_checked']=a.depth
    for part, idx in sorted({(r["part"], r["texture"]) for r in rows}):
        im = Image.open(a.native_dir / f"root-{a.root}-{part}-{idx}.png").convert("RGBA")
        key = (hashlib.sha256(im.tobytes()).hexdigest(), im.width, im.height)
        native = [r for r in rows if (r["part"], r["texture"]) == (part, idx)]
        candidates = np.array(retail.get(key, []), dtype=float).reshape(-1, 14)
        errors, q_errors, matched, uv_missing = [], [], 0, 0
        examples=[]
        for v in native:
            uv = np.array([float(v["u"]), float(v["v"])])
            same = candidates[(abs(candidates[:, 2:4] - uv) < .002).all(axis=1)]
            if not len(same):
                uv_missing += 1
                if len(examples)<6:examples.append({k:v[k] for k in ('triangle','x','y','u','v')})
                continue
            xy = np.array([float(v["x"]), float(v["y"])])
            delta = abs(same[:, :2] - xy).max(axis=1)
            rgba = np.array([int(v[k]) for k in ("r", "g", "b", "a")])
            positioned=same[(delta <= .126) & (same[:, 5:9] == rgba).all(axis=1)]
            nq=float(v['q'])
            weighted=(same[:,5:9] == rgba).all(axis=1) & (abs(same[:,4]-nq) <= 1e-8 + .00002*abs(same[:,4]))
            if a.depth:
                weighted &= (abs(same[:,9]-float(v['z']))<=1) & (same[:,10]==int(v['depth'])) & (same[:,11]==int(v['depth_write'])) & (same[:,12]==int(v['filter'])) & (same[:,13]==int(v['color_mask']))
            if weighted.any():
                error=float(delta[weighted].min());errors.append(error);matched += int(error <= .126)
            if (not weighted.any() or delta[weighted].min()>.126) and len(examples)<6:
                examples.append({k:v[k] for k in ('triangle','x','y','u','v')})
            if len(positioned):
                qdelta=abs(positioned[:,4]-nq)
                q_errors.append(float((qdelta/abs(positioned[:,4])).min()))
        report["groups"][f"{part}-{idx}"] = {"size": im.size,
            "texture_rgba_byte_exact": key in retail, "vertices": len(native),
            "position_uv_color_q_matches": matched, "missing_uv_candidates": uv_missing,
            "max_position_error_px": max(errors) if errors else None,
            "max_relative_q_error": max(q_errors) if q_errors else None,
            "unmatched_vertex_examples": examples}
    report["all_native_vertices_match"] = all(g["position_uv_color_q_matches"] == g["vertices"]
        and g["texture_rgba_byte_exact"] for g in report["groups"].values())
    result = json.dumps(report, indent=2) + "\n"
    if a.json:
        a.json.write_text(result)
    print(result, end="")
    return 0 if a.report_only or report["all_native_vertices_match"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
