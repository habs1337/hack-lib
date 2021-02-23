//module
#include <Windows.h>
#include <cstdint>
#include <winternl.h> 
//#include <iostream>


//mini_crt
#include "inline.h"
#include "string.h"
#include "memory.h"
#include "vector.h"

//hack_lib
#define JM_XORSTR_DISABLE_AVX_INTRINSICS

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "color.h"
#include "math.h"
#include "address.h"
#include "module.h"
#include "xorstr.h"
#include "hook_manager.h"


