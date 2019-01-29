/* Test the output of "-fopt-info-optimized-omp" for OpenACC 'parallel'
   constructs.  */

/* { dg-additional-options "-fopt-info-optimized-omp" } */

//TODO update accordingly
/* See also "../../gfortran.dg/goacc/note-parallelism.f90".  */

int
main ()
{
  int x, y, z;

#pragma acc parallel
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop seq /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop gang /* { dg-message "note: assigned OpenACC gang loop parallelism" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop worker /* { dg-message "note: assigned OpenACC worker loop parallelism" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop vector /* { dg-message "note: assigned OpenACC vector loop parallelism" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop gang vector /* { dg-message "note: assigned OpenACC gang vector loop parallelism" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop gang worker /* { dg-message "note: assigned OpenACC gang worker loop parallelism" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop worker vector /* { dg-message "note: assigned OpenACC worker vector loop parallelism" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop gang worker vector /* { dg-message "note: assigned OpenACC gang worker vector loop parallelism" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop gang /* { dg-message "note: assigned OpenACC gang loop parallelism" } */
  for (x = 0; x < 10; x++)
#pragma acc loop worker /* { dg-message "note: assigned OpenACC worker loop parallelism" } */
    for (y = 0; y < 10; y++)
#pragma acc loop vector /* { dg-message "note: assigned OpenACC vector loop parallelism" } */
      for (z = 0; z < 10; z++)
	;

#pragma acc parallel loop /* { dg-message "note: assigned OpenACC gang vector loop parallelism" } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc parallel loop /* { dg-message "note: assigned OpenACC gang worker loop parallelism" } */
  for (x = 0; x < 10; x++)
#pragma acc loop /* { dg-message "note: assigned OpenACC vector loop parallelism" } */
    for (y = 0; y < 10; y++)
      ;

#pragma acc parallel loop /* { dg-message "note: assigned OpenACC gang loop parallelism" } */
  for (x = 0; x < 10; x++)
#pragma acc loop /* { dg-message "note: assigned OpenACC worker loop parallelism" } */
    for (y = 0; y < 10; y++)
#pragma acc loop /* { dg-message "note: assigned OpenACC vector loop parallelism" } */
      for (z = 0; z < 10; z++)
	;

#pragma acc parallel
  for (x = 0; x < 10; x++)
#pragma acc loop /* { dg-message "note: assigned OpenACC gang worker loop parallelism" } */
    for (y = 0; y < 10; y++)
#pragma acc loop /* { dg-message "note: assigned OpenACC vector loop parallelism" } */
      for (z = 0; z < 10; z++)
	;

#pragma acc parallel loop seq /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  for (x = 0; x < 10; x++)
#pragma acc loop /* { dg-message "note: assigned OpenACC gang worker loop parallelism" } */
    for (y = 0; y < 10; y++)
#pragma acc loop /* { dg-message "note: assigned OpenACC vector loop parallelism" } */
      for (z = 0; z < 10; z++)
	;

#pragma acc parallel loop /* { dg-message "note: assigned OpenACC gang worker loop parallelism" } */
  for (x = 0; x < 10; x++)
#pragma acc loop seq /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
    for (y = 0; y < 10; y++)
#pragma acc loop /* { dg-message "note: assigned OpenACC vector loop parallelism" } */
      for (z = 0; z < 10; z++)
	;

#pragma acc parallel loop /* { dg-message "note: assigned OpenACC gang worker loop parallelism" } */
  for (x = 0; x < 10; x++)
#pragma acc loop /* { dg-message "note: assigned OpenACC vector loop parallelism" } */
    for (y = 0; y < 10; y++)
#pragma acc loop seq /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
      for (z = 0; z < 10; z++)
	;

#pragma acc parallel loop seq /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  for (x = 0; x < 10; x++)
#pragma acc loop /* { dg-message "note: assigned OpenACC gang vector loop parallelism" } */
    for (y = 0; y < 10; y++)
#pragma acc loop seq /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
      for (z = 0; z < 10; z++)
	;

  return 0;
}
