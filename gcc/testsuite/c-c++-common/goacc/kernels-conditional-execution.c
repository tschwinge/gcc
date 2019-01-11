/* Check that conditionally executed loops in OpenACC kernels loops are
   diagnosed correctly. */

extern int flag, count;

void
kernels_conditionally_executed_loops (void)
{
#pragma acc kernels
  {
#pragma acc loop gang(num: 3)
    for (int i = 0; i < 10; i++)
      ;

    if (flag) {
#pragma acc loop gang(num: 3) /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    } else if (count > 7) {
#pragma acc loop gang(num: 3) /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    } else {
#pragma acc loop gang(num: 3) /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    }

    while (count-- > 10) {
#pragma acc loop gang(num: 3) /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    }

    do {
#pragma acc loop gang(num: 3) /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    } while (count++ < 100);

    /* This is a non-OpenACC outer loop. */
    for (int j = 0; j < 10; j++)
#pragma acc loop gang(num: 3) /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;

    switch (count)
    {
      case 42:
#pragma acc loop gang(num: 3) /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
      break;

      default:
      ;
    }

backward_jump_label:
    count--;
#pragma acc loop gang(num: 3) /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
    for (int i = 0; i < 10; i++)
      ;
    if (count == 123)
      goto backward_jump_label;

    if (count == 142)
      goto forward_jump_label;
#pragma acc loop gang(num: 3) /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
    for (int i = 0; i < 10; i++)
      ;
forward_jump_label:
    ;
  }

  /* The same tests as above, but this time the number of gangs is specified
     on the kernels region, not on the loop. */
#pragma acc kernels num_gangs(3)
  {
#pragma acc loop gang
    for (int i = 0; i < 10; i++)
      ;

    if (flag) {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    } else if (count > 7) {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    } else {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    }

    while (count-- > 10) {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    }

    do {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
    } while (count++ < 100);

    /* This is a non-OpenACC outer loop. */
    for (int j = 0; j < 10; j++)
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;

    switch (count)
    {
      case 42:
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
      break;

      default:
      ;
    }

backward_jump_label_2:
    count--;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
    for (int i = 0; i < 10; i++)
      ;
    if (count == 123)
      goto backward_jump_label_2;

    if (count == 142)
      goto forward_jump_label_2;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
    for (int i = 0; i < 10; i++)
      ;
forward_jump_label_2:
    ;
  }

  /* The same tests as above, but this time there are two loops in each
     block instead of just one. */
#pragma acc kernels num_gangs(3)
  {
#pragma acc loop gang
    for (int i = 0; i < 10; i++)
      ;
#pragma acc loop gang
    for (int k = 0; k < 10; k++)
      ;

    if (flag) {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int k = 0; k < 10; k++)
        ;
    } else if (count > 7) {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int k = 0; k < 10; k++)
        ;
    } else {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int k = 0; k < 10; k++)
        ;
    }

    while (count-- > 10) {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int k = 0; k < 10; k++)
        ;
    }

    do {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int k = 0; k < 10; k++)
        ;
    } while (count++ < 100);

    /* This is a non-OpenACC outer loop. */
    for (int j = 0; j < 10; j++) {
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int k = 0; k < 10; k++)
        ;
    }

    switch (count)
    {
      case 42:
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int i = 0; i < 10; i++)
        ;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
      for (int k = 0; k < 10; k++)
        ;
      break;

      default:
      ;
    }

backward_jump_label_3:
    count--;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
    for (int i = 0; i < 10; i++)
      ;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
    for (int k = 0; k < 10; k++)
      ;
    if (count == 123)
      goto backward_jump_label_3;

    if (count == 142)
      goto forward_jump_label_3;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
    for (int i = 0; i < 10; i++)
      ;
#pragma acc loop gang /* { dg-warning "conditionally executed loop in kernels region will be executed in a single gang; ignoring .gang. clause" } */
    for (int k = 0; k < 10; k++)
      ;
forward_jump_label_3:
    ;
  }
}
