/* { dg-additional-options "-O2" } */
/* { dg-additional-options "-fdump-tree-convert_oacc_kernels" } */

#define N 1024

unsigned int a[N];

int
main (void)
{
  int i;
  unsigned int sum = 1;

#pragma acc kernels copyin(a[0:N]) copy(sum)
  {
    #pragma acc loop
    for (i = 0; i < N; ++i)
      sum += a[i];

    sum++;
    a[0]++;

    #pragma acc loop
    for (i = 0; i < N; ++i)
      sum += a[i];

    if (sum > 10)
      { 
        #pragma acc loop
        for (i = 0; i < N; ++i)
          sum += a[i];
      }

    #pragma acc loop
    for (i = 0; i < N; ++i)
      sum += a[i];
  }

  return 0;
}

/* Check that the kernels region is split into a data region and enclosed
   parallel regions.  */ 
/* { dg-final { scan-tree-dump-times "oacc_data" 1 "convert_oacc_kernels" } } */

/* The three unconditional loop regions are parallelized, the sequential
   part in between and the conditional loop are made gang-single.  */
/* { dg-final { scan-tree-dump-times "oacc_parallel_kernels_parallelized" 3 "convert_oacc_kernels" } } */
/* { dg-final { scan-tree-dump-times "oacc_parallel_kernels_gang_single" 2 "convert_oacc_kernels" } } */

/* Each of the parallel regions is async, and there is a final call to
   __builtin_GOACC_wait.  */
/* { dg-final { scan-tree-dump-times "oacc_parallel_kernels.* async\(-1\)" 5 "convert_oacc_kernels" } */
/* { dg-final { scan-tree-dump-times "__builtin_GOACC_wait" 1 "convert_oacc_kernels" } */

/* Check that the original kernels region is removed.  */
/* { dg-final { scan-tree-dump-not "oacc_kernels" "convert_oacc_kernels" } } */
