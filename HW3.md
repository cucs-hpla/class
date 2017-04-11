# HW3: Parallel Preconditioned Krylov Methods in PETSc
Due: 2017-04-15

This assignment experiments with preconditioning methods and parallel
performance.  We will work with two examples in PETSc, solved using
Newton methods.

* `src/snes/examples/tutorials/ex19.c` 2D steady-state thermo/lid-driven cavity.  This uses a finite difference discretization and has four degrees of freedom per node.  It is transport-dominated for large `-lidvelocity`.

* `src/snes/examples/tutorials/ex48.c` 3D hydrostatic ice sheet flow.  This uses finite element methods to discretize an elliptic system for momentum balance.  The discrete problem is SPD.

For each problem, I would like you to test solving with at least two choices of Krylov method and preconditioner.

* `-ksp_type` choices include GMRES, BiCGStab, CG, and pipelined variants
* `-pc_type` choices include LU, BJacobi, ASM, MG, GAMG

If using LU in parallel, be sure to configure with a third-party direct solver (e.g., `--download-superlu_dist` or `--download-mumps` or `--download-strumpack`) and run with `-pc_type lu -pc_factor_mat_solver_package superlu_dist`.

## Methods

Make a directory with your name in the `hw3` directory of this project.  E.g., `mkdir hw3/$USER`.  Put a file named `notes.md` there to keep track of your performance predictions and results.

### Experiment

Run tests on your laptop or workstation to find promising configurations.
Run `make streams` to see your machine's memory scalability.
Use `-ksp_monitor` or `-ksp_converged_reason` to understand convergence and `-log_view` to see which operations dominate the cost for each chosen method.
For each of the two problems (`ex19` and `ex48`), you should find at least two solver configurations that seem promising.
Remember to vary problem size and tests parallel cases (even if only with 2-4 processes).

### Calibrate in the batch environment

SSH to `login.rc.colorado.edu` and build PETSc on either Janus (old) or Summit (new, has Xeon Phi nodes).
You will likely need some modules

```
module load intel/17.0.0 cmake
. /curc/sw/intel/17.0.0/compilers_and_libraries/linux/bin/compilervars.sh intel64
cd petsc
```

Feel free to look in `/home/jeka2967/petsc` for a working configuration.
You have to use the batch system to run jobs here -- either as a script or interactive session.
Run `make streams` on a compute node to see memory scalability.
Run at least one of the inexpensive configurations that you ran on your laptop or workstation.

### Predict

Based on the algorithmic and performance scaling that you have seen in the tests above, choose a problem size that you think can be solved in 5-10 minutes using the best method you have available.
Predict the performance of two methods for each problem.

### Test

Use the batch system to submit jobs for each configuration.

## Submit

Submit a pull request to this repository with your `notes.md` and any log files.
