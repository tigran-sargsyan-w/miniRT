# miniRT
This project is an introduction to the beautiful world of Raytracing. Once completed you will be able to render simple Computer-Generated-Images and you will never be afraid of implementing mathematical formulas again.

For leaks-check:

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT scenes/valgrind_check.rt

# miniRT — Leak Check Scenarios

Используй эту таблицу как чек-лист. В колонке **Статус** можешь ставить `✅` / `❌` или комментарий.

---

## Категория 1 — Аргументы командной строки

| # | Сценарий                     | Что сделать / ожидаемое поведение                                                                              | Статус |
| - | ---------------------------- | -------------------------------------------------------------------------------------------------------------- | ------ |
| 1 | Нет аргументов               | Запустить `./miniRT` без аргументов. Программа выводит сообщение об ошибке/usage и корректно завершает работу. |   ✅   |
| 2 | Слишком много аргументов     | Запустить `./miniRT scene1.rt scene2.rt`. Программа выводит ошибку и корректно завершается без утечек.         |   ✅   |
| 3 | Неверное расширение файла    | Запустить `./miniRT scene.txt`. Ошибка формата, корректное завершение.                                         |   ✅   |
| 4 | Путь указывает на директорию | Запустить `./miniRT scenes/` (где `scenes/` — папка). Ошибка открытия файла, корректный выход без утечек.      |   ✅   |

---

## Категория 2 — Ошибки работы с файлом

| # | Сценарий                               | Что сделать / ожидаемое поведение                                                                                          | Статус |
| - | -------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- | ------ |
| 5 | Файл не существует                     | `./miniRT scenes/not_found.rt`. Ошибка `open`, программа ничего не парсит и полностью освобождает всё, что успела создать. |   ✅   |
| 6 | Нет прав на чтение                     | `chmod 000 scenes/no_read.rt` → `./miniRT scenes/no_read.rt`. Ошибка доступа, корректный выход без утечек.                 |   ✅   |
| 7 | Пустой файл                            | `./miniRT scenes/empty.rt`. Файл без содержимого. Ошибка (нет обязательных элементов), все ресурсы очищены.                |   ✅   |
| 8 | Файл с пробелами/переносами/комментами | `./miniRT scenes/spaces_only.rt` (только пустые строки, пробелы, `#`-комментарии). Ошибка валидности сцены, без утечек.    |   ✅   |

---

## Категория 3 — Ошибки парсера

| #  | Сценарий                         | Что сделать / ожидаемое поведение                                                                                                | Статус |
| -- | -------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- | ------ |
| 9  | Ошибка в первой строке           | `err_first_line.rt`: первая строка содержит неправильный идентификатор/формат. Программа сразу падает в ошибку и чистит всё.     |   ✅   |
| 10 | Ошибка в середине файла          | `err_middle_object.rt`: сначала валидные `A/C/L` и несколько объектов, затем битая строка. При ошибке очищается вся сцена.       |   ✅   |
| 11 | Ошибка в последней строке        | `err_last_line.rt`: много валидных объектов + ошибка в самом конце. Полная сцена очищается при выходе по ошибке.                 |   ✅   |
| 12 | Отсутствует камера               | `err_no_camera.rt`: в файле есть свет/объекты, но нет `C`. После парсинга проверка валидности сцены падает с ошибкой без утечек. |   ✅   |
| 13 | Несколько камер (если запрещено) | `err_multi_camera.rt`: две или больше строк `C`. Проверка конфигурации ловит ошибку и всё освобождает.                           |   ✅   |
| 14 | Некорректные числовые значения   | `err_bad_number.rt`: неверные координаты/цвет/нормаль (`abc`, слишком большие значения, и т.п.). Ошибка парсинга без утечек.     |   ✅   |
| 15 | Неизвестный идентификатор        | `err_unknown_id.rt`: строка с неизвестным типом (`XX` и т.п.). Парсер выдаёт ошибку и очищает уже созданные объекты.             |   ✅   |

---

## Категория 4 — Инициализация графики (mlx / окна / изображения)

> Для этих тестов удобно временно вставлять искусственные ошибки в код (в отладочной сборке), чтобы возвращать `ERROR` на нужных шагах после успешного парсинга.

| #  | Сценарий                             | Что сделать / ожидаемое поведение                                                                                                        | Статус |
| -- | ------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------- | ------ |
| 16 | Сбой на `init_mlx`                   | После успешного `parse_scene` искусственно вернуть ошибку в `init_mlx`. Программа должна вызвать общий cleanup и завершиться без утечек. |   ✅   |
| 17 | Сбой при создании окна               | `mlx` инициализировался, но создание окна возвращает ошибку. Всё уже созданное (`mlx`, сцена и т.п.) освобождается.                      |   ❌   |
| 18 | Сбой при создании изображения/буфера | Окно создано, но `mlx_new_image` (или аналог) «проваливается». Программа делает cleanup и выходит без утечек.                            |   ❌   |
| 19 | Сбой при инициализации хуков/событий | Окно и изображение готовы, но ошибка/искусственный `ERROR` на этапе установки событий. Очистить сцену, окно, изображение.                |   ❌   |

---

## Категория 5 — Нормальный запуск и все пути выхода

| #  | Сценарий                                      | Что сделать / ожидаемое поведение                                                                                               | Статус |
| -- | --------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------- | ------ |
| 20 | Запуск → ничего не делать → выход по ESC      | Открыть окно, не трогать сцену, нажать ESC. Должен отработать общий `cleanup`, утечек нет.                                      |        |
| 21 | Запуск → ничего не делать → закрыть крестиком | Открыть окно и закрыть его через [X]. Обработчик `destroy` вызывает тот же `cleanup`, утечек нет.                               |        |
| 22 | Активное управление → выход по ESC            | Подвигать камеру/зум/переключение камер (если есть), затем ESC. Все структуры, связанные с состоянием, должны быть освобождены. |        |
| 23 | Активное управление → закрыть крестиком       | То же, что 22, но выход через [X]. Проверка, что оба пути выхода одинаково хорошо чистят ресурсы.                               |        |
| 24 | Выбор/изменение объекта → ESC                 | Если есть выбор объекта/редактирование параметров: выбрать несколько объектов, изменить их, выйти по ESC без утечек.            |        |
| 25 | Выбор/изменение объекта → закрыть крестиком   | Аналогично, но выход через [X].                                                                                                 |        |
| 26 | Работа с меню/GUI (открытие/закрытие)         | Если есть меню/оверлей: несколько раз открыть/закрыть, потыкать пункты, потом выйти (ESC/[X]). Не должно быть утечек от GUI.    |        |

---

## Категория 6 — Длительная работа и "капельные" утечки

| #  | Сценарий                     | Что сделать / ожидаемое поведение                                                                                                                            | Статус |
| -- | ---------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------ |
| 27 | Длительная работа            | Запустить под Valgrind, несколько минут крутить камеру/двигаться. Потом выйти (ESC или [X]). Если в цикле есть `malloc` без `free`, Valgrind покажет утечки. |        |
| 28 | Стресс-тест быстрых действий | Быстро переключать камеры, выбирать объекты, открывать/закрывать меню и т.д., затем выйти. Проверка редких веток кода на утечки.                             |        |

---

## Категория 7 — Искусственные ошибки в рантайме (опционально)

| #  | Сценарий                             | Что сделать / ожидаемое поведение                                                                                                                                                                                                     | Статус |
| -- | ------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------ |
| 29 | Симуляция ошибки `malloc` в рантайме | В отладочной сборке добавить счётчик аллокаций и заставить `malloc` вернуть `NULL` при определённом вызове внутри цикла/события. Программа должна корректно обработать ошибку и при завершении освободить все уже выделенные ресурсы. |        |

---

> Совет: рядом с этой таблицей можешь вести заметки: какие именно команды запускаешь (полные строки Valgrind), и какие именно файлы `.rt` используешь для каждого сценария.


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
