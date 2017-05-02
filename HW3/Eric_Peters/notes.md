HW3 Eric Peters

Before running either of the example programs
I ran make streams in petsc in order to find
the optimal number of processors to run on

the results are as follows
------------------------------------------------
np  speedup
1 1.0
2 1.76
3 1.45
4 0.82
5 0.74
6 0.75
7 0.76
8 0.75
Estimation of possible speedup of MPI programs based on Streams benchmark.
It appears you have 1 node(s)

It is clear to see that using 2 processors yields the optimal speed up.

Now for the two example problems

First lets look at the lid driven cavity overall times for the different
KSP types and pc types for different grid refinements and number
of processors

lidvelcoity = 0.01 for all sims to be consistent

GMRES and BJacobi 1 proc
ra_define 5    1.00    sec
ra_define 6    15.4    sec

Spends a lot of time in KSPSolve, VecMAXPY, and KSPGMRESOrthog
177 and 713 iterations for newton convergence on ra_define 6

GMRES and  ASM 1 proc
ra_define 5    1.09    sec
ra_define 6    16.46   sec

Spends a lot of time in MatMult, VecMAXPY, and PCApply
177 and 713 iterations for newton convergence on ra_define 6 ? same?

GMRES and MG 1 proc
ra_define 5    3.21e-1 sec
ra_define 6    1.42    sec                 this is fast!

Spends a lot of time in MATSOR, KSPSOLVE, and PCAPPLY
6 and 7 iterations for newton convergence on ra_define 6  , this is quick

GMRES and GAMG 1 proc
ra_define 5    2.67 sec
ra_define 6    36.58 sec                   this is slow!

Spends a lot of time in KSPSolve, VecMAXPY, and KSPGMRESOrthog
60 and 296 iterations for newton convergence on ra_define 6, converges
relatively fast but is expensive

Run these same sims with 2 procs

Comments
     gmres with gamg is 10 times faster
     gmres with mg is 2 times as fast
     gmres with asm is 2 times as fast
     gmres with bjacobi is 1.5 times as fast

     need to test gamg with more processors seems to work well for this problem
     with gmres

Conjugate Gradient and BJacobi 1 proc
ra_define 5     did not converge
ra_define 6     did not converge

Conjugate Gradient and asm 1 proc
ra_define 5     did not converge
ra_define 6     did not converge

Conjugate Gradient and asm 1 proc
ra_define 5     did not converge
ra_define 6     did not converge

Conjugate Gradient and mg 1 proc
ra_define 5     did not converge
ra_define 6     did not converge

Conjugate Gradient and gamg 1 proc
ra_define 5     did not converge
ra_define 6     did not converge

It seems that for this particular problem, because of the convection term the
system is not symmetric so conjugate gradient will not work, so no need to check
with parallel.

So for problem 1 gmres is the way to go with an mg or gamg preconditioner

Second lets look at the hydrdostatic ice sheet flow, (SPD!!)

GMRES and BJacobi 1 proc
ra_define 3   4.36e-1  sec
ra_define 4   5.22     sec
An average of 50 iterations per linear solve

GMRES and asm 1 proc
ra_define 3   4.54e-1  sec
ra_define 4   5.46     sec
An average of 50 iterations per linear solve, same ??

GMRES and mg 1 proc
ra_define 3        sec
ra_define 4        sec

GMRES and gamg 1 proc
ra_define 3    no object
ra_define 4    no object

GMRES performs okay but I believe CG wil work better because of the SPD nature
of the problem

Run same sims with 2 processors

Comments
     gmres bjacobi 1.2 times faster
     same for gmres and asm
     there seems to take more iterations per linear solve with more processors

CG and bjacobi
ra_define 3    4.25e-1 sec
ra_define 4    4.63    sec
An average of 45 iterations per linear solve

Run same sims with 2 processors

Comments
     CG with bjacobi seems to run 2 times as fast

All in all from ex19 gmres with a mg pre conditioner seems like a good choice, and
for ex48 CG with a bjacobi pre conditioner seems to work best.

Now lets scale up larger by using the Janus super computing resource!
If we run make streams we get the following speed ups
------------------------------------------------
np  speedup
1 1.0
2 1.33
3 1.64
4 1.63
5 1.67
6 2.81
7 1.94
8 1.6
9 2.47
10 2.6
11 3.92
12 2.72
13 3.8
14 3.78
15 4.17
16 3.28
17 4.34
18 4.19
19 4.65
20 3.81
21 2.94
22 2.46
23 2.15
24 2.33

Estimation of possible speedup of MPI programs based on Streams benchmark.
It appears you have 2 node(s)

So once again for probelm 1 I used gmres with the mg preconditioner and got the
following results
srun --mpi=pmi2 ./ex19 -log_view -ksp_type gmres -pc_type mg -da_refine 6
-ksp_converged_reason -lidvelocity 0.01

GMRES and MG 1 proc
ra_define 6    2.36    sec   

with the same amount of iterations per linear solve 6 & 7

This is quick but a little slower than my computer on one processor.  There seems
to be a little more overhead when using the supercomputer, which we should see
diminish as we scale up.

For problem two the following results were obtained
srun --mpi=pmi2 ./ex48 -log_view -ksp_type cg -pc_type bjacobi -da_refine 4 -ksp_converged_reason

CG and bjacobi
ra_define 4    6.92    sec
An average of 45 iterations per linear solve

Once again, this is quick but a little slower than my computer on one processor.

So lets scale up
Unfortunately problem one can't be scaled to far because of memeory
limitations of janus nodes, I can only refine up to level 9.  But in order
to make the problem more difficult we can ramp up the lid velocity.

Now lets run
srun --mpi=pmi2 ./ex19 -log_view -ksp_type gmres -pc_type mg -da_refine 9
-ksp_converged_reason -lidvelocity 1000.00

with 3 processors
I predict this should take around 5-10 minutes to run.

It actually took 10.67 minutes so this is actually a pretty good prediction

if we ran with
srun --mpi=pmi2 ./ex19 -log_view -ksp_type gmres -pc_type asm -da_refine 9
-ksp_converged_reason -lidvelocity 1000.00

we should get a much slower time because of the effect of the preconditioner

Now for problem 2
we can run

srun --mpi=pmi2 ./ex48 -log_view -ksp_type cg -pc_type bjacobi -da_refine 6 -ksp_converged_reason

or

srun --mpi=pmi2 ./ex48 -log_view -ksp_type gmres -pc_type bjacobi -da_refine 6 -ksp_converged_reason

with 12 processors

with cg and bjacobi I predict a 5 to 10 minute run time
with gmres and bjacobi I predict 10 to 15 minute run time

The result for cg and bjacobi actually is 4.16 minutes, so a little faster than
predicted

The result for gmres bjacobi actually is 10.46, so it is confirmed to be slower
for the reasons stated earlier.

A problem like this would take forever to solve on a common laptop.
