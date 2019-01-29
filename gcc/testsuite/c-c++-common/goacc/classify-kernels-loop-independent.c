/* Check offloaded function's attributes and classification for OpenACC
   'kernels loop independent'.  */

/* { dg-additional-options "-O2" }
   { dg-additional-options "-fdump-tree-ompexp" }
   { TODOdg-additional-options "-fdump-tree-parloops1-all" }
   { dg-additional-options "-fdump-tree-oaccdevlow" } */

#define N 1024

extern unsigned int *__restrict a;
extern unsigned int *__restrict b;
extern unsigned int *__restrict c;

extern unsigned int f (unsigned int);
#pragma acc routine (f) seq

void KERNELS ()
{
#pragma acc kernels loop independent copyin (a[0:N], b[0:N]) copyout (c[0:N])
  for (unsigned int i = 0; i < N; i++)
    /* Because of the 'independent' clause, an "extern"al mapping of loop
       iterations/array indices doesn't make the loop unparallelizable.  */
    c[i] = a[f (i)] + b[f (i)];
}

//TODO
/* Check the offloaded function's attributes.
   { dg-final { scan-tree-dump-times "(?n)__attribute__\\(\\(oacc kernels, omp target entrypoint\\)\\)" 1 "ompexp" { xfail *-*-* } } } */

//TODO
/* Check that exactly one OpenACC kernels construct is analyzed, and that it
   can be parallelized.
   { TODOdg-final { scan-tree-dump-times "SUCCESS: may be parallelized" 1 "parloops1" { xfail *-*-* } } }
   { TODOdg-final { scan-tree-dump-times "(?n)__attribute__\\(\\(oacc kernels parallelized, oacc function \\(, , \\), oacc kernels, omp target entrypoint\\)\\)" 1 "parloops1" { xfail *-*-* } } }
   { TODOdg-final { scan-tree-dump-not "FAILED:" "parloops1" { xfail *-*-* } } } */

/* Check the offloaded function's classification and compute dimensions (will
   always be 1 x 1 x 1 for non-offloading compilation).
   { dg-final { scan-tree-dump-times "(?n)Function is parallelized OpenACC kernels offload" 1 "oaccdevlow" { xfail *-*-* } } }
   { dg-final { scan-tree-dump-times "(?n)Compute dimensions \\\[1, 1, 1\\\]" 1 "oaccdevlow" } }
   { dg-final { scan-tree-dump-times "(?n)__attribute__\\(\\(oacc function \\(1, 1, 1\\), oacc kernels parallelized, oacc function \\(, , \\), oacc kernels, omp target entrypoint\\)\\)" 1 "oaccdevlow" { xfail *-*-* } } } */
