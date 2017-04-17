In this document we want to assess the performance of different Krylov methods and preconditioners when solving two problems in PETSc:
1. ex19: 2D steady-state thermo/lid-driven cavity with finite difference, and
2. ex48: 3D hydrostatic ice flow using finite elements. Note discrete problem SPD, thus can use CG, and want preconditions that maintain symmetry.

For all the problems, we consider that the linear solver is nxn, where n is the degrees of freedom in the numerical PDE mesh.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Problem 1 (ex19) 
We consider GMRES preconditioned with LU and GMRES preconditioned with MG. Based on the literature, GMRES has a cost of 2n^2, LU factorization has a const of (2/3)n^3+2n^2. Since A is a sparse matrix, these costs are larger than anticipated. MG has a cost of O(n). I would predict that we improve the cost by at least an order of n. So for GMRES+LU we will see about O(n^2) and for GMRES+MG we will see about O(n).
%%%%%%%%%%%%%%
1a. GMRES with LU
%%%%%%%%%%%%%%
i) Workstation: First note, that while I have access to 4 processors, the scaling is poor. Based on the make streams function we get:
np  speedup
1 1.0
2 1.09
3 1.18
4 1.12

which does little to improve the solve time (based on testing). The dominating costs for GMRES+LU are MatLUFactorNum, PCSetup, and KSPSolve. After testing on 1 processor with da_refine between 1 and 4, it seems that the FLOPs grow between O(n) and O(n^2) (see hw3_plot_19a, lower left). Using a growth of n^(3/2) for the time (green dashed line), I would predict that a single processor could solve an n=1e6 dofs problem in 5 minutes (300 s). Based on the da_refine this puts us somewhere between da_refine= 8 (n=2e6) and da_refine 7 (n=6e5). When testing da_refine=8 it took 10.6 minutes. The lower refinement, da_refine=7 took about 1 minute.
%%%%%%%%%%%%%%
ii) Summit: On summit we have access to 12 processors, and using make streams, we have :
np  speedup1 1.02 1.813 2.664 3.485 4.36 4.957 5.978 6.569 6.3510 6.1611 7.7312 8.29

The goal now is to predict what problem size we can solve in about 5-10 minutes. First we want to calibrate performance between the workstation (1 processor) and Summit (1 processor), then based on the speed up, we should be able to estimate how large n can be. 

On Summit, I ran with 1 processor to figure out time time scaling compared to the workstation. Based on that, I would predict that we can solve a problem size of n=1.616e6 in 5 minutes. Since 12 processors have a speed up of 8x, 5 minutes on one processor would be equivalent to 40 minutes. Extrapolating based on n^3/2 (see hw3_plot_19a, lower right), I would predict that n=5e6 (between da_refine 8 and da_refine 9) can be run within 5-10 minutes on 12 processors. Using da_refine 9, this took 8.037e+02 seconds (13 minutes), and just to check that this wasn’t an over estimate, da_refine 8 took almost 2 minutes.
%%%%%%%%%%%%%%
1b. GMRES with MG
%%%%%%%%%%%%%%
i)Workstation:  The dominating costs for GMRES+MG are MatSOR (relaxation sweeps), KSPSolve, MatMult and PCApply. Since we are working with a sparse matrix, I would imagine the cost to scale as O(n). After testing on processor with da_refine between 1 and 4, it seems that the FLOPs grow a O(n) (see hw3_plot_19b). Using a growth of n (see dashed green line), I would predict a single processor could solve an n=2e7 problem in 5 minutes. Based on the da_refine this puts us somewhere between da_refine= 9 (n=9e6) and da_refine 10 (n=3.7e7). Using da_refine= 9 it takes longer than predicted - more like 30-40 minutes. This likely indicates that for larger problems, the time is growing at a faster rate than predicted.
%%%%%%%%%%%%%%
ii) Summit:
Again, the goal now is to predict what problem size we can solve in about 5-10 minutes. 

On Summit, I ran with 1 processor to figure out time time scaling compared to the workstation. Based on that, I would predict that we can solve a problem size of n=3e7 in 5 minutes. For 12 processors, I predict a problem size that runs for 40 minutes on 1 processor, that is n=2e8. I would predict running between da_refine 10 (n=3.7e7) and da_refine 11 (n=?) would take about 5 minutes. Running da_refine 10 takes about 3 minutes.  With da_refine 11 we run out of memory. 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Problem 2 (ex48) 
We consider CG preconditioned with block Jacobi and preconditioned with additive Schwartz (**with overlap). Note that without overlap, these two methods will be equivalent. Also, due to the domain decompositions, and my lack of multiple well performing processors, I am going to do my initial tests on Summit, only with 1-4 processors. Even though we wish to look first at a personal computer configuration, I think this is the best option for comparing, as the performance is dependent on the number of blocks. While I am able to set the number of blocks with a single processor, I think it would be difficult to gauge this type of performance; and with multiple processors, it automatically does 1 block per processor.

In terms of performance, the cost of CG will scale as the number of non zeros. I would predict similar complexity for the two methods, but a better error for additive Schwartz with overlap. Due to this, I would predict that CG preconditioned with additive Schwartz with overlap=1 will perform slightly faster for larger problems than CG preconditioned with block Jacobi.
%%%%%%%%%%%%%%
2a. CG+ Block Jacobi
%%%%%%%%%%%%%%
The dominating cost of this method is from MatSolve, PCApply, and KSPSetup. As the problem sizes increase, MatMult and VecAXPY join the list. The leading cost of CG is the number of non zeros. For the testing we consider the time and flops performance of using 2 processors (see hw3_plot_48a). When using 3 and 4 processors, we get speedup (as expected), but the costs still scale the same, and the data points are difficult to discern in log-scale. Extrapolating based on a growth of the number of nonzeros, we would predict that we could complete a n= 1.6e7 problem with 12 processors. Since da_refine 6 is n=4.8e6, this will take about 3 minutes (with testing, takes 2 minutes). This means using da_refine 7 (which I am guessing is about n=3e7…which is correct in hindsight) is the alternative option; however, based on extrapolation, this will take about 30 minutes. (…50 minutes later it finishes) On a positive note, I was able to correctly match the n values to the time for da_refine 6.
%%%%%%%%%%%%%%
2b. CG+ additive Schwartz with overlap=2,5
%%%%%%%%%%%%%%
The dominating cost of this method is from MatSolve, PCApply, as well as VectorScatterBegin, VectorScatterEnd, VecNorm, and VecTDot. From what I gather, it seems that large VectorScatterBegin and VectorScatterEnd correspond to the overlap.

For comparison, would like to see how additive Schwartz with overlap performs. While the overlap may help improve the convergence for cost reduction, it will likely add a cost regarding communication. I would expect the cost to grow as O(n), but I also imagine there is a cost related to the number of subdomains - I have it set such that for P processors, there will be P subdomains, 1 for each processor. Based on initial testing the costs for smaller number of processors, it seems that the cost grows like O(n); however, for 12 processors, the cost doesn’t really follow the O(n) line (see hw3_plot_48b). On plot ‘hw3_plot_19b’ we do see that having a larger overlap slows down the solve time - and this becomes more apparent as the number of processors increases. This makes sense as more communication is required when the number of subdomains are increased, which is what occurs as the number of processors increases. 

Based on these results, it seems that this method is performing worse than CG preconditioned with block Jacobi. Due to this, I would predict that for 12 processors, setting da_refine 6 would result in around a 5 minute solve time. When testing this, I find that for overlap = 2 it takes 3.274e+02 seconds and for overlap=5 it takes 3.705e+02 seconds. 

For this problem (ex48) it seems that with CG using block Jacobi performs better than additive Schwartz with overlap.









