! Check offloaded function's attributes and classification for OpenACC
! 'kernels loop independent'.

! { dg-additional-options "-O2" }
! { dg-additional-options "-fdump-tree-ompexp" }
! { TODOdg-additional-options "-fdump-tree-parloops1-all" }
! { dg-additional-options "-fdump-tree-oaccdevlow" }

program main
  implicit none
  integer, parameter :: n = 1024
  integer, dimension (0:n-1) :: a, b, c
  integer :: i

  integer, external :: f
  !$acc routine (f) seq

  call setup(a, b)

  !$acc kernels loop independent copyin (a(0:n-1), b(0:n-1)) copyout (c(0:n-1))
  do i = 0, n - 1
     ! Because of the 'independent' clause, an "external" mapping of loop
     ! iterations/array indices doesn't make the loop unparallelizable.
     c(i) = a(f (i)) + b(f (i))
  end do
  !$acc end kernels loop
end program main

!TODO
! Check the offloaded function's attributes.
! { dg-final { scan-tree-dump-times "(?n)__attribute__\\(\\(oacc kernels, omp target entrypoint\\)\\)" 1 "ompexp" { xfail *-*-* } } }

!TODO
! Check that exactly one OpenACC kernels construct is analyzed, and that it
! can be parallelized.
! { TODOdg-final { scan-tree-dump-times "SUCCESS: may be parallelized" 1 "parloops1" { xfail *-*-* } } }
! { TODOdg-final { scan-tree-dump-times "(?n)__attribute__\\(\\(oacc kernels parallelized, oacc function \\(, , \\), oacc kernels, omp target entrypoint\\)\\)" 1 "parloops1" { xfail *-*-* } } }
! { TODOdg-final { scan-tree-dump-not "FAILED:" "parloops1" { xfail *-*-* } } }

! Check the offloaded function's classification and compute dimensions (will
! always be 1 x 1 x 1 for non-offloading compilation).
! { dg-final { scan-tree-dump-times "(?n)Function is parallelized OpenACC kernels offload" 1 "oaccdevlow" { xfail *-*-* } } }
! { dg-final { scan-tree-dump-times "(?n)Compute dimensions \\\[1, 1, 1\\\]" 1 "oaccdevlow" } }
! { dg-final { scan-tree-dump-times "(?n)__attribute__\\(\\(oacc function \\(1, 1, 1\\), oacc kernels parallelized, oacc function \\(, , \\), oacc kernels, omp target entrypoint\\)\\)" 1 "oaccdevlow" { xfail *-*-* } } }
