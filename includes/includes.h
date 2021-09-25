//module
#include <Windows.h>
#include <cstdint>
#include <winternl.h> 
#include <heapapi.h>
//#include <iostream>


//mini_crt
#include "inline.h"
#include "string.h"
#include "ret_addr.h"
#include "memory.h"
#include "vector.h"

//hack_lib
#define JM_XORSTR_DISABLE_AVX_INTRINSICS
#define FLT_EPSILON 1.192092896e-07F
#define M_PI 3.14159265358979323846f
#define DO_ONCE(c) static bool do_once = false; if (!do_once) { c do_once = true; } 

#include "matrix4x4.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "color.h"
#include "math.h"
#include "address.h"
#include "module.h"
#include "xorstr.h"
#include "hook_manager.h"
#include "world_to_screen.h"


