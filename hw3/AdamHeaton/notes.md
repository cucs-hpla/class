Adam Heaton  
Homework #3  
HPLA

## Part 1

#### ex19:

1.  -ksp_type: GMRES -pc_type: ASM
	* Problem Size: 			500 x 500
	* SNES itterations: 		2
	* Linear Solver itterations:	6
	* Logs:				Dominated by VecCopy, VecSet, VecAXPY

2.  -ksp_type: GMRES -pc_type: MG
	* Problem Size: 			500 x 500
	* SNES itterations: 		2
	* Linear Solver itterations:	7
	* Logs:				Not really dominated by any one operation

3. -ksp_type: Chebyshev -pc_type: MG
	* Problem Size: 			1000 x 1000
	* SNES itterations: 		2
	* Linear Solver itterations:	39, and 44
	* Logs:				Dominated by MatMult, VecNorm, VecPointwiseMult

4. -ksp_type: GCR -pc_type: jacobi
	* Problem Size: 			1000 x 1000
	* SNES itterations: 		2
	* Linear Solver itterations:	14
	* Logs:				Dominated by VecAXPY, and other vec arithmetic

5. -ksp_type: GCR -pc_type: MG
	* Problem Size: 			1000 x 1000
	* SNES itterations: 		2
	* Linear Solver itterations:	6, and 7
	* Logs:				Dominated by VecSet, and other vec arithmetic

#### ex48:

1. -ksp_type: GCR -pc_type: MG
	* Problem Size: 			200 x 200
	* SNES itterations: 		7
	* Linear Solver itterations:	44, and 45
	* Logs:				Dominated by VecAYPX, vec arithemtic, MatMult, MatSQR

2. -ksp_type: GCR -pc_type: bjacobi
	* Problem Size: 			200 x 200
	* SNES itterations: 		7
	* Linear Solver itterations:	94, 95
	* Logs:				Dominated by VexAXPY, VecMAXPY, VecScale

3. -ksp_type: GMRES -pc_type: MG
	* Problem Size: 			200 x 200
	* SNES itterations: 		7
	* Linear Solver itterations:	43, and 44
	* Logs:				Dominated by VecAYPX, vec arithemtic, MatMult, MatSQR
 
4. -ksp_type: GMRES -pc_type: ASM
	* Problem Size: 			200 x 200
	* SNES itterations: 		7
	* Linear Solver itterations:	94, and 95
	* Logs:				Dominated by VecScatterBegin, VecSet

## Part2

I experimented with different problem sizes, preconditioners, krylov methods, and examing the log outputs from execution. From the results it seems that using a Multi-Grid preconditioner with the Generalized Conjugate Residual method works well, especially since a lot of the operaitons are spread over many methods or involve low cost ones like VecSet.

I ran experiment 48 on the summit cluster with this configuration:

`./ex48 -pc_type mg -ksp_type gcr -ksp_monitor -ksp_converged_reason -m 200 -n 200 -log_view`  
`./ex19 -pc_type mg -ksp_type gcr -ksp_monitor -ksp_converged_reason -m 200 -n 200 -log_view`

And varied the dimesnions of the matrix in order to find a suitable problem size that would finish in 5-10 minutes. This turned out to be:
1. ex19
* m = 100,000
* n = 100,000

2. ex48
* m = 10,000
* n = 10,000
