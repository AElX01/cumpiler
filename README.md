# Cumpiler: Medical Prescription JSON Validator

> **⚠️ DISCLAIMER: For Educational Purposes Only**
> This software is a proof-of-concept developed for academic and educational purposes (specifically demonstrating formal languages, lexical analysis, and parsing). It is **not** certified, tested, or intended for use in real-world healthcare, medical, or clinical environments. Do not use this to process actual patient data or validate real medical prescriptions.

**Cumpiler** is a specialized, lightweight compiler front-end designed to validate Electronic Medical Prescriptions (Recetas Médicas Electrónicas) formatted in JSON. It performs comprehensive lexical, syntactic, and semantic analysis to ensure that medical documents adhere to a strict structural schema and logical medical constraints.

Supported on **Linux** and **Windows**.

## Features

* **Lexical Analysis:** Custom tokenizer that recognizes structural JSON elements, specific medical keywords, and validates complex strings (e.g., dates `dd/mm/yyyy` and 8-digit professional IDs) via regular expressions.
* **Syntactic Analysis:** A top-down recursive descent parser that validates the nested JSON structure (e.g., ensuring `paciente`, `medico`, and `medicamentos` arrays exist in the correct hierarchy).
* **Semantic Validation:** Built-in logic to verify medication rules. For example, it ensures that *Paracetamol* is prescribed in `mg` (not `ml`), checks for valid intervals (e.g., 6, 8, or 12 hours), and validates treatment durations.
* **No Heavy Dependencies:** Uses a custom memory allocator and a minimal regex engine.

## Dependencies

This project relies on two external third-party libraries integrated as submodules:

1. **[alloc.h](https://github.com/AElX01/alloc.h):** An `stb`-style single-header custom memory allocator (owned by @Pap0m contributor).
2. **[tiny-regex-c](https://github.com/kokke/tiny-regex-c):** A small and portable regular expression implementation in C.

## Getting Started

### 1. Cloning the Repository

Because this project relies on Git submodules for its dependencies, **you must use the `--recurse-submodules` flag** when cloning. Additionally, the C implementation is located on the `c_port` branch.

Run the following command:

```bash
git clone --recurse-submodules https://github.com/AElX01/cumpiler.git
cd cumpiler

```

*(Note: If you accidentally cloned without the submodules, you can fetch them later by running `git submodule update --init --recursive` from the project root).*

### 2. Building the Project

You can compile the project using one of the following methods:

#### Method A: Using Meson (Recommended)

If you have [Meson](https://mesonbuild.com/) and Ninja installed:

```bash
meson setup build
meson compile -C build

```

#### Method B: Using the Bash Script

For Unix-like environments (Linux, macOS, or WSL):

```bash
bash build.sh

```

#### Method C: Single-Command Compilation (Clang / GCC)

You can compile manually by linking the necessary source files:

```bash
# Using Clang
clang -O3 -flto -DNDEBUG -w -Wpedantic -Wconversion -Wshadow -Wformat=2 \
    -fstack-protector-strong -D_FORTIFY_SOURCE=3 -pie -static \
    -Wl,-z,relro,-z,now -Wl,--strip-all \
    thirdparty/tiny-regex-c/re.c utils.c parser.c lexer.c cumpiler.c \
    -o cumpiler

# Using GCC
gcc -O3 -flto -DNDEBUG -w -Wpedantic -Wconversion -Wshadow -Wformat=2 \
    -fstack-protector-strong -D_FORTIFY_SOURCE=3 -pie -static \
    -Wl,-z,relro,-z,now -Wl,--strip-all \
    thirdparty/tiny-regex-c/re.c utils.c parser.c lexer.c cumpiler.c \
    -o cumpiler

```

## Usage

Pass the target JSON file as an argument to the generated executable:

```bash
cd build
./cumpiler <json file> 

```

If the file is valid, the program will exit silently with code `0`. If there are lexical, syntax, or semantic errors, it will print descriptive error messages detailing the expected vs. found tokens and the line numbers where the violations occurred.

## Accepted JSON Schema

The tool specifically expects an electronic prescription format (`receta`). Below is a minimal example of the valid structure:

```json
{
  "receta": {
    "fecha": "15/04/2026",
    "paciente": {
      "nombre": "Juan Pérez López",
      "edad": 42
    },
    "medico": {
      "nombre": "Dra. Laura Hernández",
      "cedula": "12345678"
    },
    "medicamentos": [
      {
        "nombre": "Amoxicilina",
        "dosis": {
          "cantidad": 500,
          "unidad": "mg"
        },
        "frecuencia": {
          "intervalo": 8,
          "unidad": "horas"
        },
        "duracion": {
          "cantidad": 7,
          "unidad": "dias"
        }
      }
    ],
    "indicaciones": [
      "Tomar después de alimentos"
    ]
  }
}

```

## Project Structure

```text
.
├── build.sh             # Convenience script for Unix systems
├── cumpiler.c           # Application entry point
├── docs/                # Generated documentation (HTML)
├── Doxyfile             # Doxygen configuration for documentation
├── json_files/          # Directory containing test cases (.json)
├── lexer.c / .h         # Lexical analyzer (tokenizer)
├── parser.c / .h        # Recursive descent parser & semantic logic
├── utils.c / .h         # Utility functions (Regex wrappers)
├── meson.build          # Meson build system configuration
└── thirdparty/          # Dependencies
    ├── alloc.h          # Custom memory allocator
    └── tiny-regex-c     # Regex engine

```
