# miniRT

✅ **Status**: Completed  
🏫 **School**: 42 – miniRT  
🏅 **Score**: 100/100  

`miniRT` is an educational **ray tracer** (42 school project): it parses `.rt` scenes, ray-traces basic primitives (sphere/plane/cylinder), computes lighting & shadows, and displays the result using **MiniLibX (X11/Linux)**.

> Repository: https://github.com/tigran-sargsyan-w/miniRT

---

## Gallery (render results)

Add your best renders here to showcase the program’s features and visual quality.

> Tip: store images inside `docs/gallery/` and link them below.

### Showcase #1 — _scene name / short description_
<!-- TODO: add image -->
<!-- Example: ![showcase-1](docs/gallery/showcase-1.png) -->

### Showcase #2 — _scene name / short description_
<!-- TODO: add image -->
<!-- ![showcase-2](docs/gallery/showcase-2.png) -->

### Showcase #3 — _scene name / short description_
<!-- TODO: add image -->
<!-- ![showcase-3](docs/gallery/showcase-3.png) -->

---

## Features

- Parse scene from `.rt` file
- Primitives:
  - `sp` — sphere
  - `pl` — plane
  - `cy` — cylinder (including caps)
- Lights:
  - `A` — ambient light
  - `L` — point light
- `C` — camera (position / direction / FOV)
- Shadows (shadow rays / occlusion)
- Rendering via MiniLibX (window + image buffer)
- **Feature: Runtime Transform (Translate / Rotate / Scale)** — interactively transform objects while the program is running
- **Feature: OOP-like design in C (interface / polymorphism via function pointers)** — a unified object “interface” implemented by each primitive

---

## Controls (Runtime Transform)

### Object selection
- **LMB (Left Mouse Click)** — select an object
- `ESC` — cancel selection (unselect)
- Window close button `[X]` — quit
- `ESC` — quit (when nothing is selected / depending on your logic)

### Translate — `WASDQE`
- `W / S` — forward / backward
- `A / D` — left / right
- `Q / E` — down / up

### Rotate — `J I L K U O`
- `J / L` — rotate around **Y** (yaw)
- `I / K` — rotate around **X** (pitch)
- `U / O` — rotate around **Z** (roll)

### Scale
- `← / →` — **uniform scale** (scale up / down)
- `↑ / ↓` — **height scale** (scale height)

> Note: height scale is especially useful for cylinders, but can be applied to any object depending on the implementation.

---

## Architecture: “Interface” & Polymorphism in C

This project uses an OOP-like approach in pure C:

- `t_object` is the **base abstraction**
- each primitive “implements” the same operations (intersection + transforms)
- the implementation is plugged in using **function pointers** (like a vtable)

### 1) The “interface” (function pointers)

File: `include/object.h`

`struct s_object` contains pointers to operations:

- `intersect_func` — ray/object intersection
- `translate` — move
- `rotate_euler` — Euler rotation (rx, ry, rz)
- `scale_uniform` — uniform scale
- `scale_height` — height scale

```c
typedef int  (*t_intersect_func)(const t_object *object, t_ray ray,
                                 t_range range, t_hit *hit_result);
typedef void (*t_translate_func)(t_object *object, t_vector3 delta);
typedef void (*t_rotate_euler_func)(t_object *object, double rx, double ry, double rz);
typedef void (*t_scale_func)(t_object *object, double factor);
typedef void (*t_scale_height_func)(t_object *object, double factor);

typedef struct s_object
{
    t_object_type         type;
    t_material            material;

    t_intersect_func      intersect_func;
    t_translate_func      translate;
    t_rotate_euler_func   rotate_euler;
    t_scale_func          scale_uniform;
    t_scale_height_func   scale_height;
} t_object;
```

### 2) Abstraction: base object initializer

File: `src/scene_utils/object.c`

A single `object_init()` binds a concrete implementation (set of functions) to the object:

```c
void object_init(t_object *object, t_object_type type,
                 t_material material, t_object_funcs funcs)
{
    object->type = type;
    object->material = material;
    object->intersect_func = funcs.intersect;
    object->translate = funcs.translate;
    object->rotate_euler = funcs.rotate_euler;
    object->scale_uniform = funcs.scale_uniform;
    object->scale_height = funcs.scale_height;
}
```

### 3) Concrete implementations: primitives “implement the interface”

Example: `src/objects/plane.c` (similar in `sphere.c`, `cylinder.c`)

```c
funcs.intersect = &intersect_plane;
funcs.translate = &plane_translate;
funcs.rotate_euler = &plane_rotate;
funcs.scale_uniform = &plane_scale_uniform;
funcs.scale_height = &plane_scale_height;

object_init(&plane->base, PLANE, material, funcs);
```

This lets the renderer & event system work with `t_object*` **without knowing the concrete shape type**.

---

## Quick Start

### 1) Clone

```bash
git clone --recursive https://github.com/tigran-sargsyan-w/miniRT.git
cd miniRT
```

If you already cloned without `--recursive`:

```bash
git submodule update --init --recursive
```

### 2) Dependencies (Linux)

MiniLibX on Linux requires X11. Typical packages:

- Debian/Ubuntu:
  ```bash
  sudo apt-get install -y build-essential libx11-dev libxext-dev zlib1g-dev libbsd-dev
  ```
- Arch:
  ```bash
  sudo pacman -S --needed base-devel libx11 libxext zlib libbsd
  ```

### 3) Build

```bash
make
```

Clean:
```bash
make clean
make fclean
make re
```

---

## Run

```bash
./miniRT scenes/colored_room_with_sphere.rt
```

Scenes: [`scenes/`](https://github.com/tigran-sargsyan-w/miniRT/tree/main/scenes)

---

## `.rt` scene format (brief)

```text
A 0.15 255,255,255
C 0,8,-30 0,0,1 65
L -5,18,-5 0.8 255,255,255

pl 0,0,0   0,1,0   0,0,255
sp 0,5,35  10      220,220,220
```

---

## Leak check (Valgrind)

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
  ./miniRT scenes/valgrind_check.rt
```

---

# miniRT — Leak Check Scenarios

Use this checklist to systematically test memory leak paths.  
In the **Status** column you can mark `✅` / `❌` or add a short note.

---

## Category 1 — Command line arguments

| # | Scenario | What to do / expected behavior | Status |
| - | -------- | ------------------------------ | ------ |
| 1 | No arguments | Run `./miniRT` with no args. Should print error/usage and exit cleanly (no leaks). | ✅ |
| 2 | Too many arguments | Run `./miniRT scene1.rt scene2.rt`. Should print error and exit cleanly. | ✅ |
| 3 | Invalid file extension | Run `./miniRT scene.txt`. Should detect invalid format and exit cleanly. | ✅ |
| 4 | Path is a directory | Run `./miniRT scenes/` (where `scenes/` is a folder). Should fail to open as file and exit cleanly. | ✅ |

---

## Category 2 — File I/O errors

| # | Scenario | What to do / expected behavior | Status |
| - | -------- | ------------------------------ | ------ |
| 5 | File does not exist | `./miniRT scenes/not_found.rt`. Should report `open` error and free everything. | ✅ |
| 6 | No read permission | `chmod 000 scenes/no_read.rt` → `./miniRT scenes/no_read.rt`. Should report access error and exit cleanly. | ✅ |
| 7 | Empty file | `./miniRT scenes/empty.rt`. Should fail validation (missing required elements) and free resources. | ✅ |
| 8 | Only spaces/newlines/comments | `./miniRT scenes/spaces_only.rt` (blank lines/spaces/`#` only). Scene invalid, exit cleanly. | ✅ |

---

## Category 3 — Parser errors

| # | Scenario | What to do / expected behavior | Status |
| -- | ------- | ------------------------------ | ------ |
| 9 | Error in the first line | `err_first_line.rt`: invalid identifier/format. Parser must stop and free everything. | ✅ |
| 10 | Error in the middle | `err_middle_object.rt`: valid start, then broken line. Must free the whole scene. | ✅ |
| 11 | Error in the last line | `err_last_line.rt`: many valid objects + invalid last line. Must free everything. | ✅ |
| 12 | Missing camera | `err_no_camera.rt`: no `C`. Validation fails and everything is freed. | ✅ |
| 13 | Multiple cameras (if forbidden) | `err_multi_camera.rt`: 2+ `C` lines. Config error and full cleanup. | ✅ |
| 14 | Bad numeric values | `err_bad_number.rt`: invalid coords/color/normal (e.g. `abc`, overflow). Clean exit. | ✅ |
| 15 | Unknown identifier | `err_unknown_id.rt`: unknown type (e.g. `XX`). Error + full cleanup. | ✅ |

---

## Category 4 — Graphics initialization (mlx / window / image)

> For these tests it’s convenient to temporarily inject forced failures in a debug build after a successful parse.

| # | Scenario | What to do / expected behavior | Status |
| -- | ------- | ------------------------------ | ------ |
| 16 | Failure in `init_mlx` | After `parse_scene`, force `init_mlx` to fail. Must run global cleanup with no leaks. | ✅ |
| 17 | Window creation failure | `mlx` initialized but window creation fails. All resources freed. | ✅ |
| 18 | Image/buffer creation failure | Window exists but `mlx_new_image` (or equivalent) fails. Cleanup and exit. | ✅ |
| 19 | Hooks/events setup failure | Window+image OK, but hooks setup fails. Must free scene/window/image. | ✅ |

---

## Category 5 — Normal run & all exit paths

| # | Scenario | What to do / expected behavior | Status |
| -- | ------- | ------------------------------ | ------ |
| 20 | Start → do nothing → ESC | Open window, press ESC. Cleanup must run. | ✅ |
| 21 | Start → close via [X] | Close the window using [X]. Cleanup must match ESC path. | ✅ |
| 22 | Select/transform object → ESC | Select object, translate/rotate/scale, then exit. No leaks. | ✅ |
| 23 | Select/transform object → [X] | Same as 22 but exit via [X]. No leaks. | ✅ |

---

## Category 6 — Long run & “drip” leaks

| # | Scenario | What to do / expected behavior | Status |
| -- | ------- | ------------------------------ | ------ |
| 24 | Long session | Run under Valgrind, keep window open for minutes, select and transform objects, then exit. Loop leaks should appear here. | ✅ |
| 25 | Stress test | Rapidly select objects and apply many transforms, then exit. Should catch rare leak branches. | ✅ |
