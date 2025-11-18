#ifndef CONSTANTS_H
# define CONSTANTS_H

#  ifndef M_PI
#   define M_PI 3.14159265358979323846
#  endif

#  ifndef RT_EPS
#   define RT_EPS 1e-9
#  endif

# ifndef RT_MIN_OBJECT_EXTENT
#  define RT_MIN_OBJECT_EXTENT 1e-6
# endif

# ifndef K_TMIN_PRIMARY
#  define K_TMIN_PRIMARY 1e-6
# endif

# ifndef K_TMAX_PRIMARY
#  define K_TMAX_PRIMARY 1e6
# endif

# ifndef K_SKY_BLEND_BIAS
#  define K_SKY_BLEND_BIAS 0.5
# endif

# ifndef K_SHADOW_BIAS
#  define K_SHADOW_BIAS 1e-4
# endif

# ifndef KeyEscape
# define KeyEscape 65307
# endif

// Optional convenient movement keys (X11 KeySyms)
# ifndef KeyLeft
# define KeyLeft 65361
# endif
# ifndef KeyUp
# define KeyUp 65362
# endif
# ifndef KeyRight
# define KeyRight 65363
# endif
# ifndef KeyDown
# define KeyDown 65364
# endif
# ifndef KeyPageUp
# define KeyPageUp 65365
# endif
# ifndef KeyPageDown
# define KeyPageDown 65366
# endif

// WASDQE for 3D translation
# ifndef KeyW
# define KeyW 119
# endif
# ifndef KeyA
# define KeyA 97
# endif
# ifndef KeyS
# define KeyS 115
# endif
# ifndef KeyD
# define KeyD 100
# endif
# ifndef KeyQ
# define KeyQ 113
# endif
# ifndef KeyE
# define KeyE 101
# endif

// Rotations: I/K around X, J/L around Y, U/O around Z
# ifndef KeyI
# define KeyI 105
# endif
# ifndef KeyK
# define KeyK 107
# endif
# ifndef KeyJ
# define KeyJ 106
# endif
# ifndef KeyL
# define KeyL 108
# endif
# ifndef KeyU
# define KeyU 117
# endif
# ifndef KeyO
# define KeyO 111
# endif

// Transform steps
# ifndef MOVE_STEP
# define MOVE_STEP 0.25
# endif
# ifndef ROTATE_STEP_DEG
# define ROTATE_STEP_DEG 5.0
# endif
# ifndef SCALE_STEP
# define SCALE_STEP 1.05
# endif

# endif