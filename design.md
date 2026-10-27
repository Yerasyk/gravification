# Gravification — game design

Last updated: 2026-10-27

## Core idea

A calm, slow progression game. The player controls one body and grows by absorbing smaller bodies, while avoiding bigger ones that can absorb the player.

Progression: rock → planetoid → planet → gas giant → star → … → pulsar / supernova → black hole.

- A full run to black hole: about 10 hours.
- Players can stop at any stage and keep what they reached (collections).
- Mostly calm, with some danger. Growth is slow, like real formation, but tuned for play.

## Design principles

- **Gravity is the main threat.** Bigger bodies pull you in on their own. Escaping means using thrust well (real orbital mechanics). Add simple behavior (bigger bodies drifting toward you) only later, if needed.
- **3D physics, mostly flat action.** Bodies settle near one plane, like real disks. The player steers within that plane, relative to the camera.
- **Game units, not SI.** Real physics shapes how things behave; the numbers stay in a comfortable float range.
- **Each stage is its own zoom level.** On moving up a stage, the world rescales so the player is "size 1" again; small bodies become dust or are removed; new, bigger neighbors appear.
- **Stages as data.** A table of stages (name, mass needed for the next one, rule flags). Later stages change rules one at a time (for example, a star pushes dust away, a black hole swallows anything inside a radius).
- **Spawn around the player.** Bodies appear near the player and are removed when far away, so the particle count stays small.
- **Pacing is a tuning knob.** Slowness comes from how much mass each stage needs, not from real timescales.
- **Same start + same inputs = same result.** Use a fixed physics timestep.

## Roadmap

1. LearnOpenGL: Shaders (uniforms) → Transformations → Coordinate Systems → Camera. Skip textures, lighting, model loading and advanced chapters for now.
2. Draw particles, fixed timestep, two-body orbit (with energy readout).
3. **Prototype stage 1 (rock → planetoid):** player thrust, dust, bigger bodies, absorb or be absorbed. Goal: fun for 5 minutes.
4. N-body and merging polish, spawning around the player.
5. Stage transition with rescaling, then save/load.
6. More stages, collections, visuals.

Biggest risk is scope, not tech. Prove stage 1 is fun before planning later stages in detail.

## Open questions

- One endless open space around the player, or separate areas per stage?
- What does this game add compared with existing games in the genre (for example, Solar 2)? Candidates: real 3D N-body physics, collections.
- Is there fuel or limited thrust?
