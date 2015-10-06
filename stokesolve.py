import numpy as np
import time
import sys
import hgf
import re

##############################################################################
### PROBLEM SETUP, USER DEFINES GRID, VISCOSITY, AND NUMBER OF OMP THREADS ###
##############################################################################

# GRID INFORMATION. USER PROVIDES PATH .DAT FILE CONTAINING
# VOXEL ARRAY OF 0S 1S AND 2S.
# ALSO, USER PROVIDES TOTAL GRID LENGTHS IN EACH DIRECTION.
gridfiles = './grids/2dsquare.dat'
L = 1.
W = 1.
H = 1.

# PRINCIPAL FLOW DIRECTION, 0 - X, 1 - Y, 2 - Z, SINGLE FLOW DIRECTION SOLVES,
# PRODUCES CONSTANT K FOR USE IN PORE-NETWORK THROATS
# 3 - ALL DIRECTIONS, PRODUCES UPSCALED K TENSOR
direction = 0;

# SET VISCOSITY
visc = 1

# NUMBER OF OMP THREADS FOR USE IN PARALUTION LINEAR ALGEBRA
nThreads = 4

##########################################################
### SWIG TRANSLATION, USER SHOULD NOT EDIT BELOW HERE ####
##########################################################

gridF = open( gridfiles, 'r' )
gridF.seek(0) # make sure we read the file from the beginning
geoData = gridF.readline() # read the first line containing nx, ny, nz info
gridin1 = np.genfromtxt(gridF, dtype = int) # import the rest as a numpy array
gridF.close()
nxyz = re.findall(r'\d+', geoData)
nx = int(nxyz[0])
ny = int(nxyz[1])
nz = int(nxyz[2])

if nz:
    gridin = np.zeros((nx, ny, nz), dtype = int)
    for zLevel in range(0,nz):
        gridin[:,:,zLevel] = gridin1[zLevel*ny:(zLevel+1)*ny][:]
    gridin_ldi1, gridin_ldi2, gridin_ldi3 = gridin.shape
    gridin = np.array(gridin, dtype = np.uint64).ravel()
elif not nz:
    gridin = np.transpose(gridin1)
    gridin_ldi1, gridin_ldi2 = gridin.shape
    gridin = np.array(gridin, dtype = np.uint64).ravel()
    gridin_ldi3 = 0

gridin_len = gridin.size

totalStart = time.time()
print 'Solving the stationary Stokes problem...\n'

#################
### SWIG CALL ###
#################

hgf.hgfStokesDrive ( gridin, gridin_ldi2, gridin_ldi3, nx, ny, nz, L, W, H, direction, visc, nThreads )

totalStop = time.time()
totalTime = totalStop - totalStart

print 'Done. Total time:', totalTime
