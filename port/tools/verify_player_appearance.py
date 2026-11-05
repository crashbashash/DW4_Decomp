#!/usr/bin/env python3
"""Compare Dorumon's held-camera arrival body and starter weapon with retail GS.

The RGB hashes identify the original P_dorumon01.png and w_common07.png texels.
This is an optional private-capture check, not a runtime dependency or a claim
of synchronized skeletal phase. Requires the repository analysis scripts, NumPy and Pillow.
"""
import argparse
import csv
import json
from pathlib import Path
import subprocess
import sys
import tempfile

import numpy as np
from PIL import Image

PORT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PORT.parent / "scripts"))
import gsdump  # noqa: E402

TEXTURES = {"body": 0xb3c84587, "weapon": 0x27bcf606}


def rgb_hash(rgba):
    result = 2166136261
    for value in np.frombuffer(rgba, np.uint8).reshape(-1, 4)[:, :3].flat:
        result = ((result ^ int(value)) * 16777619) & 0xffffffff
    return result


def compare(rows, dump):
    native = {name: np.array([[float(row[key]) for key in ("x", "y", "u", "v")]
                             for row in rows if int(row["texture_rgb_hash"], 16) == hash_])
              for name, hash_ in TEXTURES.items()}
    state = gsdump.read_state(dump)
    offset = state["CTXT0.XYOFFSET"]
    ox, oy = (offset & 0xffff)/16, ((offset >> 32) & 0xffff)/16
    textures, retail = {}, {name: [] for name in TEXTURES}
    for draw in gsdump.draws(dump):
        prim = draw["state"].get("PRIM_EFF", 0)
        if not prim & 16 or prim & 64:  # opaque textured pass; omit shadows
            continue
        tex0 = draw["state"].get(6, state["CTXT0.TEX0"])
        if tex0 not in textures:
            textures[tex0] = None
            if gsdump.tex0_fields(tex0)["PSM"] == 19:
                hash_ = rgb_hash(gsdump.texture_rgba(dump, tex0)[0])
                textures[tex0] = next((name for name, value in TEXTURES.items()
                                      if value == hash_), None)
        name = textures[tex0]
        if not name:
            continue
        for vertex in draw["verts"]:
            if "ST" not in vertex:
                continue
            s, t, q = vertex["ST"]
            if q:
                retail[name].append((vertex["XYZ"][0]/16-ox,
                                     vertex["XYZ"][1]/16-oy, s/q, t/q))
    report = {}
    for name, target in retail.items():
        points = native[name]
        assert len(points) > 100 and len(target) > 100, f"missing {name} submissions"
        errors = []
        for vertex in np.array(target):
            candidates = points[np.max(abs(points[:, 2:]-vertex[2:]), axis=1) < .001]
            if len(candidates):
                errors.append(float(np.min(np.linalg.norm(candidates[:, :2]-vertex[:2], axis=1))))
        assert len(errors) == len(target), f"unpaired {name} UVs"
        report[name] = {"native_vertices": len(points), "retail_instances": len(target),
                        "median_pixels": float(np.median(errors)),
                        "p95_pixels": float(np.quantile(errors, .95)),
                        "max_pixels": max(errors)}
    # Repeated UV seams use the closest candidate. The dump may contain several
    # skeletal phases; report the complete distribution instead of excluding outliers.
    assert report["weapon"]["p95_pixels"] < 1 and report["weapon"]["max_pixels"] < 1.5, report
    assert report["body"]["median_pixels"] < .5, report
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--roms", default=str(PORT.parent.parent / "local/extracted"))
    parser.add_argument("--tool", default=str(PORT / "build/lobby_frame"))
    parser.add_argument("--frame", type=int, default=339)
    parser.add_argument("--dump", required=True)
    parser.add_argument("--reference")
    parser.add_argument("--baseline")
    parser.add_argument("--json")
    args = parser.parse_args()
    with tempfile.TemporaryDirectory() as tmp:
        png, tsv = Path(tmp)/"frame.png", Path(tmp)/"vertices.tsv"
        subprocess.run([args.tool, args.roms, str(args.frame), str(png), str(tsv)],
                       check=True, stdout=subprocess.DEVNULL)
        with tsv.open() as file:
            report = compare(list(csv.DictReader(file, delimiter="\t")), gsdump.read_dump(args.dump))
        report["frame"] = args.frame
        if args.reference:
            reference = np.array(Image.open(args.reference).convert("RGB"), dtype=float)
            native = np.array(Image.open(png).convert("RGB"), dtype=float)
            assert reference.shape == native.shape == (448, 640, 3)
            # Fixed Dorumon/katana region. This also includes shadows/background;
            # retain these residuals rather than treating it as isolated mesh error.
            region = np.s_[165:240, 280:355]
            report["player_region_mae_255"] = float(abs(native-reference)[region].mean())
            if args.baseline:
                before = np.array(Image.open(args.baseline).convert("RGB"), dtype=float)
                assert before.shape == reference.shape
                report["baseline_region_mae_255"] = float(abs(before-reference)[region].mean())
                assert report["player_region_mae_255"] < report["baseline_region_mae_255"]
        output = json.dumps(report, indent=2)+"\n"
        if args.json:
            Path(args.json).write_text(output)
        print(output, end="")


if __name__ == "__main__":
    main()
