/* Header file for gimple iterators.
   Copyright (C) 2013-2025 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef GCC_GIMPLE_ITERATOR_H
#define GCC_GIMPLE_ITERATOR_H

/* Iterator object for GIMPLE statement sequences.  */

struct gimple_stmt_iterator
{
  gimple *operator * () const { return ptr; }

  /* Sequence node holding the current statement.  */
  gimple_seq_node ptr;

  /* Sequence and basic block holding the statement.  These fields
     are necessary to handle edge cases such as when statement is
     added to an empty basic block or when the last statement of a
     block/sequence is removed.  */
  gimple_seq *seq;
  basic_block bb;
};

/* Iterator over GIMPLE_PHI statements.  */
struct gphi_iterator : public gimple_stmt_iterator
{
  gphi *operator * () const { return as_a <gphi *> (ptr); }

  gphi *phi () const
  {
    return as_a <gphi *> (ptr);
  }
};

enum gsi_iterator_update
{
  GSI_NEW_STMT = 2,	/* Move the iterator to the first statement added.  */
  GSI_LAST_NEW_STMT,	/* Move the iterator to the last statement added.  */
  GSI_SAME_STMT,	/* Leave the iterator at the same statement.  */
  GSI_CONTINUE_LINKING	/* Move iterator to whatever position is suitable
			   for linking other statements in the same
			   direction.  */
};

extern void gsi_insert_seq_before_without_update (gimple_stmt_iterator *,
						  gimple_seq,
						  enum gsi_iterator_update);
extern void gsi_insert_seq_before (gimple_stmt_iterator *, gimple_seq,
				   enum gsi_iterator_update);
extern void gsi_insert_seq_after_without_update (gimple_stmt_iterator *,
						 gimple_seq,
						 enum gsi_iterator_update);
extern void gsi_insert_seq_after (gimple_stmt_iterator *, gimple_seq,
				  enum gsi_iterator_update);
extern gimple_seq gsi_split_seq_after (gimple_stmt_iterator);
extern void gsi_set_stmt (gimple_stmt_iterator *, gimple *);
extern void gsi_split_seq_before (gimple_stmt_iterator *, gimple_seq *);
extern bool gsi_replace (gimple_stmt_iterator *, gimple *, bool);
extern void gsi_replace_with_seq (gimple_stmt_iterator *, gimple_seq, bool);
extern void gsi_insert_before_without_update (gimple_stmt_iterator *, gimple *,
					      enum gsi_iterator_update);
extern void gsi_insert_before (gimple_stmt_iterator *, gimple *,
			       enum gsi_iterator_update);
extern void gsi_insert_after_without_update (gimple_stmt_iterator *, gimple *,
					     enum gsi_iterator_update);
extern void gsi_insert_after (gimple_stmt_iterator *, gimple *,
			      enum gsi_iterator_update);
extern bool gsi_remove (gimple_stmt_iterator *, bool);
extern gimple_stmt_iterator gsi_for_stmt (gimple *);
extern gimple_stmt_iterator gsi_for_stmt (gimple *, gimple_seq *);
extern gphi_iterator gsi_for_phi (gphi *);
extern void gsi_move_after (gimple_stmt_iterator *, gimple_stmt_iterator *);
extern void gsi_move_before (gimple_stmt_iterator *, gimple_stmt_iterator *,
			     gsi_iterator_update = GSI_SAME_STMT);
extern void gsi_move_to_bb_end (gimple_stmt_iterator *, basic_block);
extern void gsi_insert_on_edge (edge, gimple *);
extern void gsi_insert_seq_on_edge (edge, gimple_seq);
extern basic_block gsi_insert_on_edge_immediate (edge, gimple *);
extern basic_block gsi_insert_seq_on_edge_immediate (edge, gimple_seq);
extern void gsi_safe_insert_before (gimple_stmt_iterator *, gimple *);
extern void gsi_safe_insert_seq_before (gimple_stmt_iterator *, gimple_seq);
extern void gsi_commit_edge_inserts (void);
extern void gsi_commit_one_edge_insert (edge, basic_block *);
extern gphi_iterator gsi_start_phis (basic_block);
extern void update_modified_stmts (gimple_seq);

/* Return a new iterator pointing to GIMPLE_SEQ's first statement.  */

inline gimple_stmt_iterator
gsi_start (gimple_seq &seq)
{
  gimple_stmt_iterator i;

  i.ptr = gimple_seq_first (seq);
  i.seq = &seq;
  i.bb = i.ptr ? gimple_bb (i.ptr) : NULL;

  return i;
}

inline gimple_stmt_iterator
gsi_none (void)
{
  gimple_stmt_iterator i;
  i.ptr = NULL;
  i.seq = NULL;
  i.bb = NULL;
  return i;
}

/* Return a new iterator pointing to the first statement in basic block BB.  */

inline gimple_stmt_iterator
gsi_start_bb (basic_block bb)
{
  gimple_stmt_iterator i;
  gimple_seq *seq;

  seq = bb_seq_addr (bb);
  i.ptr = gimple_seq_first (*seq);
  i.seq = seq;
  i.bb = bb;

  return i;
}

gimple_stmt_iterator gsi_start_edge (edge e);

/* Return a new iterator initially pointing to GIMPLE_SEQ's last statement.  */

inline gimple_stmt_iterator
gsi_last (gimple_seq &seq)
{
  gimple_stmt_iterator i;

  i.ptr = gimple_seq_last (seq);
  i.seq = &seq;
  i.bb = i.ptr ? gimple_bb (i.ptr) : NULL;

  return i;
}

/* Return a new iterator pointing to the last statement in basic block BB.  */

inline gimple_stmt_iterator
gsi_last_bb (basic_block bb)
{
  gimple_stmt_iterator i;
  gimple_seq *seq;

  seq = bb_seq_addr (bb);
  i.ptr = gimple_seq_last (*seq);
  i.seq = seq;
  i.bb = bb;

  return i;
}

/* Return a new iterator pointing to before the first statement or after
   last statement (depending on whether adding statements after it or before it)
   in a GIMPLE_SEQ.  */

inline gimple_stmt_iterator
gsi_end (gimple_seq &seq)
{
  gimple_stmt_iterator i;
  gimple *g = gimple_seq_last (seq);

  i.ptr = NULL;
  i.seq = &seq;
  i.bb = g ? gimple_bb (g) : NULL;

  return i;
}

/* Return a new iterator pointing to before the first statement or after
   last statement (depending on whether adding statements after it or before it)
   in basic block BB.  */

inline gimple_stmt_iterator
gsi_end_bb (basic_block bb)
{
  gimple_stmt_iterator i;
  gimple_seq *seq;

  seq = bb_seq_addr (bb);
  i.ptr = NULL;
  i.seq = seq;
  i.bb = bb;

  return i;
}

/* Return true if I is at the end of its sequence.  */

inline bool
gsi_end_p (gimple_stmt_iterator i)
{
  return i.ptr == NULL;
}

/* Return true if I is one statement before the end of its sequence.  */

inline bool
gsi_one_before_end_p (gimple_stmt_iterator i)
{
  return i.ptr != NULL && i.ptr->next == NULL;
}

/* Advance the iterator to the next gimple statement.  */

inline void
gsi_next (gimple_stmt_iterator *i)
{
  i->ptr = i->ptr->next;
}

/* Advance the iterator to the previous gimple statement.  */

inline void
gsi_prev (gimple_stmt_iterator *i)
{
  gimple *prev = i->ptr->prev;
  if (prev->next)
    i->ptr = prev;
  else
    i->ptr = NULL;
}

/* Return the current stmt.  */

inline gimple *
gsi_stmt (gimple_stmt_iterator i)
{
  return i.ptr;
}

/* Return a block statement iterator that points to the first
   non-label statement in block BB.  */

inline gimple_stmt_iterator
gsi_after_labels (basic_block bb)
{
  gimple_stmt_iterator gsi = gsi_start_bb (bb);

  for (; !gsi_end_p (gsi); )
    {
      if (gimple_code (gsi_stmt (gsi)) == GIMPLE_LABEL)
	gsi_next (&gsi);
      else
	break;
    }

  return gsi;
}

/* Return a statement iterator that points to the first
   non-label statement in sequence SEQ.  */

inline gimple_stmt_iterator
gsi_after_labels (gimple_seq &seq)
{
  gimple_stmt_iterator gsi = gsi_start (seq);

  for (; !gsi_end_p (gsi); )
    {
      if (gimple_code (gsi_stmt (gsi)) == GIMPLE_LABEL)
	gsi_next (&gsi);
      else
	break;
    }

  return gsi;
}

/* Advance the iterator to the next non-debug gimple statement.  */

inline void
gsi_next_nondebug (gimple_stmt_iterator *i)
{
  do
    {
      gsi_next (i);
    }
  while (!gsi_end_p (*i) && is_gimple_debug (gsi_stmt (*i)));
}

/* Advance the iterator to the previous non-debug gimple statement.  */

inline void
gsi_prev_nondebug (gimple_stmt_iterator *i)
{
  do
    {
      gsi_prev (i);
    }
  while (!gsi_end_p (*i) && is_gimple_debug (gsi_stmt (*i)));
}

/* Return a new iterator pointing to the first non-debug statement in
   SEQ.  */

inline gimple_stmt_iterator
gsi_start_nondebug (gimple_seq seq)
{
  gimple_stmt_iterator gsi = gsi_start (seq);
  if (!gsi_end_p (gsi) && is_gimple_debug (gsi_stmt (gsi)))
    gsi_next_nondebug (&gsi);

  return gsi;
}

/* Return a new iterator pointing to the first non-debug statement in
   basic block BB.  */

inline gimple_stmt_iterator
gsi_start_nondebug_bb (basic_block bb)
{
  gimple_stmt_iterator i = gsi_start_bb (bb);

  if (!gsi_end_p (i) && is_gimple_debug (gsi_stmt (i)))
    gsi_next_nondebug (&i);

  return i;
}

/* Return a new iterator pointing to the first non-debug non-label statement in
   basic block BB.  */

inline gimple_stmt_iterator
gsi_start_nondebug_after_labels_bb (basic_block bb)
{
  gimple_stmt_iterator i = gsi_after_labels (bb);

  if (!gsi_end_p (i) && is_gimple_debug (gsi_stmt (i)))
    gsi_next_nondebug (&i);

  return i;
}

/* Return a new iterator pointing to the last non-debug statement in
   basic block BB.  */

inline gimple_stmt_iterator
gsi_last_nondebug_bb (basic_block bb)
{
  gimple_stmt_iterator i = gsi_last_bb (bb);

  if (!gsi_end_p (i) && is_gimple_debug (gsi_stmt (i)))
    gsi_prev_nondebug (&i);

  return i;
}

/* Return true if I is followed only by debug statements in its
   sequence.  */

inline bool
gsi_one_nondebug_before_end_p (gimple_stmt_iterator i)
{
  if (gsi_one_before_end_p (i))
    return true;
  if (gsi_end_p (i))
    return false;
  gsi_next_nondebug (&i);
  return gsi_end_p (i);
}

/* Advance I statement iterator to the next non-virtual GIMPLE_PHI
   statement.  */

inline void
gsi_next_nonvirtual_phi (gphi_iterator *i)
{
  do
    {
      gsi_next (i);
    }
  while (!gsi_end_p (*i) && virtual_operand_p (gimple_phi_result (i->phi ())));
}

/* Return a new iterator pointing to the first non-virtual phi statement in
   basic block BB.  */

inline gphi_iterator
gsi_start_nonvirtual_phis (basic_block bb)
{
  gphi_iterator i = gsi_start_phis (bb);

  if (!gsi_end_p (i) && virtual_operand_p (gimple_phi_result (i.phi ())))
    gsi_next_nonvirtual_phi (&i);

  return i;
}

/* Return the basic block associated with this iterator.  */

inline basic_block
gsi_bb (gimple_stmt_iterator i)
{
  return i.bb;
}

/* Return the sequence associated with this iterator.  */

inline gimple_seq
gsi_seq (gimple_stmt_iterator i)
{
  return *i.seq;
}

/* Determine whether SEQ is a nondebug singleton.  */

inline bool
gimple_seq_nondebug_singleton_p (gimple_seq seq)
{
  gimple_stmt_iterator gsi = gsi_start_nondebug (seq);

  return gsi_one_nondebug_before_end_p (gsi);
}

#endif /* GCC_GIMPLE_ITERATOR_H */
