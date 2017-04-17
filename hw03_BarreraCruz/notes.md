# High Performance Linear Algebra
# HW-03
# Jorge Luis Barrera Cruz

# Parallel Preconditioned Krylov Methods in PETSc

# --------------------------------------
# --------------------------------------
# on personal computer
# --------------------------------------
# --------------------------------------

# Run streams:
# ------------
Running streams with '/Users/Aizen/tpls/petsc/arch-darwin-c-opt/bin/mpiexec ' using 'NPMAX=8' 
Number of MPI processes 1 Processor names  cocomac 
Triad:        20050.4523   Rate (MB/s) 
Number of MPI processes 2 Processor names  cocomac cocomac 
Triad:        31631.5535   Rate (MB/s) 
Number of MPI processes 3 Processor names  cocomac cocomac cocomac 
Triad:        27368.3105   Rate (MB/s) 
Number of MPI processes 4 Processor names  cocomac cocomac cocomac cocomac 
Triad:        18647.9473   Rate (MB/s) 
Number of MPI processes 5 Processor names  cocomac cocomac cocomac cocomac cocomac 
Triad:        16508.0300   Rate (MB/s) 
Number of MPI processes 6 Processor names  cocomac cocomac cocomac cocomac cocomac cocomac 
Triad:        15815.3798   Rate (MB/s) 
Number of MPI processes 7 Processor names  cocomac cocomac cocomac cocomac cocomac cocomac cocomac 
Triad:        15629.2486   Rate (MB/s) 
Number of MPI processes 8 Processor names  cocomac cocomac cocomac cocomac cocomac cocomac cocomac cocomac 
Triad:        15695.3923   Rate (MB/s) 
------------------------------------------------
np  speedup
1 1.0
2 1.58
3 1.36
4 0.93
5 0.82
6 0.79
7 0.78
8 0.78
Estimation of possible speedup of MPI programs based on Streams benchmark.
It appears you have 1 node(s)
Unable to open matplotlib to plot speedup
Unable to open matplotlib to plot speedup

# Note:
# -----
Shell scripts and matlab subroutines where used to run and postprocess the experiments. 2, 4, and 8 processors where used for meshes of size 50x50, 100x100, and 150x150 for both problems. All mentioned scripts are attached to this hw.

# Run problem ex19
# ----------------  
problem types used: pipefgmres, cg, and bcgsl
preconditioner types used: asm, bjacobi, mg

For this problem pipefgmres and bcgsl had a significantly better performance than cg. The preconditioner chosen for each simulation did not have a big influence on the total time. However, in the plots attached one can see that pipefgmres works slightly better with asm and bcgsl with mg. The convergence for almost all of the problems was CONVERGED_RTOL with the exception of a few cg and bcgsl problems (7 of them) that converged with the CONVERGED_ATOL criterion. A file with the three main dominant operations is attached as well.

# Run problem ex48
# ----------------  
problem types used: pipefgmres, cg, and bcgsl
preconditioner types used: asm, bjacobi, mg

For this problem all 3 problem types (pipefgmres, cg, and bcgsl) have better performance with bjacobi preconditioner. An improvement between 25-50% in computational time can be seen for all methods using the three preconditioner types mentioned above in the attached figures. The convergence for all problems was CONVERGED_RTOL. A file with the three main dominant operations is attached as well.


# --------------------------------------
# --------------------------------------
# on JANUS
# --------------------------------------
# --------------------------------------

[joba0735@login04 petsc]$ make streams NPMAX=20
cd src/benchmarks/streams; /usr/bin/gmake  --no-print-directory PETSC_DIR=/projects/joba0735/hpla/petsc PETSC_ARCH=arch-darwin-c-opt streams
/projects/joba0735/hpla/petsc/arch-darwin-c-opt/bin/mpicc -o MPIVersion.o -c -Wall -Wwrite-strings -Wno-strict-aliasing -Wno-unknown-pragmas -fvisibility=hidden -g -O   -I/projects/joba0735/hpla/petsc/include -I/projects/joba0735/hpla/petsc/arch-darwin-c-opt/include    `pwd`/MPIVersion.c
Running streams with '/projects/joba0735/hpla/petsc/arch-darwin-c-opt/bin/mpiexec ' using 'NPMAX=20' 
Number of MPI processes 1 Processor names  login04 
Triad:         3267.4932   Rate (MB/s) 
Number of MPI processes 2 Processor names  login04 login04 
Triad:         5355.2496   Rate (MB/s) 
Number of MPI processes 3 Processor names  login04 login04 login04 
Triad:         5550.7066   Rate (MB/s) 
Number of MPI processes 4 Processor names  login04 login04 login04 login04 
Triad:         6507.9791   Rate (MB/s) 
Number of MPI processes 5 Processor names  login04 login04 login04 login04 login04 
Triad:         6336.5093   Rate (MB/s) 
Number of MPI processes 6 Processor names  login04 login04 login04 login04 login04 login04 
Triad:         6649.6729   Rate (MB/s) 
Number of MPI processes 7 Processor names  login04 login04 login04 login04 login04 login04 login04 
... (up to 20)

------------------------------------------------
np  speedup
1 1.0
2 1.64
3 1.7
4 1.99
5 1.94
6 2.04
7 2.03
8 2.03
9 1.96
10 2.01
11 1.97
12 2.01 (no significant speedup above 12 processors)
13 2.04
14 2.02
15 2.03
16 2.03
17 2.03
18 2.03
19 2.03
20 2.06
Estimation of possible speedup of MPI programs based on Streams benchmark.
It appears you have 1 node(s)
Unable to open matplotlib to plot speedup
Unable to open matplotlib to plot speedup

# Note:
# -----
Similar shell scripts and matlab subroutines where used to run and postprocess the experiments. Experiments were run using 12 processors and mesh sizes of 400x400 and 250x250 for examples ex19 and ex48, respectively (approximating 5 min for those mesh sizes). All mentioned scripts are attached to this hw.

# Run problem ex19
# ----------------  
problem types used: pipefgmres, and bcgsl (cg was not used due to bad performance in personal machine).
preconditioner types used: asm, bjacobi, mg

In this problem I overestimated the time pipefgmres would take. Overall, the times for pipefgmres with the preconditioners mentioned above are significantly better than the times for bcgsl. There is a difference of more than 300% between the smallest (~1.5 min) and longest (~5.5 min) computation time. The convergence for all problems was CONVERGED_RTOL. A file with the three main dominant operations is attached as well.

# Run problem ex48
# ----------------  
problem types used: pipefgmres, and cg (bcgsl was not used because its performance was not as good as the other 2 in personal machine and time constraints).
preconditioner types used: asm, bjacobi, mg

In this problem I underestimate the time cg would take. Similar to ex19, the times for pipefgmres with the preconditioners mentioned above are significantly better than the times for bcgsl. There is a difference of more than 400% between the smallest (~3 min) and longest (~14 min) computation time. The convergence for all problems was CONVERGED_RTOL. A file with the three main dominant operations is attached as well.

