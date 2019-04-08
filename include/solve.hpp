/* solvers header */
#ifndef _SOLVE_H
#define _SOLVE_H

#include "hgflow.hpp"

#include <vector>

namespace hgf
{
    /** \brief Contains solvers.
     * 
     */
    namespace solve
    {
        void init_solver(void);
        void finalize_solver(void);
        void solve(const parameters& par, \
            const std::vector< array_coo >& array, \
            const std::vector< double >& rhs, \
            std::vector<double>& solution);
        void solve_ps_flow(const parameters& par, \
            const std::vector< array_coo >& array, \
            const std::vector< double >& rhs, \
            std::vector<double>& solution, \
            int n_u, int n_v, int n_w, int n_p);
    }
}

#endif
