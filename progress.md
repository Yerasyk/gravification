# Gravification — learning progress

Last updated: 2026-10-27

## Goal and working approach

Build and eventually ship a slow, calm gravity and accretion game in C++, with 3D physics viewed on a 2D screen: the player controls a body that grows from rock to black hole while avoiding bigger bodies (see design.md). Learn OpenGL and simulation physics along the way. Keep the first version small and its physical approximations understandable; gas and star formation are longer-term possibilities, not initial requirements.

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

- Added GLAD (gl-api-33) and initialized it after making the context current.
- Drew triangles with VBO/VAO/EBO, wireframe toggle, and two shader programs switchable from ImGui.
- Wrote a Shader class that loads shader files, compiles, links, and reports errors.
- Viewport now uses glfwGetFramebufferSize.

## Current stage: roadmap step 1 (LearnOpenGL essentials)

Game design and full roadmap: see design.md.

Next task: finish the Shaders chapter (uniforms). The Shader::setBool/setInt/setFloat functions currently only look up the uniform location and never call glUniform*, so they set nothing. Test: animate a color with glfwGetTime().

Then: Transformations (GLM) → Coordinate Systems → Camera.

Keep the code in main.cpp while it remains easy to understand. Introduce abstractions when there is a concrete need.

## Follow-up checks

- Shader file paths are relative ("./shaders/..."), so they depend on the working directory the program runs from.
- Review initialization failure handling as new components are added.
- Confirm build/ is excluded from Git before committing generated outputs.
- Use CMake Tools build/run actions consistently. The previously inspected default Ctrl+Shift+B task used g++ directly and bypassed CMake; check it before relying on that shortcut.

## Planned

The roadmap lives in design.md. Physics checks to keep along the way: units, numerical stability, energy and momentum before increasing particle counts; profile before choosing acceleration structures or GPU simulation.

Long-term topics: angular momentum and spin, fragmentation, composition, gas and thermodynamics, and the limits of the accretion model. These are not needed for the next learning milestone.

## Notes already learned

- vcpkg.json declares dependencies; CMake finds and links the libraries used by an executable.
- Headers declare functions; the linker needs the libraries containing their implementations.
- Variables initialized inside the frame loop reset every frame; persistent editable state belongs outside it.
- A frame follows clear background → draw scene → draw ImGui → present.

Update this file as milestones are completed, plans change, or new checks are discovered. Distinguish implemented code from planned work and user-reported success from newly executed verification.
