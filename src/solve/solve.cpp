#include "solve.hpp"

// 1d->2d index
#define idx2(i, j, ldi) ((i * ldi) + j)

#if defined(_HGF_USE_PARALUTION_)
#include "paralution/solve_paralution.cxx"
#elif defined(_HGF_USE_AMGX_)
#include "amgx/solve_amgx.cxx"
#else 
#include "solve_native.cxx"
#endif

