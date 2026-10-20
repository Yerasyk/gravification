# Gravification — learning progress

Last updated: 2026-10-20

## Goal and working approach

Build and eventually ship a slow, approachable gravity and accretion sandbox in C++, with 3D physics viewed on a 2D screen. Explore particles merging into larger bodies while learning OpenGL and simulation physics. Keep the first version small and its physical approximations understandable; gas and star formation are longer-term possibilities, not initial requirements.

The user writes the implementation. The assistant teaches, reviews, explains errors, and suggests small exercises. Do not implement game features unless explicitly requested. See AGENTS.md.

## Finished

- Set up development in VS Code with MSVC and C++20.
- Created CMakeLists.txt and learned the configure → build → run workflow.
- Learned that build/ contains generated files and can be regenerated.
- Connected the existing C:/dev/vcpkg installation through workspace CMake settings.
- Declared GLFW and ImGui dependencies in vcpkg.json, including GLFW and OpenGL3 ImGui backends.
- Found and linked GLFW, ImGui, and OpenGL in CMake.
- Created an 800 × 600 GLFW window requesting an OpenGL 3.3 core context.
- Added event processing, buffer swapping, and cleanup.
- Cleared the background using an RGB array that persists between frames.
- Initialized ImGui, added a Settings panel with a background color editor, and added frame rendering and cleanup.
- User confirmed the window and interactive color picker work.
- Understood why clearing must happen before drawing: clearing afterward erases the drawing.

## Current stage: first custom OpenGL drawing

Next milestone: draw a triangle behind the ImGui panel.

Next task: check which GLAD version the local vcpkg port supplies, then teach its installation, header order, and initialization for this project. GLAD has not been added yet. ImGui's renderer has its own loader; that does not expose modern OpenGL functions to our application code.

Proceed in small checkpoints:

1. Add and initialize GLAD; verify the existing window and interface still work.
2. Learn vertex positions and upload three vertices using a VBO and VAO.
3. Learn and compile a minimal vertex shader and fragment shader, including error reporting.
4. Issue the triangle draw call between clearing and rendering ImGui.
5. Release the OpenGL resources during shutdown.

Keep the code in main.cpp while it remains easy to understand. Introduce abstractions when there is a concrete need.

## Follow-up checks

- Use glfwGetFramebufferSize for glViewport dimensions. The current code uses glfwGetWindowSize; window coordinates and framebuffer pixels can differ with display scaling.
- Review initialization failure handling as new components are added.
- Confirm build/ is excluded from Git before committing generated outputs.
- Use CMake Tools build/run actions consistently. The previously inspected default Ctrl+Shift+B task used g++ directly and bypassed CMake; check it before relying on that shortcut.

## Planned after the triangle

1. Render a particle and expose its visual properties through ImGui.
2. Move one particle using position, velocity, and elapsed time.
3. Separate a fixed physics timestep from frame rendering; add pause and single-step controls.
4. Simulate two gravitationally attracting bodies and study a stable orbit.
5. Check units, numerical stability, energy, and momentum before increasing particle counts.
6. Add a small many-body simulation with direct CPU gravity.
7. Add sphere collisions and a clearly documented simplified merging model conserving mass and linear momentum.
8. Add approachable sandbox interactions, trails, inspection, save/load, and learning scenarios.
9. Profile before choosing acceleration structures or GPU simulation.

Long-term topics: angular momentum and spin, fragmentation, composition, gas and thermodynamics, and the limits of the accretion model. These are not needed for the next learning milestone.

## Notes already learned

- vcpkg.json declares dependencies; CMake finds and links the libraries used by an executable.
- Headers declare functions; the linker needs the libraries containing their implementations.
- Variables initialized inside the frame loop reset every frame; persistent editable state belongs outside it.
- A frame follows clear background → draw scene → draw ImGui → present.

Update this file as milestones are completed, plans change, or new checks are discovered. Distinguish implemented code from planned work and user-reported success from newly executed verification.
