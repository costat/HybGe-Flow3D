/* porenetwork permeability functions source */

// hgf includes
#include "model_porenetwork.hpp"

#include <random>

// 1d->2d index
#define idx2(i, j, ldi) ((i * ldi) + j)

/** \brief hgf::models::uniform_porenetwork::init_permeability_one sets permeability to 1 for all throats.
 *
 * @param[in] par - parameters struct containing problem information.
 */
void
hgf::models::uniform_porenetwork::init_permeability_one(const parameters& par)
{
  permeability.assign(pressure.size() * par.dimension * 2, 0.0);
  for (int ii = 0; ii < pressure.size(); ii++) {
    for (int jj = 0; jj < (par.dimension * 2); jj++) {
      if (pressure[ii].neighbors[jj] != -1) {
        permeability[idx2(ii, jj, (par.dimension * 2))] = 1.0;
      }
    }
  }
}

/** \brief hgf::models::uniform_porenetwork::init_permeability_one draws from a uniform distribution to set the permeability in each throat.
 *
 * @param[in] par - parameters struct containing problem information.
 * @param[in] min - lower bound on range for permeability in each throat.
 * @param[in] max - upper bound on range for permeability in each throat.
 */
void 
hgf::models::uniform_porenetwork::init_permeability_random(const parameters& par, double min, double max)
{
  permeability.assign(pressure.size() * par.dimension * 2, 0.0);
  std::uniform_real_distribution<double> unif(min, max);
  std::default_random_engine re;

  for (int ii = 0; ii < pressure.size(); ii++) {
    for (int jj = 0; jj < (par.dimension * 2); jj++) {
      if (pressure[ii].neighbors[jj] != -1) {
        permeability[idx2(ii, jj, (par.dimension * 2))] = unif(re);
      }
    }
  }
}
