#pragma once

#define SEED 1337

#define HASH __LINE__

#define INLINE_STATE (HASH + SEED)

#define COND ((INLINE_STATE % 2) == 0)

#define FORCEINLINE __forceinline
#define NOINLINE __declspec(noinline)
