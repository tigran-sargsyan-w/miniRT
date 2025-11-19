# miniRT
This project is an introduction to the beautiful world of Raytracing. Once completed you will be able to render simple Computer-Generated-Images and you will never be afraid of implementing mathematical formulas again.

For leaks-check:

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT scenes/valgrind_check.rt

# miniRT — Leak Check Scenarios

Use this checklist to systematically test your program for memory leaks. In the **Status** column you can put `✅` / `❌` or add a short comment.

---

## Category 1 — Command Line Arguments

| # | Scenario               | What to do / expected behavior                                                                                          | Status |
| - | ---------------------- | ----------------------------------------------------------------------------------------------------------------------- | ------ |
| 1 | No arguments           | Run `./miniRT` with no arguments. Program should print usage/error message and exit cleanly (no leaks).                 |        |
| 2 | Too many arguments     | Run `./miniRT scene1.rt scene2.rt`. Program should print an error and exit cleanly.                                     |        |
| 3 | Invalid file extension | Run `./miniRT scene.txt`. Program should detect invalid extension/format and exit without leaks.                        |        |
| 4 | Path is a directory    | Run `./miniRT scenes/` where `scenes/` is a directory. Program should fail to open it as a file and exit without leaks. |        |

---

## Category 2 — File I/O Errors

| # | Scenario                      | What to do / expected behavior                                                                                                  | Status |
| - | ----------------------------- | ------------------------------------------------------------------------------------------------------------------------------- | ------ |
| 5 | File does not exist           | Run `./miniRT scenes/not_found.rt`. Program should report `open` error and exit, freeing anything it may have allocated.        |        |
| 6 | No read permission            | `chmod 000 scenes/no_read.rt` then run `./miniRT scenes/no_read.rt`. Program should report access error and exit cleanly.       |        |
| 7 | Empty file                    | Run `./miniRT scenes/empty.rt` where the file is empty. Program should detect missing required elements and exit without leaks. |        |
| 8 | Only spaces/newlines/comments | Run `./miniRT scenes/spaces_only.rt` with blank lines, spaces and `#` comments only. Scene is invalid, program exits cleanly.   |        |

---

## Category 3 — Parser Errors

| #  | Scenario                          | What to do / expected behavior                                                                                                      | Status |
| -- | --------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------- | ------ |
| 9  | Error in the first line           | `err_first_line.rt`: first line has invalid identifier/format. Program should detect it, stop parsing and free everything.          |        |
| 10 | Error in the middle of the file   | `err_middle_object.rt`: valid `A/C/L` and some objects, then a broken line. On error, full scene (all already added data) is freed. |        |
| 11 | Error in the last line            | `err_last_line.rt`: many valid objects, last line is invalid. Program must free the fully built scene on error.                     |        |
| 12 | Missing camera                    | `err_no_camera.rt`: file contains lights/objects but no `C`. After parsing, validation fails and everything is freed.               |        |
| 13 | Multiple cameras (if not allowed) | `err_multi_camera.rt`: two or more `C` lines. Configuration check fails, program frees all scene data and exits.                    |        |
| 14 | Invalid numeric values            | `err_bad_number.rt`: invalid coordinates/color/normal (e.g. `abc`, overflowed values, etc.). Parser reports error, no leaks.        |        |
| 15 | Unknown identifier                | `err_unknown_id.rt`: a line with an unknown type (`XX` or similar). Parser reports error and frees all previously created objects.  |        |

---

## Category 4 — Graphics Initialization (mlx / window / image)

> For these tests it's convenient to temporarily inject artificial failures in your code (debug build) so functions return an error at specific steps *after* successful parsing.

| #  | Scenario                                   | What to do / expected behavior                                                                                                 | Status |
| -- | ------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------ | ------ |
| 16 | Failure in `init_mlx`                      | After a successful `parse_scene`, force `init_mlx` to fail. Program should call global cleanup and exit without leaks.         |        |
| 17 | Failure creating the window                | `mlx` is initialized, but window creation fails (forced). All created resources (`mlx`, scene, etc.) must be freed.            |        |
| 18 | Failure creating image/buffer              | Window is created, but `mlx_new_image` (or equivalent) fails. Program performs cleanup and exits leak-free.                    |        |
| 19 | Failure during hooks/events initialization | Window and image are ready, but an error/forced failure occurs while setting up events. Scene, window and image must be freed. |        |

---

## Category 5 — Normal Run and All Exit Paths

| #  | Scenario                                  | What to do / expected behavior                                                                                             | Status |
| -- | ----------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- | ------ |
| 20 | Start → do nothing → exit via ESC         | Open the window, do nothing, press ESC. Global cleanup is executed, no leaks reported.                                     |        |
| 21 | Start → do nothing → close via window [X] | Open the window and close it with the [X] button. The destroy handler calls the same cleanup, no leaks.                    |        |
| 22 | Active control → exit via ESC             | Move camera/zoom/switch cameras (if implemented), then exit with ESC. All state-related structures are freed.              |        |
| 23 | Active control → close via window [X]     | Same as 22 but exit via [X]. Ensures both exit paths call the same cleanup logic.                                          |        |
| 24 | Select/modify object → ESC                | If you have object selection/editing: select multiple objects, change their params, then ESC. Program exits without leaks. |        |
| 25 | Select/modify object → close via [X]      | Same as 24 but exit via [X].                                                                                               |        |
| 26 | Work with menu/GUI (open/close)           | If you have menu/overlay: open/close it several times, click different options, then exit (ESC/[X]). No GUI-related leaks. |        |

---

## Category 6 — Long-Running and "Drip" Leaks

| #  | Scenario                      | What to do / expected behavior                                                                                                                                                                | Status |
| -- | ----------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------ |
| 27 | Long-running session          | Run under Valgrind, keep the program open for several minutes, moving the camera/character. Then exit (ESC or [X]). Any `malloc` in the loop without a matching `free` will show up as leaks. |        |
| 28 | Stress test with fast actions | Rapidly switch cameras, select objects, open/close menus, etc., then exit. Checks rare code branches for leaks.                                                                               |        |

---

## Category 7 — Artificial Runtime Failures (Optional)

| #  | Scenario                              | What to do / expected behavior                                                                                                                                                                                                             | Status |
| -- | ------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------ |
| 29 | Simulated `malloc` failure at runtime | In a debug build add an allocation counter and force `malloc` to return `NULL` at a specific call inside the loop/event handler. Program should handle the error gracefully and, on exit, free all already allocated resources (no leaks). |        |

---

> Tip: next to this table you can keep a small note section where you write the exact Valgrind command you used and which `.rt` file belongs to each scenario.
