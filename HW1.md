# HW1: optimizing dense matrix-matrix multiplication
Due: 2017-02-06

This assignment involves profiling and optimizing implementations of matrix-matrix multiplication.
I suggest using the [Linux perf](https://perf.wiki.kernel.org/index.php/Main_Page) tool, though you are welcome to use other tools.
[Brendan Gregg](http://www.brendangregg.com/perf.html) has good usage documentation.
Some commands you will likely find useful.

* `perf list`
* `perf record -e L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores ./test_MMult.x`
* `perf report`
* `perf record -g`

Perf can give much better information if you compile with debug symbols (`-g` option to gcc/clang/icc).

* Start by forking the repository (https://github.com/cucs-hpla/how-to-optimize-gemm) to your personal account.
* Edit `src/HowToOptimizeGemm/proc_parameters.m` to reflect your machine parameters (check `/proc/cpuinfo` on Linux).
* Edit `src/HowToOptimizeGemm/makefile` to choose implementations to compare and to choose compiler flags.
* Put the results of your analysis in a file called `Analysis.md` (remember to `git add` this file before committing).

## GEMM: GEneral Matrix Multiply

* Compare the number of `instructions` and `cache-misses` for the reference implementation and your choice of optimized implementation.
* Write an implementation (copy an `MMult*.c` file and edit) that calls the `dgemm_` function from an optimized BLAS (e.g., OpenBLAS or a BLAS that is already installed).  You'll need to edit the `makefile` to link `-lblas`.  Depending on your BLAS, you may need to write a prototype.
* Make a plot comparing your favorite implementation to the BLAS implementation.

## SYMM: SYmmetric Matrix Multiply

* Extend the test harness to perform the multiplication `C += A * B` where `A` is symmetric (i.e., `A[i,j] = A[j,i]`).  You may assume that either the upper- or lower-triangular part is significant.
* What is good and bad about this implementation relative to GEMM?
