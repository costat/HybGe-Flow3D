# HybGe-Flow3D #

HybGe-Flow3D is a library designed for solving multiscale fluid flow problems in complex, uncertain 3D and 2D geometries.

This software is maintained by Numerical Solutions, Inc.

The first version of this software was developed under the partial support of the National Science
Foundation on the projects NSF DMS-1115827 "Hybrid modeling in porous media" (PI: M. Peszynska)
and NFS DMS-1522734 "Phase transitions in porous media across multiple scales" (PI: M. Peszynska).

### Documentation ###

Please find detailed documentation at www.numericalsolutions.org/doc/hybge-flow3d

### License ###

HybGe-Flow3D Copyright (C) Numerical Solutions, Inc.

This program is free software; you can redistribute and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This software is distributed AS IS and
WITHOUT ANY WARRANTY.

A copy of the GNU General Public License is included in the source and
can also be found at http://www.gnu.org/licenses/.

### Citation ###

Publications making use of HybGe-Flow3D should cite this software package. An example citation is given as:

    Costa, T., "HybGe-Flow3D", Package Version 3.0.0,
    http://github.com/numsol/HybGe-Flow3D.

### Contact ###

Timothy B. Costa, timothy.costa@numericalsolutions.org

### Contributors ###
 
- Timothy B. Costa
- Anthony B. Costa
- Joe Umhoefer

### Change Log ###

Version 3.0.0 (Beta)
- New model: Poisson equation.
    - Model solves the Poisson equation with a tensor alpha coefficient using a cell-centered Finite Volume discretiziation.
        - Beta version requires a diagonal tensor. This will be extended prior to release of 3.0.0.
    - Includes tools for setting force and alpha coefficient.
    - Ships with tools to set Dirichlet or mixed Dirichlet/Neumann boundary conditions.
- Added controls to inflow boundary conditions in Stokes Model. 
    - Allows user to control constant or parabolic inflow, as well as the value of the inflow condition. 
    - Requires API change in directional flow boundary condition functions.

Version 2.3.1
- Stokes model unnecessary divides removed.
- 2D Mesh bug fixed. Bug only affected visualization for some geometries.

Version 2.3.0
- Add new function hgf::models::stokes::write_geometry.
    - Writes a geometry file to the problem folder. Useful for saving geometries with generated immersed boundaries.
- Add new function hgf::mesh::refine_voxel_uniform.
    - Performs a uniform mesh refinement of an input voxel geometry according to input refine length integer, refine_len.
    - int refine_len = 2 subdivides each cell into 2x2 = 4 cells in 2d and 2x2x2 = 8 cells in 3d.
    - Output is an updated voxel geometry vector in the parameters struct. This function should be used after reading a parameters file and before meshing. 

Version 2.2.0
- Add new function hgf::models::stokes::check_divergence.
    - Calculates divergence of Stokes solution on each cell and places value in info input vector. If requested, prints divergence to vtk file for visualization.
- Bug in outflow boundary condition in Stokes model fixed.
- Viscosity removed from parameters struct and placed as variable in Stokes class.
    - hgf::models::stokes::build initializes viscosity to 1.0.
    - Examples updated to reflect this change.
- Vector that tracks immersed boundary is now initialized to the length of the pressure vector during build. 

Version 2.1.0
- Add linear solver controls to parameters struct. Requires Parameters.dat file include:
    - solver_max_iterations
    - solver_absolute_tolerance
    - solver_relative_tolerance
    - solver_verbose
 - Add function hgf::models::stokes::write_state.
    - Writes to file (name argument appended with '.dat') the state of the Stokes system, storing all degree of freedom coordinates and values.
 - Correct upscaled permeability functions to account for presence of an immersed boundary. Requires API change to include pressure_ib_list argument in functions:
    - hgf::multiscale::flow::compute_permeability_x
    - hgf::multiscale::flow::compute_permeability_y
    - hgf::multiscale::flow::compute_permeability_z
    - hgf::multiscale::flow::compute_permeability_tensor
 - Example geometries given descriptive names.
 - Add example geometry 'immersed_circles_2d' identical to voxel_quadrilaterals but with geometry entirely enforced via immersed boundary.
