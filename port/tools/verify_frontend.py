#!/usr/bin/env python3
"""verify_frontend.py — the port boots to the title, presents it, stops for input, and (on Game
Start) follows the Game Start branch to the first playable stage (porting §4; boot-contract W1/W2).

The `dw4` host with `--boot` must not jump straight into a stage.  The recovered front-end (finding
#606) is a boot/attract chain that *stops at the title* and waits for the pad:

  boot/attract chain:  menu-database (AFS 800) -> bandai-logo (802, scene stagis09) -> opening
                       (804, stagis10) -> title-screen (806, stagML11)   -- then STOP.
  Game Start branch:   character-select-1/2/3 (808/810/812)  -- entered only on Cross at the title.
  hand-off:            the Main Lobby, stagML11 (packs 820 + 819), which the host then loads.

Two runs are checked:

  1. `--boot --headless` with no input: the boot chain runs, the title is presented (the game's own
     font from bectext.igb + the stagML11 backdrop + the menu rows) and the host STOPS there — it
     must NOT reach the world, and it must write a title frame.
  2. `--boot --headless --input-script <cross>`: a scripted Cross on Game Start advances the Game
     Start branch and the host enters stagml11.

Every claim is checked against the disc too: each entry's own bytes must carry the NEXTSTAGE token
the plan expects, each scene stage must resolve to real packs, and the hand-off stage must produce a
frame.

  tools/verify_frontend.py [--tool build/dw4] [--roms <dir>]
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)
DEFAULT_ROMS = os.path.join(PORT, "..", "..", "local/extracted")

# the recovered plan: (AFS entry, tree name, scene stage, expected NEXTSTAGE token)
BOOT_CHAIN = [
    (800, "menu-database", None, "stagML11"),
    (802, "bandai-logo", "stagis09", "stagis09"),
    (804, "opening", "stagis10", "stagis10"),
    (806, "title-screen", "stagML11", "stagML11"),
]
GAME_BRANCH = [
    (808, "character-select-1", "stagis11", "stagML11"),
    (810, "character-select-2", "stagis12", "stagML11"),
    (812, "character-select-3", "stagis13", "stagML11"),
]
PLAN = BOOT_CHAIN + GAME_BRANCH
FIRST_STAGE = "stagml11.igb"

# The front-end trail layer is generated from the pack's own model controller (findings
# #610/#614/#619): AREA.AFS entry 620's `j_startback` graph, its JOINTSET schedule and its
# `sback00` texture.  It is part of the shipped path — no capture directory and no flag.
LAYER_LINE = "front-end layer: j_startback, 16 mesh(es)"
# The layer's camera is recovered from the pack, not calibrated (finding #630): the title's
# `SETDEMOCAMERA "entry"` demo path composes to an on-axis eye at world z = 730.  The port must
# resolve that chain and must not fall back to a calibrated distance or a missing camera.
CAM_RE = re.compile(r"front-end layer camera: 'cameraanimShape01' eye \(([-\d.]+) ([-\d.]+) ([-\d.]+)\)")

# The title's own UI tree (findings #632/#633) is the pack's `AREA.AFS` 620 graphs `j_startlogo`
# (the `rogo` logo quad + `kenri` copyright) and `j_startmenu01`/`02` (the rows), each geometry's
# texture resolved through the pack's material chain.  It is part of the shipped path, and it
# resolves four image identities under three names -- the logo, separate row/copyright atlases
# and the cursor -- eagerly at open (not a lazy-load zero).
UI_RE = re.compile(r"front-end UI: (\d+) item\(s\), (\d+) texture\(s\): (.*)")
UI_LOGO_RE = re.compile(r"front-end UI: logo=(\S+)")
UI_RECT_RE = re.compile(r"front-end UI: logo rect x ([-.\d]+)\.\.([-.\d]+) y ([-.\d]+)\.\.([-.\d]+)"
                        r" \(at (\d+)x(\d+)\)")
UI_OPEN_RE = re.compile(r"front-end UI: logo rect at OPEN t=0 x ([-.\d]+)\.\.([-.\d]+)"
                        r" y ([-.\d]+)\.\.([-.\d]+)")
EXPECT_TEXTURES = ["cursor.png", "logo.png", "mojips.png", "mojips.png"]
# The recovered composition order (findings #609/#610/#632/#636): the static stagML11 backdrop is
# composed under the generated layer and the native UI, through the recovered title camera.
BACKDROP_RE = re.compile(r"front-end title: stagML11 backdrop composed under the layer"
                         r" \((\d+) mesh\(es\), (\d+) triangles\) via the recovered camera")
# The recovered logo quad: `polySurfaceShape2` spans x [-294.4, 294.4], and after the `rogo` node's
# world y = +73 its y spans [-56.95, 237.45]; the engine draws the UI one model unit per pixel at
# 448 high, +y up, origin at the centre.  So at (w, h): x0 = w/2 - 294.4*s, x1 = w/2 + 294.4*s,
# y0 = h/2 - 237.45*s, y1 = h/2 + 56.95*s, with s = h/448.
LOGO_HALF_W = 294.4
LOGO_Y_UP = 56.95          # the quad's lower edge above the centre
LOGO_Y_DOWN = 237.45       # the quad's upper edge below the centre (the logo overhangs the top)


def png_size(path):
    with open(path, "rb") as f:
        head = f.read(24)
    if len(head) < 24 or head[:8] != b"\x89PNG\r\n\x1a\n":
        return None
    w = int.from_bytes(head[16:20], "big")
    h = int.from_bytes(head[20:24], "big")
    return (w, h)


def png_rows(path):
    """Decode a non-interlaced 8-bit RGB/RGBA PNG to (w, h, bytes-per-pixel, rows)."""
    import struct
    import zlib
    data = open(path, "rb").read()
    pos, idat, w, h, ct = 8, b"", 0, 0, 6
    while pos < len(data):
        n, typ = struct.unpack(">I4s", data[pos:pos + 8])
        body = data[pos + 8:pos + 8 + n]
        if typ == b"IHDR":
            w, h, _bd, ct = struct.unpack(">IIBB", body[:10])
        elif typ == b"IDAT":
            idat += body
        pos += 12 + n
    bpp = 4 if ct == 6 else 3
    raw = zlib.decompress(idat)
    stride = w * bpp
    rows, prev = [], bytearray(stride)
    for y in range(h):
        f = raw[y * (stride + 1)]
        cur = bytearray(raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)])
        for i in range(stride):
            a = cur[i - bpp] if i >= bpp else 0
            b = prev[i]
            c = prev[i - bpp] if i >= bpp else 0
            if f == 1:
                cur[i] = (cur[i] + a) & 255
            elif f == 2:
                cur[i] = (cur[i] + b) & 255
            elif f == 3:
                cur[i] = (cur[i] + ((a + b) >> 1)) & 255
            elif f == 4:
                pa, pb, pc = abs(b - c), abs(a - c), abs(a + b - 2 * c)
                pr = a if (pa <= pb and pa <= pc) else (b if pb <= pc else c)
                cur[i] = (cur[i] + pr) & 255
        rows.append(cur)
        prev = cur
    return w, h, bpp, rows


def run(tool, args, env=None):
    # Menu tests must not read or change the operator's real configuration.
    with tempfile.TemporaryDirectory(prefix="dw4-frontend-config-") as config:
        isolated = dict(os.environ if env is None else env, XDG_CONFIG_HOME=config)
        r = subprocess.run([tool] + args, capture_output=True, text=True, env=isolated)
    return r.returncode, r.stdout, r.stderr


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default=os.path.join(PORT, "build", "dw4"))
    ap.add_argument("--roms", default=DEFAULT_ROMS)
    a = ap.parse_args()
    if not os.path.exists(a.tool):
        print("  front-end: %s not built" % a.tool)
        return 1

    problems = []
    with tempfile.TemporaryDirectory() as tmp:
        # --- run 1: boot to the title and STOP (no input) ---------------------------------------
        tdir = os.path.join(tmp, "title")
        os.makedirs(tdir)
        rc, out, err = run(a.tool, ["--roms", a.roms, "--boot", "--headless",
                                    "--frames", "8", "--w", "320", "--h", "240",
                                    "--out-dir", tdir])
        if rc != 0:
            print("  front-end: boot host failed (%s)" % (err.strip() or out.strip()))
            return 1

        if "blank slate -> %d stage(s)" % len(PLAN) not in out:
            problems.append("no blank-slate %d-stage header" % len(PLAN))

        # the boot chain runs, in order, and each entry's own bytes carry its NEXTSTAGE token
        for i, (entry, tree, scene, expect) in enumerate(BOOT_CHAIN):
            line = "  [%d] entry %d %-13s :" % (i, entry, tree)
            if line not in out:
                problems.append("boot chain missing/!ordered entry %d (%s)" % (entry, tree))
            if "disc check: NEXTSTAGE == %s  ok" % expect not in out:
                problems.append("entry %d disc check failed for %s" % (entry, expect))
            if scene:
                m = re.search(r"scene %s\s+\(\w+\.igb\):\s+(\d+) pack ref\(s\)" % re.escape(scene), out)
                if not m:
                    problems.append("entry %d scene %s not reported" % (entry, scene))
                elif int(m.group(1)) < 1:
                    problems.append("entry %d scene %s has no pack refs" % (entry, scene))

        # the title entry's live menu
        for need in ('be: SYSgetArea()=-1 -> PLAY "AM_TITLE"', "be: TITLE2 RUN",
                     "be: PADINPUT ENABLE 29", "be: FLGisOn(81)="):
            if need not in out:
                problems.append("title missing %r" % need)

        # W1: the title presented with the game's own font + the stagML11 backdrop, and it STOPS.
        # The title boots into its press-start state (finding #605/#639): the logo, the copyright and
        # the "Press START button" line, with the Game Start/Option rows not yet shown.
        if "title: 'Press START button' screen (TITLE2 RUN); START -> 'Game Start' / 'Option'" not in out:
            problems.append("the title's press-start screen was not presented")
        mstate = re.search(r"front-end UI: state=press-start \((\d+) visible item\(s\)\)", out)
        if not mstate:
            problems.append("the title did not report its press-start state")
        elif int(mstate.group(1)) < 3:
            problems.append("the press-start screen resolved too few items (%s)" % mstate.group(1))
        if "state=press-start," not in out:
            problems.append("the title did not stay in the press-start state without input")
        mfont = re.search(r"font: font00\.png 512x512 atlas, (\d+) glyph\(s\) from bectext\.igb", out)
        if not mfont:
            problems.append("the game's own font (bectext.igb) did not decode")
        elif int(mfont.group(1)) < 90:
            problems.append("bectext.igb decoded too few glyphs")
        if "backdrop: stagml11.igb [ref 0]," not in out:
            problems.append("the stagML11 backdrop was not loaded")
        # the generated trail layer resolves from the pack with NO --menu-anim (the asset root is
        # found automatically), and the port draws its own live rows on top
        if LAYER_LINE not in out:
            problems.append("the generated front-end layer (j_startback) did not resolve")
        # the layer's camera is the pack's recovered chain, at its own on-axis z = 730 -- not a
        # calibrated constant
        mcam = CAM_RE.search(out)
        if not mcam:
            problems.append("the recovered title camera (cameraanimShape01) did not resolve")
        elif abs(float(mcam.group(3)) - 730.0) > 1.0:
            problems.append("the recovered camera eye z = %s, not the chain's 730" % mcam.group(3))
        if "not recovered in NDMW.AFS" in out:
            problems.append("the title camera fell back to the calibrated distance")

        # the recovered title UI tree (the pack's own logo/copyright/rows) resolved from AREA.AFS 620
        mui = UI_RE.search(out)
        if not mui:
            problems.append("the recovered title UI tree (AREA.AFS 620) did not resolve")
        else:
            if int(mui.group(1)) < 5:
                problems.append("the recovered UI resolved only %s item(s)" % mui.group(1))
            names = sorted(mui.group(3).split())
            if names != EXPECT_TEXTURES:
                problems.append("the recovered UI textures are %s, not the pack's %s"
                                % (names, EXPECT_TEXTURES))
            if int(mui.group(2)) != len(EXPECT_TEXTURES):
                problems.append("the recovered UI resolves %s texture(s), not the pack's %d"
                                % (mui.group(2), len(EXPECT_TEXTURES)))
        mlg = UI_LOGO_RE.search(out)
        if not mlg or mlg.group(1) != "logo.png":
            problems.append("the logo item is not bound to logo.png (%s)"
                            % (mlg.group(1) if mlg else "no line"))
        mrect = UI_RECT_RE.search(out)
        if not mrect:
            problems.append("the recovered logo quad's rectangle was not reported")
        else:
            x0, x1, y0, y1 = (float(mrect.group(k)) for k in (1, 2, 3, 4))
            rw, rh = int(mrect.group(5)), int(mrect.group(6))
            s = rh / 448.0
            ex0, ex1 = rw / 2.0 - LOGO_HALF_W * rw / 640.0, rw / 2.0 + LOGO_HALF_W * rw / 640.0
            ey0, ey1 = rh / 2.0 - LOGO_Y_DOWN * s, rh / 2.0 + LOGO_Y_UP * s
            for got, exp, name in ((x0, ex0, "x0"), (x1, ex1, "x1"), (y0, ey0, "y0"), (y1, ey1, "y1")):
                if abs(got - exp) > 0.5:
                    problems.append("logo rect %s = %.1f, not the recovered %.1f (at %dx%d)"
                                    % (name, got, exp, rw, rh))
        # the OPEN pop-in is the recovered controller, not a frozen pose: at t=0 the logo node's
        # sequence scale is 0 (a degenerate quad), then it settles to the resting rectangle
        mopen = UI_OPEN_RE.search(out)
        if not mopen:
            problems.append("the recovered OPEN pop-in (logo rect at t=0) was not reported")
        elif mrect:
            ow = float(mopen.group(2)) - float(mopen.group(1))
            rw0 = float(mrect.group(2)) - float(mrect.group(1))
            if ow > 1.0 or rw0 <= 1.0:
                problems.append("the OPEN pop-in is not recovered: t=0 width %.1f, rest width %.1f"
                                % (ow, rw0))
        # the static stagML11 backdrop is composed under the layer and the UI (the missing-backdrop gap)
        mbg = BACKDROP_RE.search(out)
        if not mbg:
            problems.append("the stagML11 backdrop was not composed under the layer")
        elif int(mbg.group(1)) < 100 or int(mbg.group(2)) < 1000:
            problems.append("the composed backdrop is too small (%s meshes, %s triangles)"
                            % (mbg.group(1), mbg.group(2)))
        if "dw4 front-end: stopped at the title, awaiting input  ok" not in out:
            problems.append("the boot did not stop at the title")
        if "title: no confirmation; stopped at the title" not in out:
            problems.append("the title did not report waiting for input")

        # the boot must NOT have jumped into the world (that is the old contract)
        for bad in ("-- Game Start branch", "first playable stage stagML11",
                    "entering the first playable stage", "reached the first playable stage"):
            if bad in out:
                problems.append("the boot ran past the title: saw %r" % bad)

        # the opening FMV: a headless boot reports it (never plays 64 s of video)
        if "opening FMV: aus_opening.sfd (not played: no window)" not in out:
            problems.append("the opening stage did not report its FMV")

        tframe = os.path.join(tdir, "frame_0000.png")
        if not os.path.exists(tframe) or os.path.getsize(tframe) < 1024:
            problems.append("no title frame was written")

        # --- run 2: START advances to the menu, Cross on Game Start enters the world ---------------
        gdir = os.path.join(tmp, "game")
        os.makedirs(gdir)
        rc, out2, err2 = run(a.tool, ["--roms", a.roms, "--boot", "--headless",
                                      "--frames", "900", "--w", "320", "--h", "240",
                                      "--input-script", "5:start,70:start,130:cross,300:cross,345:left,380:right,"
                                      "415:right,450:right,485:right,520:cross,600:circle,700:circle,760:cross,810:right",
                                      "--out-dir", gdir])
        if rc != 0:
            problems.append("Game Start host failed (%s)" % (err2.strip() or out2.strip()))
        else:
            # the press-start screen advances to the Game Start/Option rows (finding #605/#639):
            # START on the pad; Cross is deliberately not an alias
            # the first press during the opening skips it to the press-start screen; only the next
            # START opens the menu (buttons are edge-triggered)
            if "title: opening skipped at frame 5 -> 'Press START button'" not in out2:
                problems.append("a button during the opening did not skip it to the press-start screen")
            if "title: press-start -> main menu ('Game Start' / 'Option')" not in out2:
                problems.append("the press-start screen did not advance to the menu")
            mmenu = re.search(r"title: state=menu \((\d+) visible item\(s\)\)", out2)
            if not mmenu:
                problems.append("the menu state did not report its visible item count")
            elif mstate and int(mmenu.group(1)) <= int(mstate.group(1)):
                problems.append("the menu state shows no more items than the press-start screen")
            if "state=menu," not in out2:
                problems.append("the title did not reach the menu state")
            # Creation (LoadIntf2 starter choice and name entry) stays on the slot screen until a nonempty name is confirmed.
            if "title: Game Start -> slot screen" not in out2:
                problems.append("Cross on Game Start did not open the slot screen")
            expected = ["Dorumon", "Guilmon", "Dorumon", "Agumon", "Veemon", "Guilmon", "Dorumon", "Dorumon", "Agumon"]
            selected = re.findall(r"title: species: (\w+)", out2)
            if selected != expected:
                problems.append("species wrap/re-entry mismatch: %r" % selected)
            if "title: species -> slot screen" not in out2:
                problems.append("Circle did not cancel species selection")
            if "species confirmed: Guilmon -> name entry" not in out2:
                problems.append("Cross did not preserve the selected species")
            if "title: name entry -> species" not in out2:
                problems.append("Circle on an empty name did not return to the starter choice")
            if "entering the first playable stage" in out2 or "first playable stage stagML11" in out2:
                problems.append("Create Digimon still bypasses character creation")
            if not os.path.exists(os.path.join(gdir, "frame_0899.png")):
                problems.append("species selector did not remain on screen")

        # Name "ab" -> question -> No -> edit "a" -> Yes (GAMESTART) -> log-in prompt -> Circle -> "ac" -> Yes -> Start.
        ndir = os.path.join(tmp, "named")
        os.makedirs(ndir)
        rc, outn, errn = run(a.tool, ["--roms", a.roms, "--boot", "--headless", "--frames", "1666",
                                     "--w", "320", "--h", "240", "--input-script",
                                     "5:start,70:start,130:cross,300:cross,345:cross,395:cross,410:right,422:cross,"
                                     "440:start,490:cross,515:down,530:cross,560:start,610:cross,640:cross,700:circle,"
                                     "760:cross,775:right,787:right,800:cross,815:start,865:cross,890:cross,950:start,"
                                     "956:circle,960:start,966:cross,1416+cross", "--out-dir", ndir])
        if rc or "title: name question: ab" not in outn or "title: name question: a" not in outn:
            problems.append("name entry/edit/No confirmation failed: " + errn)
        if "title: created Dorumon named a" not in outn:
            problems.append("name confirmation did not create the selected Digimon")
        if "title: created Dorumon named ac" not in outn:
            problems.append("log-in prompt cancellation did not preserve name/species/key for editing")
        if "entering the first playable stage: stagml11.igb" not in outn:
            problems.append("Start on the created card did not enter the lobby")
        if "lobby: BG02 + portal/arrival controllers, 131 mesh(es), 24 texture(s); camera camsp0101" not in outn:
            problems.append("lobby environment did not resolve its runtime material bindings")
        if "lobby: player ac, SQ_ENTR fade 50" not in outn or "login: arrived;" not in outn:
            problems.append("login did not retain the created name in the boot window")
        if "stagml02.igb" in outn or "camsp0201" in outn or "TALKFONT02 I<281>" in outn:
            problems.append("login incorrectly entered the commander room intro")
        if outn.count("title: logging in") != 1:
            problems.append("login transition accepted extra Start presses")
        # Original first.lua waits for authored window OPEN before showing
        # page 39. Observe the real text owner, not the adapter's earlier log.
        if "original scene start.lua -> first.lua" not in outn or "TALKFONT02 I<39>" not in outn or "TALKFONT02 I<42>" in outn:
            problems.append("Digi-Elf greeting missing or held Cross skipped dialogue")

        # The slot scene's closing fade must present a fully black frame before any lobby loading/drawing.
        w, h, bpp, rows = png_rows(os.path.join(ndir, "frame_1050.png"))
        if any(row[x+k] for row in rows for x in range(0, w*bpp, bpp) for k in range(3)):
            problems.append("login did not present a fully black frame before loading")
        if "loading: complete after 103 presented frame(s)" not in outn:
            problems.append("headless login did not present loading before preparing the destination")
        w, h, bpp, rows = png_rows(os.path.join(ndir, "frame_1125.png"))
        green = sum(row[x+1] > row[x]+25 and row[x+1] > row[x+2]+25
                    for row in rows for x in range(0, w*bpp, bpp))
        if green < 150:
            problems.append("original stage loading card was not revealed after CLOSE")
        w, h, bpp, rows = png_rows(os.path.join(ndir, "frame_1200.png"))
        colored = sum(max(row[x:x+3])-min(row[x:x+3]) > 20
                      for row in rows for x in range(0, w*bpp, bpp))
        if colored < 10000:
            problems.append("arrival remained blank or untextured")

        # Holding the naming stick scrolls past the first five keys.
        hdir = os.path.join(tmp, "name-held")
        os.makedirs(hdir)
        rc, outh, errh = run(a.tool, ["--roms", a.roms, "--boot", "--headless",
                                     "--frames", "560", "--w", "320", "--h", "224",
                                     "--input-script", "5:start,70:start,130:cross,300:cross,345:cross,"
                                     "395-440+right,470:cross,490:start", "--out-dir", hdir])
        if rc or not re.search(r"title: name question: [f-z]", outh):
            problems.append("held naming input did not repeat: " + errh)

        # --- run 2a: the Option screen (finding #724): Down + Cross opens it from the menu, Right flips the
        # highlighted setting (Dungeon camera Near -> Far), Down moves to Light, Cross on the Return row
        # closes it.  Edge-triggered input: each press is one action.
        odir = os.path.join(tmp, "option")
        os.makedirs(odir)
        rc, outo, erro = run(a.tool, ["--roms", a.roms, "--boot", "--headless", "--frames", "520",
                                      "--w", "320", "--h", "240", "--input-script",
                                      "5:start,70:start,120:down,150:cross,310:right,340:down,365:down,"
                                      "390:cross", "--out-dir", odir])
        if rc != 0:
            problems.append("Option screen host failed (%s)" % (erro.strip() or outo.strip()))
        else:
            for want in ("title: option screen opened",
                         "title: option: Dungeon camera = Far, Light = Hard",
                         "title: option screen closed -> main menu"):
                if want not in outo:
                    problems.append("Option screen: missing '%s'" % want)
            if "title: Cross on" in outo and "-> Game Start" in outo:
                problems.append("the Option screen's Return row went to Game Start")
            ofr = os.path.join(odir, "frame_0330.png")
            if not os.path.exists(ofr) or os.path.getsize(ofr) < 1024:
                problems.append("no frame written while the Option screen was up")

        # --- run 2c: the slot screen is the pack's own four coloured panels ----
        sfr = os.path.join(tmp, "slot.png")
        asset = os.path.join(os.path.dirname(a.tool), "dw4asset")
        rc, outs, errs = run(asset, ["chr", a.roms, "--t", "3.5", "--out", sfr])
        if rc != 0 or not os.path.exists(sfr):
            problems.append("slot screen render failed (%s)" % (errs.strip() or outs.strip()))
        else:
            w, h, bpp, rows = png_rows(sfr)
            def px(x, y):
                return tuple(rows[y][x * bpp:x * bpp + 3])
            # panel 1 red, 2 blue, 3 yellow, 4 green, sampled on each body's flat colour (the captured
            # frame's bodies: (249,110,110) (32,150,231) (253,253,48) (0,253,7))
            want = {(45, 40): (255, 107, 107), (355, 40): (33, 148, 231),
                    (45, 300): (255, 255, 49), (355, 300): (0, 255, 0)}
            for (x, y), (r, g, b) in want.items():
                got = px(x, y)
                if max(abs(got[0] - r), abs(got[1] - g), abs(got[2] - b)) > 12:
                    problems.append("slot panel at (%d,%d) is %s, expected about %s" % (x, y, got, (r, g, b)))

        # Sample only exposed backdrop pixels, excluding the animated panels and cursor.
        # This catches a missing BG02 root, a frozen clock, and a loop that fails to restart.
        backdrops = []
        for phase in (0, 1.5, 6):
            path = os.path.join(tmp, "slot-bg-%s.png" % phase)
            rc, outbg, errbg = run(asset, ["chr", a.roms, "--t", str(phase), "--out", path])
            if rc or not os.path.exists(path):
                problems.append("slot backdrop render failed: %s" % errbg)
                continue
            w, h, bpp, rows = png_rows(path)
            pixels = [tuple(rows[y][x*bpp:x*bpp+3])
                      for y in range(230, 345) for x in range(85, 310)]
            if len(set(pixels)) < 20:
                problems.append("slot backdrop is still a flat field")
            if phase == 1.5 and sum(b > r * 1.5 and b > g * 1.3
                                    for r, g, b in pixels) < 40:
                problems.append("slot backdrop lost its coloured diamonds")
            backdrops.append(pixels)
        if len(backdrops) == 3:
            if backdrops[0] == backdrops[1]:
                problems.append("slot backdrop animation is frozen")
            if backdrops[0] != backdrops[2]:
                problems.append("slot backdrop does not repeat after its six-second track")

        # All four native previews must change the model and icon, while leaving other slots alone.
        species_frames = []
        for species in range(4):
            path = os.path.join(tmp, "species-%d.png" % species)
            rc, outsp, errsp = run(asset, ["chr", a.roms, "--t", "3.5", "--species", str(species), "--out", path])
            if rc or not os.path.exists(path):
                problems.append("species %d render failed: %s" % (species, errsp))
                continue
            w, h, bpp, rows = png_rows(path)
            def crop(x0, y0, x1, y1):
                return b"".join(bytes(rows[y][x0*bpp:x1*bpp]) for y in range(y0, y1))
            species_frames.append((crop(90, 45, 240, 142), crop(267, 18, 303, 55), crop(322, 0, 640, 448)))
        if len(species_frames) == 4:
            if len({f[0] for f in species_frames}) != 4:
                problems.append("species previews do not draw four distinct models")
            if len({f[1] for f in species_frames}) != 4:
                problems.append("species icons do not select four distinct atlas cells")
            if len({f[2] for f in species_frames}) != 1:
                problems.append("changing species altered the other player slots")

        # --- run 2b: the opening FMV is skippable (Cross/Space), deterministically via the script --
        rc, out3, err3 = run(a.tool, ["--roms", a.roms, "--movie", "aus_opening.sfd",
                                      "--input-script", "5:cross"])
        if rc != 0:
            problems.append("the FMV skip run failed (%s)" % (err3.strip() or out3.strip()))
        elif "played 5 movie frame(s)" not in out3 or "[skipped]" not in out3:
            problems.append("Cross did not skip the opening FMV at the scripted frame")

        # --- run 3: the generated layer animates every frame (no capture, no flag) ---------------
        mdir = os.path.join(tmp, "layer")
        os.makedirs(mdir)
        rc, out3, err3 = run(a.tool, ["--roms", a.roms, "--boot", "--headless",
                                      "--frames", "240", "--input-script", "999:cross",
                                      "--w", "640", "--h", "480", "--out-dir", mdir])
        if rc != 0:
            problems.append("layer host failed (%s)" % (err3.strip() or out3.strip()))
        if LAYER_LINE not in out3:
            problems.append("the generated layer did not resolve without a flag")
        # it must still stop at the title, not run into the world
        if "title: no confirmation; stopped at the title" not in out3:
            problems.append("the layer boot did not stop at the title")
        frames = sorted(f for f in os.listdir(mdir) if f.endswith(".png"))
        if len(frames) < 2:
            problems.append("the generated layer wrote no frames")
        else:
            first = os.path.join(mdir, frames[0])
            last = os.path.join(mdir, frames[-1])
            # the controller regenerates the layer every frame, so four seconds must move it
            if open(first, "rb").read() == open(last, "rb").read():
                problems.append("the generated layer is frozen (first and last frame are identical)")
            sz = png_size(first)
            if sz != (640, 480):
                problems.append("the boot did not compose at its own 640x480 (%s)" % (sz,))
        out = out + out3

        # The shared layer renderer has optional lobby-only state. Its frontend draw
        # records must initialize that state rather than inherit realloc's heap bytes.
        # Poison fresh allocations with both zero and nonzero bytes, covering the blue
        # trace, white flash, settled title and main menu in otherwise identical runs.
        heap_dirs = []
        for poison in (255, 85):
            hdir = os.path.join(tmp, "heap-%d" % poison)
            os.makedirs(hdir)
            env = dict(os.environ, MALLOC_PERTURB_=str(poison))
            rc, _hout, herr = run(a.tool, ["--roms", a.roms, "--boot", "--headless",
                                          "--frames", "350", "--input-script", "275:start",
                                          "--w", "320", "--h", "224", "--out-dir", hdir], env=env)
            if rc != 0:
                problems.append("heap-poisoned frontend failed (%s)" % herr.strip())
            heap_dirs.append(hdir)
        for frame in (30, 60, 120, 180, 208, 210, 270, 310, 340):
            name = "frame_%04d.png" % frame
            paths = [os.path.join(d, name) for d in heap_dirs]
            if not all(os.path.exists(p) for p in paths):
                problems.append("heap-poisoned frontend did not write %s" % name)
            elif open(paths[0], "rb").read() != open(paths[1], "rb").read():
                problems.append("frontend frame %d depends on uninitialized heap state" % frame)

        # The layer's opening plays alone: the game shows no title UI until the recovered 209-frame
        # SQ_OPEN has finished (finding #640), so the UI's first drawn frame must be past it.  Run 3
        # renders 240 frames, which is the run that reaches it.
        mfirst = re.search(r"title: UI first drawn at frame (\d+) \(after the layer's ([\d.]+) s opening\)", out3)
        if not mfirst:
            problems.append("the title did not report the frame it first draws the UI")
        elif int(mfirst.group(1)) < 209:
            problems.append("the title UI appears during the layer's opening (frame %s)" % mfirst.group(1))

        # The white flash (finding #642): the title stage's Lua runs `MODELCTRL i_fadewn01 GENERATE
        # SQ_WTIN60` once j_startback's SQ_OPEN has finished -- a full-screen white overlay at alpha
        # 1.0 fading to 0 over 60 frames (FADESET OUT fadeTime 60).  It must start on the frame the
        # opening ends, at full alpha, and fade from there.
        mflash = re.search(r"title: white flash \(SQ_WTIN60\) alpha (\d+) at frame (\d+)", out3)
        if not mflash:
            problems.append("the title never drew the recovered white flash (SQ_WTIN60)")
        else:
            if int(mflash.group(1)) < 128:
                problems.append("the white flash did not start at full alpha (alpha %s)"
                                % mflash.group(1))
            if int(mflash.group(2)) != 209:
                problems.append("the white flash starts at frame %s, not when SQ_OPEN ends (209)"
                                % mflash.group(2))

        # the movie the plan names must resolve inside the disc's own archives
        asset = os.path.join(PORT, "build", "dw4asset")
        if os.path.exists(asset):
            _, mout, _ = run(asset, ["media", a.roms, "list"])
            if "aus_opening.sfd" not in mout:
                problems.append("the archives do not list aus_opening.sfd")

        for bad in ("FAIL", "WARNING"):
            if bad in out or bad in out2:
                problems.append("output contains %r" % bad)

    if problems:
        print("  front-end: BAD")
        for p in problems:
            print("    - %s" % p)
        return 1

    nchecks = len(re.findall(r"disc check: NEXTSTAGE ==", out2))
    print("  front-end: boot chain stops at the title (font + stagML11 backdrop), "
          "Create Digimon -> four species, wrap/cancel/hold, no premature hand-off (%d boot disc checks; destination %s)  ok" % (nchecks, FIRST_STAGE))
    return 0


if __name__ == "__main__":
    sys.exit(main())
