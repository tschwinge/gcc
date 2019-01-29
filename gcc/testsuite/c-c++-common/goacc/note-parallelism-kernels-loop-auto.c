/* Test the output of "-fopt-info-optimized-omp" for OpenACC 'kernels'
   constructs containing 'loop' constructs with explicit or implicit 'auto'
   clause.  */

/* { dg-additional-options "-fopt-info-optimized-omp" } */

//TODO update accordingly
/* See also "../../gfortran.dg/goacc/note-parallelism.f90".  */

int
main ()
{
  int x, y, z;

#pragma acc kernels
#pragma acc loop /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc kernels
#pragma acc loop auto gang /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc kernels
#pragma acc loop auto worker /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc kernels
#pragma acc loop auto vector /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc kernels
#pragma acc loop auto gang vector /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc kernels
#pragma acc loop auto gang worker /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc kernels
#pragma acc loop auto worker vector /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc kernels
#pragma acc loop auto gang worker vector /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc kernels
#pragma acc loop auto gang /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
#pragma acc loop auto worker
    for (y = 0; y < 10; y++)
#pragma acc loop auto vector
      for (z = 0; z < 10; z++)
	;

#pragma acc kernels
#pragma acc loop auto /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
    ;

#pragma acc kernels
#pragma acc loop auto /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
#pragma acc loop auto
    for (y = 0; y < 10; y++)
      ;

#pragma acc kernels
#pragma acc loop auto /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
#pragma acc loop auto
    for (y = 0; y < 10; y++)
#pragma acc loop auto
      for (z = 0; z < 10; z++)
	;

#pragma acc kernels
#pragma acc loop /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
#pragma acc loop auto
    for (y = 0; y < 10; y++)
#pragma acc loop auto
      for (z = 0; z < 10; z++)
	;

#pragma acc kernels
#pragma acc loop auto /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
#pragma acc loop
    for (y = 0; y < 10; y++)
#pragma acc loop auto
      for (z = 0; z < 10; z++)
	;

#pragma acc kernels
#pragma acc loop auto /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
#pragma acc loop auto
    for (y = 0; y < 10; y++)
#pragma acc loop
      for (z = 0; z < 10; z++)
	;

#pragma acc kernels
#pragma acc loop /* { dg-message "note: assigned OpenACC seq loop parallelism" } */
  /* { dg-message "note: forwarded loop nest in OpenACC .kernels. construct to .parloops. for analysis" "" { target *-*-* } .-1 } */
  for (x = 0; x < 10; x++)
#pragma acc loop auto
    for (y = 0; y < 10; y++)
#pragma acc loop
      for (z = 0; z < 10; z++)
	;

  return 0;
}
