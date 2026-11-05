#!/usr/bin/env python3
"""Compare an arrival frame's vertices with a retail GS capture at the same camera pose.

Requires the workspace's scripts/gsdump.py, NumPy, SciPy and Pillow. Game assets
and captures stay outside the repository. Seam vertices with multiple different
candidate colours are excluded before consulting the retail colour.

make build/lobby_frame
python3 tools/verify_lobby_render.py --dump /path/lobby.gs.zst \
    --reference /path/lobby.png --out /path/comparison.png
"""
import argparse
import csv
import json
from pathlib import Path
import subprocess
import sys
import tempfile

import numpy as np
from PIL import Image, ImageDraw
from scipy.spatial import cKDTree

PORT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PORT.parent / "scripts"))
import gsdump  # noqa: E402
from verify_player_appearance import TEXTURES, rgb_hash  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--roms", default=str(PORT.parent.parent / "local/extracted"))
    ap.add_argument("--tool", default=str(PORT / "build/lobby_frame"))
    ap.add_argument("--frame", type=int, default=323)
    ap.add_argument("--light", choices=("hard", "soft"), default="hard")
    ap.add_argument("--held-world", action="store_true",
                    help="use the fixed greeting environment region, excluding unsynchronized actors")
    ap.add_argument("--dump", required=True)
    ap.add_argument("--reference")
    ap.add_argument("--baseline")
    ap.add_argument("--out")
    ap.add_argument("--json")
    args = ap.parse_args()
    with tempfile.TemporaryDirectory() as tmp:
        png, tsv = Path(tmp)/"frame.png", Path(tmp)/"vertices.tsv"
        subprocess.run([args.tool, args.roms, str(args.frame), str(png), str(tsv), "--"+args.light], check=True,
                       stdout=subprocess.DEVNULL)
        rows = list(csv.DictReader(tsv.open(), delimiter="\t"))
        pos = np.array([[float(r[k]) for k in ("x", "y")] for r in rows])
        uv = np.array([[float(r[k]) for k in ("u", "v")] for r in rows])
        colors = np.array([[int(r[k]) for k in ("r", "g", "b")] for r in rows])
        fog = np.array([int(r["fog"]) for r in rows])
        texture_hashes = np.array([int(r["texture_rgb_hash"], 16) for r in rows])
        # The held-camera capture is not synchronized to the native player's
        # skeletal phase. Keep its newly matched colours as separate evidence;
        # the strict static-world lighting oracle retains its original tolerance.
        player = np.array([int(r["texture_rgb_hash"], 16) in TEXTURES.values() for r in rows])
        tree = cKDTree(pos)
        dump = gsdump.read_dump(args.dump)
        state = gsdump.read_state(dump)
        offset = state["CTXT0.XYOFFSET"]
        ox, oy = (offset & 0xffff)/16, ((offset >> 32) & 0xffff)/16
        matched, actor_matches, fog_matches, ambiguous = [], [], [], 0
        textures, texture_matches = {}, []
        for draw in gsdump.draws(dump):
            prim = draw["state"].get("PRIM_EFF", 0)
            if not prim & 16 or prim & 64:  # opaque, textured draws only; excludes shadow multipasses
                continue
            for vertex in draw["verts"]:
                if "ST" not in vertex:
                    continue
                s, t, q = vertex["ST"]
                x, y = vertex["XYZ"][0]/16-ox, vertex["XYZ"][1]/16-oy
                if not q or not (0 <= x < 640 and 0 <= y < 448):
                    continue
                if args.held_world and (y >= 280 or
                        (190 <= x < 390 and 150 <= y < 280) or
                        (575 <= x and 180 <= y < 280)):
                    continue
                ids = [i for i in tree.query_ball_point((x, y), .25)
                       if np.max(abs(uv[i]-np.array((s, t))/q)) < .001]
                candidates = {tuple(colors[i]) for i in ids}
                fog_candidates = {fog[i] for i in ids}
                if len(fog_candidates) == 1 and prim & 32 and "FOG" in vertex:
                    fog_matches.append((next(iter(fog_candidates)), vertex["FOG"]))
                if len(candidates) == 1:
                    if all(player[i] for i in ids):
                        actor_matches.append((next(iter(candidates)), vertex["RGBA"][:3]))
                    elif not any(player[i] for i in ids):
                        matched.append((next(iter(candidates)), vertex["RGBA"][:3]))
                        if args.held_world and len(set(texture_hashes[ids])) == 1:
                            tex0 = draw["state"].get(6, state["CTXT0.TEX0"])
                            if gsdump.tex0_fields(tex0)["PSM"] == 19:
                                if tex0 not in textures:
                                    textures[tex0] = rgb_hash(gsdump.texture_rgba(dump, tex0)[0])
                                texture_matches.append(texture_hashes[ids[0]] == textures[tex0])
                elif candidates:
                    ambiguous += 1
        assert len(matched) > 1000, "camera/UV correspondence failed: too few retail matches"
        delta = abs(np.array([a for a, _ in matched])-np.array([b for _, b in matched]))
        report = {"frame": args.frame, "light": args.light, "held_world": args.held_world,
                  "matched_vertices": len(matched),
                  "ambiguous_seams_excluded": ambiguous, "colour_mae_255": float(delta.mean()),
                  "fraction_within_one": float((delta.max(axis=1) <= 1).mean())}
        if actor_matches:
            adelta = abs(np.array([a for a, _ in actor_matches])-np.array([b for _, b in actor_matches]))
            report["player_colour"] = {"matched_instances": len(actor_matches),
                                       "mae_255": float(adelta.mean()),
                                       "fraction_within_one": float((adelta.max(axis=1) <= 1).mean()),
                                       "max_channel_error": int(adelta.max())}
        assert report["fraction_within_one"] > .999, report
        if args.held_world:
            assert len(texture_matches) > 1000, "missing texture comparisons"
            report.update(texture_vertices=len(texture_matches),
                          texture_rgb_fraction_exact=float(np.mean(texture_matches)))
            assert report["texture_rgb_fraction_exact"] == 1, report
        assert len(fog_matches) > 1000, "missing retail fog samples"
        fdelta = abs(np.array([a for a, _ in fog_matches])-np.array([b for _, b in fog_matches]))
        report.update(fog_vertices=len(fog_matches), fog_mae_255=float(fdelta.mean()),
                      fog_fraction_within_one=float((fdelta <= 1).mean()))
        assert report["fog_fraction_within_one"] > .999, report
        if args.reference:
            retail = Image.open(args.reference).convert("RGB")
            native = Image.open(png).convert("RGB")
            assert retail.size == native.size == (640, 448), "use the native 640x448 GS frame"
            a, b = np.array(native).astype(int), np.array(retail).astype(int)
            # Fixed environment region for the first greeting camera: omit the message
            # window and the player/NPC silhouettes (task 3), retain portal and walls.
            mask = np.zeros((448, 640), dtype=bool)
            mask[:280] = True
            mask[150:280, 190:390] = False
            mask[180:280, 575:] = False
            report["environment_mae_255"] = float(abs(a-b)[mask].mean())
            panels = [("Retail", retail), ("Native", native)]
            if args.baseline:
                baseline = Image.open(args.baseline).convert("RGB")
                assert baseline.size == native.size
                report["baseline_environment_mae_255"] = float(abs(np.array(baseline).astype(int)-b)[mask].mean())
                panels.insert(1, ("Before", baseline))
            diff = Image.fromarray(np.minimum(255, abs(a-b)*4).astype("uint8"))
            panels.append(("Difference x4 (includes UI / actors)", diff))
            if args.out:
                canvas = Image.new("RGB", (640*len(panels), 472), "#121820")
                label = ImageDraw.Draw(canvas)
                for i, (title, im) in enumerate(panels):
                    label.text((i*640+10, 6), title, fill="white")
                    canvas.paste(im, (i*640, 24))
                canvas.save(args.out)
        if args.json:
            Path(args.json).write_text(json.dumps(report, indent=2)+"\n")
        print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
