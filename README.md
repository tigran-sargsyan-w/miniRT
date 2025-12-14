# miniRT

✅ **Status**: Completed  
🏫 **School**: 42 – miniRT  
🏅 **Score**: 100/100  

`miniRT` — учебный **ray tracer** (проект школы 42): парсер сцен `.rt`, трассировка лучей (сферы/плоскости/цилиндры), освещение и тени, вывод результата в окно через **MiniLibX (X11/Linux)**.

> Репозиторий: https://github.com/tigran-sargsyan-w/miniRT

---

## Галерея (результаты рендера)

Сюда добавляй лучшие рендеры, чтобы сразу показать работоспособность и «мощность» проекта.

> Рекомендация: складывай картинки в `docs/gallery/` и вставляй их ниже.

### Showcase #1 — _название сцены/описание_
<!-- TODO: add image -->
<!-- Пример: ![showcase-1](docs/gallery/showcase-1.png) -->

### Showcase #2 — _название сцены/описание_
<!-- TODO: add image -->
<!-- ![showcase-2](docs/gallery/showcase-2.png) -->

### Showcase #3 — _название сцены/описание_
<!-- TODO: add image -->
<!-- ![showcase-3](docs/gallery/showcase-3.png) -->

---

## Возможности

- Парсинг сцены из файла формата `.rt`
- Объекты:
  - `sp` — sphere (сфера)
  - `pl` — plane (плоскость)
  - `cy` — cylinder (цилиндр, включая крышки)
- Источники света:
  - `A` — ambient (окружающее освещение)
  - `L` — point light (точечный свет)
- `C` — camera (позиция/направление/FOV)
- Тени (shadow rays / occlusion)
- Вывод через MiniLibX (окно, изображение/буфер)
- **Feature: Runtime Transform (Translate / Rotate / Scale)** — интерактивные трансформации объектов во время работы программы
- **Feature: OOP-like design in C (interface / polymorphism via function pointers)** — единый “интерфейс” для объектов, реализация в конкретных shape-файлах

---

## Управление (Runtime Transform)

### Выбор объекта
- **ЛКМ (Left Mouse Click)** — выбрать объект
- `ESC` — снять выделение (cancel selection)
- Закрытие окна кнопкой `[X]` — выход
- `ESC` — выход из программы (если объект не выделен / либо по твоей логике)

### Translate (перемещение) — `WASDQE`
- `W / S` — вперёд / назад
- `A / D` — влево / вправо
- `Q / E` — вниз / вверх

### Rotate (вращение) — `J I L K U O`
- `J / L` — rotate Y (yaw)
- `I / K` — rotate X (pitch)
- `U / O` — rotate Z (roll)

### Scale (масштабирование)
- `← / →` — **uniform scale** (равномерно увеличить / уменьшить)
- `↑ / ↓` — **height scale** (масштабирование по высоте)

---

## Архитектура: “интерфейс” и полиморфизм в C

В проекте используется OOP-подобный подход: есть **общая абстракция объекта** (`t_object`) и **набор “виртуальных методов”** (функции через указатели).  
Конкретные фигуры (sphere/plane/cylinder) “реализуют интерфейс”, подставляя свои функции пересечения и трансформаций.

### 1) Интерфейс (function pointers)

Файл: `include/object.h`  
Суть: `t_object` содержит указатели на функции:

- `intersect_func` — пересечение луча с объектом
- `translate` — перемещение
- `rotate_euler` — вращение по Euler (rx, ry, rz)
- `scale_uniform` — равномерный scale
- `scale_height` — scale по высоте

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

### 2) Абстракция: инициализация базового объекта

Файл: `src/scene_utils/object.c`  
Единый конструктор `object_init()` “привязывает” реализацию (набор функций) к объекту:

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

### 3) Реализация: конкретные фигуры “подключают” свои методы

Пример: `src/objects/plane.c` (аналогично `sphere.c`, `cylinder.c`)

```c
funcs.intersect = &intersect_plane;
funcs.translate = &plane_translate;
funcs.rotate_euler = &plane_rotate;
funcs.scale_uniform = &plane_scale_uniform;
funcs.scale_height = &plane_scale_height;

object_init(&plane->base, PLANE, material, funcs);
```

Таким образом, дальнейшая логика (рендер/тени/выбор/трансформации) может работать с объектами **через единый интерфейс** `t_object*`, не зная конкретный тип (SPHERE/PLANE/CYLINDER).

---

## Быстрый старт

### 1) Клонирование

```bash
git clone --recursive https://github.com/tigran-sargsyan-w/miniRT.git
cd miniRT
```

Если уже клонировали без `--recursive`:

```bash
git submodule update --init --recursive
```

### 2) Зависимости (Linux)

MiniLibX на Linux использует X11. Обычно нужны пакеты:

- Debian/Ubuntu:
  ```bash
  sudo apt-get install -y build-essential libx11-dev libxext-dev zlib1g-dev libbsd-dev
  ```
- Arch:
  ```bash
  sudo pacman -S --needed base-devel libx11 libxext zlib libbsd
  ```

### 3) Сборка

```bash
make
```

Очистка:
```bash
make clean
make fclean
make re
```

---

## Запуск

```bash
./miniRT scenes/colored_room_with_sphere.rt
```

Сцены: [`scenes/`](https://github.com/tigran-sargsyan-w/miniRT/tree/main/scenes)

---

## Формат сцены `.rt` (кратко)

```text
A 0.15 255,255,255
C 0,8,-30 0,0,1 65
L -5,18,-5 0.8 255,255,255

pl 0,0,0   0,1,0   0,0,255
sp 0,5,35  10      220,220,220
```

---

## Проверка утечек (Valgrind)

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
  ./miniRT scenes/valgrind_check.rt
```

---

# miniRT — Leak Check Scenarios

Используй эту таблицу как чек-лист. В колонке **Статус** можешь ставить `✅` / `❌` или добавлять короткий комментарий.

---

## Категория 1 — Аргументы командной строки

| # | Сценарий | Что сделать / ожидаемое поведение | Статус |
| - | -------- | --------------------------------- | ------ |
| 1 | Нет аргументов | Запустить `./miniRT` без аргументов. Программа выводит сообщение об ошибке/usage и корректно завершает работу (no leaks). |   ✅   |
| 2 | Слишком много аргументов | Запустить `./miniRT scene1.rt scene2.rt`. Программа выводит ошибку и корректно завершается без утечек. |   ✅   |
| 3 | Неверное расширение файла | Запустить `./miniRT scene.txt`. Ошибка формата, корректное завершение. |   ✅   |
| 4 | Путь указывает на директорию | Запустить `./miniRT scenes/` (где `scenes/` — папка). Ошибка открытия файла, корректный выход без утечек. |   ✅   |

---

## Категория 2 — Ошибки работы с файлом

| # | Сценарий | Что сделать / ожидаемое поведение | Статус |
| - | -------- | --------------------------------- | ------ |
| 5 | Файл не существует | `./miniRT scenes/not_found.rt`. Ошибка `open`, программа ничего не парсит и полностью освобождает всё, что успела создать. |   ✅   |
| 6 | Нет прав на чтение | `chmod 000 scenes/no_read.rt` → `./miniRT scenes/no_read.rt`. Ошибка доступа, корректный выход без утечек. |   ✅   |
| 7 | Пустой файл | `./miniRT scenes/empty.rt`. Файл без содержимого. Ошибка (нет обязательных элементов), все ресурсы очищены. |   ✅   |
| 8 | Файл с пробелами/переносами/комментами | `./miniRT scenes/spaces_only.rt` (только пустые строки, пробелы, `#`-комментарии). Ошибка валидности сцены, без утечек. |   ✅   |

---

## Категория 3 — Ошибки парсера

| # | Сценарий | Что сделать / ожидаемое поведение | Статус |
| -- | ------- | --------------------------------- | ------ |
| 9 | Ошибка в первой строке | `err_first_line.rt`: первая строка имеет неверный идентификатор/формат. Парсер должен остановиться и всё освободить. | ✅ |
| 10 | Ошибка в середине файла | `err_middle_object.rt`: валидные `A/C/L`, затем битая строка. На ошибке фридится вся сцена. | ✅ |
| 11 | Ошибка в последней строке | `err_last_line.rt`: много валидного + ошибка в конце. Должно очищаться всё. | ✅ |
| 12 | Отсутствует камера | `err_no_camera.rt`: нет `C`. После парсинга/валидации — ошибка и очистка. | ✅ |
| 13 | Несколько камер (если запрещено) | `err_multi_camera.rt`: две и более `C`. Ошибка конфигурации и полная очистка. | ✅ |
| 14 | Некорректные числа | `err_bad_number.rt`: неверные координаты/цвет/нормали. Ошибка и чистый выход. | ✅ |
| 15 | Неизвестный идентификатор | `err_unknown_id.rt`: неизвестный тип (например `XX`). Ошибка и освобождение всего. | ✅ |

---

## Категория 4 — Инициализация графики (mlx / окно / image)

> Для этих тестов удобно временно сделать debug-режим и “форсировать” неудачные возвраты функций после успешного парсинга.

| # | Сценарий | Что сделать / ожидаемое поведение | Статус |
| -- | ------- | --------------------------------- | ------ |
| 16 | Сбой на `init_mlx` | После `parse_scene` заставить `init_mlx` вернуть ошибку. Должен быть global cleanup без утечек. | ✅ |
| 17 | Сбой при создании окна | `mlx` инициализирован, но окно не создаётся. Все ресурсы освобождены. | ❌ |
| 18 | Сбой при создании image/buffer | Окно создано, но `mlx_new_image` (или аналог) падает. cleanup/выход без утечек. | ❌ |
| 19 | Сбой при настройке hooks/events | Окно и image готовы, но при установке событий ошибка. Освобождение scene/window/image. | ❌ |

---

## Категория 5 — Нормальный запуск и все пути выхода

| # | Сценарий | Что сделать / ожидаемое поведение | Статус |
| -- | ------- | --------------------------------- | ------ |
| 20 | Старта → ничего не делать → ESC | Открыть окно, нажать ESC. Должен выполниться cleanup. | ✅ |
| 21 | Старта → закрыть окно [X] | Закрыть окно кнопкой [X]. cleanup должен быть тем же, что и на ESC. | ✅ |
| 22 | Выбор/изменение объекта → ESC | Выбрать объект, покрутить/подвигать/поменять scale, затем ESC/выход — без утечек. | ✅ |
| 23 | Выбор/изменение объекта → [X] | То же самое, но выйти через [X]. | ✅ |

---

## Категория 6 — Длительная работа и “drip” утечки

| # | Сценарий | Что сделать / ожидаемое поведение | Статус |
| -- | ------- | --------------------------------- | ------ |
| 24 | Долгая сессия | Запустить под Valgrind, держать окно несколько минут, выбирать объекты, двигать/крутить/скейлить. Затем выйти (ESC или [X]). Утечки в цикле должны проявиться. | ✅ |
| 25 | Стресс-тест быстрыми действиями | Быстро выбирать объекты мышью и совершать много трансформаций + выход. Найти редкие ветки утечек. | ✅ |

---

## Лицензия

Учебный проект (42). Если хочешь — добавлю `LICENSE` (MIT/Apache-2.0 и т.д.).

---

## Где хранить скриншоты/рендеры (для галереи)

Рекомендуемая структура:

```text
docs/
  gallery/
    showcase-1.png
    showcase-2.png
    showcase-3.png
```

Вставка в README:

```markdown
![showcase-1](docs/gallery/showcase-1.png)
```