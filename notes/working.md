# C++ Compilation Steps (Short)

1. **Preprocessing**
   - Handles `#include`, `#define`, macros
   - Expands libraries into code
   - **Output:** Preprocessed file (`.i`)

2. **Compilation**
   - Converts code to assembly instructions
   - Detects syntax errors
   - **Output:** Assembly file (`.s`)

3. **Assembly**
   - Converts assembly to object code (machine code)
   - **Output:** Object file (`.o` or `.obj`)d

4. **Linking**
   - Combines object files & libraries into executable
   - Handles external references (`cout`, etc.)
   - **Output:** Executable (`.exe` on Windows, no extension on Linux)
