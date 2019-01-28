! { dg-additional-options "-O2" }
! { dg-additional-options "-fopenacc-convert-kernels" }
! { dg-additional-options "-fdump-tree-convert_oacc_kernels" }

program main
  implicit none
  integer, parameter         :: N = 1024
  integer, dimension (1:N)   :: a
  integer                    :: i, sum

  !$acc kernels copyin(a(1:N)) copy(sum)

  !$acc loop
  do i = 1, N
    sum = sum + a(i)
  end do

  sum = sum + 1
  a(1) = a(1) + 1

  !$acc loop
  do i = 1, N
    sum = sum + a(i)
  end do

  !$acc end kernels
end program main

! Check that the kernels region is split into a data region and enclosed
! parallel regions.
! { dg-final { scan-tree-dump-times "oacc_data" 1 "convert_oacc_kernels" } }

! The two loop regions are parallelized, the sequential part in between is
! made gang-single.
! { dg-final { scan-tree-dump-times "oacc_parallel_kernels_parallelized" 2 "convert_oacc_kernels" } }
! { dg-final { scan-tree-dump-times "oacc_parallel_kernels_gang_single" 1 "convert_oacc_kernels" } }

! Check that the original kernels region is removed.
! { dg-final { scan-tree-dump-not "oacc_kernels" "convert_oacc_kernels" } }
