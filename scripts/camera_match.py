#!/usr/bin/env python3
"""camera_match.py — build a camera-matched scene TSV for a paused DW4 capture.

The port has three ways to learn where geometry goes, and they cover different parts of a frame
(findings #519/#520/#521):

  * the *static environment* is world-space pack geometry: its `igGeometry` shapes carry no usable
    `igTransform`-chain matrix, so the mesh is already in stage coordinates and identity places it;
  * a *placed object* (a prop, a character part) is normally reached through the `igGeometry`
    `igAttrList` walk `scripts/capture_scene.py --pack` does;
  * a *runtime-spawned or skinned* object is on neither path: its transform lives on a
    `beModelCtrlNode2` (vtable 0x537f40, `_m` at +0x20) and its pack mesh must be named.  The
    character (the player's skin) and the destructible crates are this case.

This tool writes one TSV the port's `--scene` consumes (name, matrix, live attrs, shape, pack ids):

    --pack      the stage model pack (AFS:ENTRY), to compute mesh bounds
    --big       bbox-diagonal threshold for the world-space environment (default 150)
    --min-z     a mesh flatter than this in z is a screen-space UI/backdrop card, not world
                geometry (default 1.0); this is the world-set membership test (finding #544
                follow-up -- the old --big-only test kept 40 flat cards and they were the frame's
                flat "gaps")
    --character MESH at the beModelCtrlNode2 node nearest --target
    --prop      MESH@NODE_ADDR, repeatable (a runtime object at that node's transform)

    python3 camera_match.py --from dump.bin --pack ../local/extracted/NDMW.AFS:614 \\
        --target 421.83 72 -110.07 --character gobr_skinShape2 \\
        --prop M_TR32_barrelShape@0x14df9d0 --prop M_box_bodyShape@0x130a858 \\
        --tsv /tmp/camera.tsv
"""
import argparse
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
LO = 0x00100000
VT_NODE = 0x537F40          # beModelCtrlNode2; _m at +0x20


def u32(ram, a):
    o = a - LO
    return struct.unpack_from("<I", ram, o)[0] if 0 <= o and o + 4 <= len(ram) else 0


def m16(ram, a):
    return struct.unpack_from("<16f", ram, a - LO)


def nodes(ram):
    """Every beModelCtrlNode2 address, 4-byte aligned."""
    pat = struct.pack("<I", VT_NODE)
    out, s = [], 0
    while True:
        i = ram.find(pat, s)
        if i < 0:
            break
        if (LO + i) % 4 == 0:
            out.append(LO + i)
        s = i + 1
    return out


def nearest_node(ram, target):
    best, bd = 0, None
    for a in nodes(ram):
        m = m16(ram, a + 0x20)
        if abs(m[15] - 1.0) > 1e-3:                 # a real affine transform, not a stale slot
            continue
        d = sum((m[12 + i] - target[i]) ** 2 for i in range(3))
        if bd is None or d < bd:
            best, bd = a, d
    return best


def pack_bounds(pack, decomp):
    """geometry-attribute id -> (name, bbox diagonal, z extent, has_uv), for the world-space test.

    The z extent is the membership signal the world test needs: a stage's UI/backdrop meshes are
    flat *cards* authored in a constant-z plane (their z extent is exactly 0 in the pack), while
    the 3D world spans z.  `camera_match --big` used to keep every large pack mesh, which pulled in
    the whole screen-space pass (`color0Shape1`, `win0Shape*`, `maskShape`, `fadein/bgclear`, ...)
    and they rendered as the frame's flat planes -- the "gaps" of finding #544's follow-up.

    `has_uv` is the *texture* signal: a drawn surface in this engine carries texcoords, so an
    untextured mesh of the pack is an auxiliary volume (collision, blocker, a vertex-colour helper)
    the render does not draw -- the world test can drop it (finding #550)."""
    sys.path.insert(0, os.path.join(decomp, "scripts"))
    import igb_ids
    import igb_models
    import igb_pool
    refl = igb_ids.igb_inst.load_reflection(os.path.join(decomp, "data", "reflection.json"))
    afs, entry = pack.rsplit(":", 1)
    data = open(afs, "rb").read()
    off = int.from_bytes(data[8 + 8 * int(entry):12 + 8 * int(entry)], "little")
    P = igb_pool.load(afs, hex(off), refl)
    out = {}
    for g in igb_models.read_geometry(P, refl):
        got, _why = igb_models.extract(P, g)
        if got is None:
            continue
        vs, uv, _tris = got
        ex = [max(v[i] for v in vs) - min(v[i] for v in vs) for i in range(3)]
        diag = sum(e * e for e in ex) ** 0.5
        out[g["id"]] = (g.get("name"), diag, ex[2], bool(uv))
    return out


def pack_normals(pack, decomp):
    """geometry-attribute id -> the area-weighted mean face normal, for the ground/wall split."""
    sys.path.insert(0, os.path.join(decomp, "scripts"))
    import igb_ids
    import igb_models
    import igb_pool
    refl = igb_ids.igb_inst.load_reflection(os.path.join(decomp, "data", "reflection.json"))
    afs, entry = pack.rsplit(":", 1)
    data = open(afs, "rb").read()
    off = int.from_bytes(data[8 + 8 * int(entry):12 + 8 * int(entry)], "little")
    P = igb_pool.load(afs, hex(off), refl)
    out = {}
    for g in igb_models.read_geometry(P, refl):
        got, _why = igb_models.extract(P, g)
        if got is None:
            continue
        vs, _uv, tris = got
        n = [0.0, 0.0, 0.0]
        for a, b, c in tris:
            e1 = [vs[b][k] - vs[a][k] for k in range(3)]
            e2 = [vs[c][k] - vs[a][k] for k in range(3)]
            n[0] += e1[1] * e2[2] - e1[2] * e2[1]
            n[1] += e1[2] * e2[0] - e1[0] * e2[2]
            n[2] += e1[0] * e2[1] - e1[1] * e2[0]
        L = sum(x * x for x in n) ** 0.5
        out[g["id"]] = tuple(x / L for x in n) if L > 1e-9 else (0.0, 0.0, 0.0)
    return out


def pack_shape_keys(pack, decomp):
    """`(primType, numPrims) -> [pack geometry-attr id]`, the key finding #565 matches a world
    shape on when its live vertex buffer is drained.  One pack attribute is one shape, so a key
    usually names exactly one id; the small props share keys and the caller keeps the distinctive
    ones."""
    sys.path.insert(0, os.path.join(decomp, "scripts"))
    import igb_ids
    import igb_models
    import igb_pool
    refl = igb_ids.igb_inst.load_reflection(os.path.join(decomp, "data", "reflection.json"))
    afs, entry = pack.rsplit(":", 1)
    data = open(afs, "rb").read()
    off = int.from_bytes(data[8 + 8 * int(entry):12 + 8 * int(entry)], "little")
    P = igb_pool.load(afs, hex(off), refl)
    out = {}
    for g in igb_models.read_geometry(P, refl):
        out.setdefault((g["prim_type"], g["num_prims"]), []).append(g["id"])
    return out


def stage_fallback_textures(ram, ground_name=None, wall_name=None):
    """`(ground, wall)` texture names for the *unnamed* world meshes (finding #544).

    The cave's big meshes are RamData/packet-drawn, so `attr_pack_map`'s vertex-buffer content
    match never reaches them and they end up with no texture.  The stage's BG ground/object material
    sets already carry the textures they actually use, so this is a fallback, not a new binding: the
    ground set has **two** variants and the stage draws one per surface -- the `s` (`P11G00s`, the
    brown cracked floor) for the flat floor and the `n` (`P11G00n`, a 256x128 rock atlas that also
    carries the wall's blue light-dash band) for the wall/dome (finding #547, measured against the
    real frame: `P11G00n` reproduces both the rock and the band's curve, `P11G00s` the floor).
    `camera_match` picks between them per mesh by the mesh's own shape (see the membership section),
    not by the old `--big`/mean-normal guess.

    `ground_name`/`wall_name` override the set's choice.  The wall default is now the `n` variant,
    not the ground `s` material: #544's colour test could not separate a cave rock from a cave wall
    because it only looked at mean RGB, but the textures themselves do -- `P11G00n` is the atlas
    with the blue strip.  The real per-draw binding is still the staged packet material (#522).
    """
    import texture_map
    tm = texture_map.TextureMap(ram)
    ground = [ground_name] if ground_name else sorted(
        {n for i, ns in tm.info_textures.items() if i.startswith("BGGround")
         for n in ns if n.endswith("s.png")}, key=lambda n: (n != "P11G00s.png", n))
    if wall_name:
        wall = [wall_name]
    else:
        wall = sorted(
            {n for i, ns in tm.info_textures.items() if i.startswith("BGGround")
             for n in ns if n.endswith("n.png")}, key=lambda n: (n != "P11G00n.png", n))
        if not wall:
            obj = {n for i, ns in tm.info_textures.items() if i.startswith("BGObj") for n in ns}
            wall = sorted(obj) or list(ground) or ["P11G00s.png"]
    return ground or ["P11G00s.png"], wall


def skinned_char_ids(ram, pack, decomp):
    """The pack id(s) of the live **skinned** mesh(s) -- which is NOT reliably the player.

    A skinned mesh is the one whose `igVertexArray1_1` carries the per-vertex blend stream: the
    runtime allocates `_blendWeights` (+0x20, f32 per vertex) and `_blendIndices` (+0x24, u8 per
    vertex), which the VU1 BLEND family consumes.  On the Goblin Pass capture exactly ONE live mesh
    qualifies -- and it is `ogre_skinShape`, an **Ogremon NPC**, NOT the player (finding #531,
    refuted by #535).  The player is Susanoomon and is an **actor rig**, not a mesh: walk
    beModelCtrlNode2 -> igLod -> igActor -> igAppearance._skin -> igSkin._skinnedGraph, whose child
    list is the model and whose igActor owns the bone matrix caches.  So `--character auto` here is
    a trap: it answers "which mesh is skinned", not "which mesh is the player".
    """
    import extract_live_models as el
    import capture_scene
    el._RAM = ram
    afs, entry = pack.rsplit(":", 1)
    packmap = capture_scene.load_pack_map(afs, int(entry, 0), decomp)
    ids = []
    for a in el.find_objects(0x005238C0):
        g = el.read_geom(a)
        if not g:
            continue
        vb = el.pine_read(g["vertexArray"], 0x30)
        if len(vb) < 0x30:
            continue
        if not (el.u32(vb, 0x20) and el.u32(vb, 0x24)):
            continue                        # not skinned
        try:
            verts, _t, _l, _n, _u = el.extract(g)
        except Exception:
            continue
        pid = packmap.get(tuple(verts))
        if pid is not None and pid not in ids:
            ids.append(pid)
    return ids


def walk_live_pack(ram, pack, decomp):
    """One pass over the live `igGeometry` shapes, for the texture map and the world test.

    Returns `(attr2pack, unplaced, placed)`: `attr2pack` is the live geometry-attribute address ->
    pack attribute id content match `capture_scene --pack` does; `unplaced`/`placed` are the same
    ids split by whether the shape's `igTransform` chain yields a usable matrix.  A shape with a
    matrix is a **placed** object (a prop, a backdrop sphere, the character) and must not be drawn
    at identity; a shape without one is authored in world space, so identity *is* its placement
    (finding #520).
    """
    import capture_scene
    import extract_live_models as el
    r = capture_scene.Ram(ram)
    afs, entry = pack.rsplit(":", 1)
    el._RAM = ram
    packmap = capture_scene.load_pack_map(afs, int(entry, 0), decomp)
    a2p, unplaced, placed = {}, set(), set()
    for s in capture_scene.scan(r, capture_scene.VT_SHAPE):
        attrs = capture_scene.attrs_of(r, s)
        ids = capture_scene.pack_ids_of(el, attrs, packmap)
        for a, i in zip(attrs, ids):
            if i is not None and i >= 0:
                a2p[a] = i
        tgt = placed if capture_scene.placement(r, s) is not None else unplaced
        tgt.update(i for i in ids if i is not None and i >= 0)
    return a2p, unplaced, placed


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--from", dest="src", required=True, help="a paused EE RAM dump")
    ap.add_argument("--pack", required=True, metavar="AFS:ENTRY")
    ap.add_argument("--tsv", required=True)
    ap.add_argument("--target", type=float, nargs=3, metavar=("X", "Y", "Z"),
                    help="the camera look-at (beCameraCtrl._avgPos)")
    ap.add_argument("--character",
                    help="a mesh name to place at the node nearest --target.  'auto' = the live"
                         " skinned mesh, which is an NPC here, NOT the player (finding #535)")
    ap.add_argument("--prop", action="append", default=[], metavar="MESH@NODE_ADDR",
                    help="a mesh at that beModelCtrlNode2 node's transform (repeatable)")
    ap.add_argument("--prop-tex", action="append", default=[], metavar="MATERIAL@MESH",
                    help="bind MESH to a stage-pack igAttrSet's inline texture (repeatable).  The"
                         " destructible objects' material is not in the live graph or a texture"
                         " pack -- it is an igAttrSet in the stage pack whose igTextureAttr points"
                         " at an inline pool block (scripts/pack_inline_tex.py; finding #552)")
    ap.add_argument("--character-pack", metavar="AFS:ENTRY",
                    help="a second pack to resolve --character in -- the player is"
                         " `P_susanoo_Skin0Shape*` in NDMW.AFS:861, which the stage pack does not"
                         " contain.  Pass it to `dw4asset render --pack2 AFS:ENTRY` too")
    ap.add_argument("--character-tex", metavar="NAME",
                    help="the texture name for the --character row (the player's is"
                         " P_susanoo01.png / P_susanoo02.png, from the livedump)")
    ap.add_argument("--texdir", metavar="DIR",
                    help="write <MATERIAL>.rgba for each --prop-tex into DIR, for"
                         " `dw4asset render --texdir DIR`")
    ap.add_argument("--big", type=float, default=150.0,
                    help="bbox-diagonal threshold for the world-space environment")
    ap.add_argument("--min-z", type=float, default=1.0, metavar="DZ",
                    help="exclude a mesh flatter than DZ in z: the stage's UI/backdrop meshes are"
                         " flat cards in a constant-z plane (z extent exactly 0 in the pack), so"
                         " this is the first half of the world-set membership test that replaces"
                         " the old --big-only heuristic")
    ap.add_argument("--keep-placed", action="store_true",
                    help="also emit a pack mesh the live scene places with a real transform (a"
                         " prop, a backdrop sphere); by default the env set is only the unplaced"
                         " world-space geometry (finding #520), which is the other half of the"
                         " membership test")
    ap.add_argument("--include-untextured", action="store_true",
                    help="keep large 3D world meshes that carry no texcoords.  By default they"
                         " are dropped: a drawn surface in this engine has UVs, and the untextured"
                         " meshes are auxiliary volumes.  On Goblin Pass one of them (38907) is a"
                         " big blocker that crosses the camera plane and hides the barrel"
                         " (finding #550); drop the flag to see it come back")
    ap.add_argument("--drop-id", action="append", default=[], type=int, metavar="ID",
                    help="never emit this pack geometry-attribute id (repeatable); for sweeping a"
                         " single mesh out of the world set while a rule is being pinned down")
    ap.add_argument("--textures", action="store_true",
                    help="add a sixth column with the live texture name(s) for each mesh"
                         " (texture_map.py; needs the --pack content match)")
    ap.add_argument("--stage-material", action="store_true",
                    help="for a world mesh the material walk cannot name (the cave shell is"
                         " RamData/packet-drawn), fall back to the stage's BG ground/object texture"
                         " chosen by the mesh's mean normal (finding #544; needs --textures)")
    ap.add_argument("--ground-tex", metavar="NAME",
                    help="override the stage-material ground texture (default: the BG ground set's"
                         " `s` variant, P11G00s on Goblin Pass)")
    ap.add_argument("--wall-tex", metavar="NAME",
                    help="override the stage-material wall texture (default: the same ground"
                         " texture - the cave is one rock formation, and the old TA01BJ20 pick was"
                         " a guess; the draw-time material is the real fix)")
    ap.add_argument("--decomp", default=os.path.join(os.path.dirname(HERE)))
    args = ap.parse_args()

    ram = open(args.src, "rb").read()
    bounds = pack_bounds(args.pack, args.decomp)
    prop_tex = {}
    for spec in args.prop_tex:
        mat, _, mesh = spec.partition("@")
        if mat and mesh:
            prop_tex[mesh] = mat
    if prop_tex and args.texdir:
        import pack_inline_tex as pit
        P, _d, _r, oid = pit.load(args.pack, args.decomp)
        sets = pit.all_attrsets(P, _d, _r)
        os.makedirs(args.texdir, exist_ok=True)
        for mat in sorted(set(prop_tex.values())):
            hit = [s for s in sets if (s["name"] or "").strip("\x00 ") == mat]
            t = pit.texture_of(P, _d, _r, oid, hit[0]) if hit else None
            if not t:
                print("  prop-tex %s: no inline texture" % mat, file=sys.stderr)
                continue
            rgba, w, h, _n = t
            path = os.path.join(args.texdir, mat + ".rgba")
            pit.write_rgba(path, rgba, w, h)
            print("  prop-tex %s -> %dx%d inline texture -> %s" % (mat, w, h, path))
    by_name = {}
    for gid, (name, diag, _ze, _uv) in bounds.items():
        by_name.setdefault(name, []).append(gid)
    # A character can live in another pack: the player is `P_susanoo_Skin0Shape*` in
    # NDMW.AFS:861, a model file the stage pack does not contain (finding #555).
    char_by_name = by_name
    if getattr(args, "character_pack", None):
        cb = pack_bounds(args.character_pack, args.decomp)
        char_by_name = {}
        for gid, (name, _d, _ze, _uv) in cb.items():
            char_by_name.setdefault(name, []).append(gid)

    rows = []

    pack_tex = {}
    shape_tex = {}
    name_tex = {}
    a2p, _unplaced, placed = {}, set(), set()
    if args.textures or not args.keep_placed:
        a2p, _unplaced, placed = walk_live_pack(ram, args.pack, args.decomp)
    if args.textures:
        import texture_map
        tm = texture_map.TextureMap(ram)
        pack_tex = tm.pack_id_textures(a2p)
        shape_tex = tm.per_shape_pack_textures(pack_shape_keys(args.pack, args.decomp))
        name_tex = tm.name_textures
        print("  textures: %d pack mesh(es) content-match, %d by (primType,numPrims) key (#565),"
              " %d live shape name(s)" % (len(pack_tex), len(shape_tex), len(name_tex)))

    normals, fallback = {}, (None, None)
    if args.textures and args.stage_material:
        normals = pack_normals(args.pack, args.decomp)
        fallback = stage_fallback_textures(ram, args.ground_tex, args.wall_tex)
        print("  stage material fallback: ground %s / wall %s" % (fallback[0], fallback[1]))

    def row(matrix, *ids, fb=None, name=None):
        if name and name in prop_tex:
            texs = [prop_tex[name]]
        else:
            # The per-shape binding (#565) first: the live material's own shape's texture, keyed by
            # (primType, numPrims).  Then the vertex-buffer content match, the live shape name, and
            # the stage-material fallback (#544) for the RamData-drawn meshes none of the above reach.
            texs = sorted({t for i in ids for t in shape_tex.get(i, ())})
            if not texs:
                texs = sorted({t for i in ids for t in pack_tex.get(i, ())})
            if not texs and name:
                # A pack mesh whose live shape carries a node-held material: the content match can
                # miss it (the character's skinned mesh is not matched), but its live shape still
                # names its texture (TextureMap.name_textures).
                texs = sorted(name_tex.get(name, ()))
            if not texs and fb:
                texs = list(fb)
        line = "-\t%s\t\t0x0\t%s" % (" ".join("%.6f" % v for v in matrix),
                                      ",".join(str(i) for i in ids))
        if args.textures:
            line += "\t" + ",".join(texs)
        rows.append(line)

    # 1. the world-space environment: identity.  The world test has two parts: a screen-space
    #    UI/backdrop card is flat in z (finding #546), and a mesh the live scene *places* (a prop,
    #    a backdrop sphere) must not be drawn at identity -- only the unplaced shapes are authored
    #    in world space (finding #520).  Together they replace the old `--big`-only heuristic.
    ident = [1.0, 0, 0, 0, 0, 1.0, 0, 0, 0, 0, 1.0, 0, 0, 0, 0, 1.0]
    # A mesh that is placed *and* also drawn unplaced is still world geometry, so only the
    # placed-only ids are dropped.
    placed_only = placed - _unplaced
    env = [gid for gid, (_n, d, ze, uv) in bounds.items()
           if d > args.big and ze > args.min_z and gid not in placed_only
           and gid not in set(args.drop_id)
           and (uv or args.include_untextured)]
    for gid in env:
        fb = None
        if fallback[0] is not None:
            n = normals.get(gid)
            if n is not None:
                # The floor is the one *near-planar horizontal* mesh (31788 on Goblin Pass: mean
                # normal (0.04, 1.00, 0.02)); the wall/dome wraps, so its mean normal is tilted
                # even though it still points up (21835: (-0.47, 0.86, 0.19)).  The plain
                # `n[1] > 0.5` test called both of them floor and put the ground texture on the
                # wall (finding #547).
                planar = abs(n[0]) + abs(n[2])
                fb = fallback[0] if (n[1] > 0.5 and planar < 0.15) else fallback[1]
        row(ident, gid, fb=fb)

    # 2. the character (a named skin) at the node nearest the look-at
    if args.character:
        if args.target is None:
            ap.error("--character needs --target")
        node = nearest_node(ram, args.target)
        if not node:
            print("camera_match: no beModelCtrlNode2 near the target", file=sys.stderr)
            return 1
        if args.character == "auto":
            ids = skinned_char_ids(ram, args.pack, args.decomp)
            label = "auto(skinned)"
        else:
            ids = char_by_name.get(args.character, [])
            if not ids:
                # a prefix names the whole skinned graph: the player is three shapes
                # (P_susanoo_Skin0Shape0/1/2) placed by the same node matrix
                ids = sorted(i for n, g in char_by_name.items()
                             if n and n.startswith(args.character) for i in g)
            label = args.character
        row(m16(ram, node + 0x20), *ids,
            name=args.character if args.character != "auto" else None)
        if args.character_tex:
            rows[-1] = rows[-1].rsplit("\t", 1)[0] + "\t" + args.character_tex
            print("  character texture override: %s" % args.character_tex)
        print("  character %s at node 0x%08x -> %d mesh(es)"
              % (label, node, len(ids)))

    # 3. runtime props at explicit node transforms
    for spec in args.prop:
        mesh, _, addr = spec.partition("@")
        ids = by_name.get(mesh, [])
        row(m16(ram, int(addr, 0) + 0x20), *ids, name=mesh)
        print("  prop %s at 0x%08x -> %d mesh(es)" % (mesh, int(addr, 0), len(ids)))

    with open(args.tsv, "w") as f:
        f.write("\n".join(rows) + "\n")
    print("wrote %s: %d row(s) (%d environment meshes)" % (args.tsv, len(rows), len(env)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
