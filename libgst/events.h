/******************************** -*- C -*- ****************************
 *
 *	Header file for asynchronous events
 *
 *
 ***********************************************************************/

/***********************************************************************
 *
 * Copyright 2001, 2002, 2006, 2008, 2009 Free Software Foundation, Inc.
 * Written by Paolo Bonzini.
 *
 * This file is part of GNU Smalltalk.
 *
 * GNU Smalltalk is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later
 * version.
 *
 * Linking GNU Smalltalk statically or dynamically with other modules is
 * making a combined work based on GNU Smalltalk.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * In addition, as a special exception, the Free Software Foundation
 * give you permission to combine GNU Smalltalk with free software
 * programs or libraries that are released under the GNU LGPL and with
 * independent programs running under the GNU Smalltalk virtual machine.
 *
 * You may copy and distribute such a system following the terms of the
 * GNU GPL for GNU Smalltalk and the licenses of the other code
 * concerned, provided that you include the source code of that other
 * code when and as the GNU GPL requires distribution of source code.
 *
 * Note that people who make modified versions of GNU Smalltalk are not
 * obligated to grant this special exception for their modified
 * versions; it is their choice whether to do so.  The GNU General
 * Public License gives permission to release a modified version without
 * this exception; this exception also makes it possible to release a
 * modified version which carries forward this exception.
 *
 * GNU Smalltalk is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * GNU Smalltalk; see the file COPYING.	 If not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 ***********************************************************************/

#ifndef GST_EVENTS_H
#define GST_EVENTS_H

/* Array of semaphores associated to the C signals.  */
extern volatile OOP _gst_sem_int_vec[NSIG]
  ATTRIBUTE_HIDDEN;

/* Initialize the interface to the glib main loop.  */
extern void _gst_init_async_events (void) 
  ATTRIBUTE_HIDDEN;

/* Arrange so that when the SIG signal arrives from the operating
   system, SEMAPHOREOOP is signaled by the virtual machine.  A
   previous wait for the same signal, if any, are discarded.  */
extern void _gst_async_interrupt_wait (OOP semaphoreOOP,
				       int sig) 
  ATTRIBUTE_HIDDEN;


/* Arrange so that after DELAY milliseconds SEMAPHOREOOP is signaled
   by the virtual machine. Previous waits are discarded.  */
extern void _gst_async_timed_wait (OOP semaphoreOOP,
				   int delay) 
  ATTRIBUTE_HIDDEN;

/* Answer whether a timeout has been scheduled and a semaphore was
   passed to the virtual machine, to be signaled when the timer
   fires.  */
extern mst_Boolean _gst_is_timeout_programmed (void)
  ATTRIBUTE_PURE 
  ATTRIBUTE_HIDDEN;

/* Initialize the socket for asynchronous event notifications for the
   kind of socket given by PASSIVE.  */
extern void _gst_register_socket (int fd)
  ATTRIBUTE_HIDDEN;

/* Check whether I/O is possible on the FD file descriptor; COND is 0
   to check for pending input, 1 to check for the possibility of doing
   non-blocking output, 2 to check for pending exceptional situations
   (such as out-of-band data).  Answer -1 if there is an error (including
   POLLHUP -- in that case errno is left to 0), 0 if I/O is impossible,
   1 if possible.  */
extern int _gst_sync_file_polling (int fd,
				   int cond) 
  ATTRIBUTE_HIDDEN;

/* Check whether I/O is possible on the FD file descriptor; COND is 0
   to check for pending input, 1 to check for the possibility of doing
   non-blocking output, 2 to check for pending exceptional situations
   (such as out-of-band data).  Answer -1 if there is an error (including
   POLLHUP -- in that case errno is left to 0), 0 if I/O is impossible,
   1 if possible.  If 0 is answered, the virtual machine arranges things
   so that when the given condition is true SEMAPHOREOOP is signaled.

   Note: due to lack of support from many kernels, waiting for a
   semaphore to be signaled when *output* is possible is risky and
   known to works for sockets only.  */
extern void _gst_async_file_polling (int fd,
				     int cond,
				     OOP semaphoreOOP) 
  ATTRIBUTE_HIDDEN;

extern void _gst_main_context_iterate (void)
  ATTRIBUTE_HIDDEN;

/* Pause until an event is received or USEC milliseconds have passed.  */
extern void _gst_pause (int usec)
  ATTRIBUTE_HIDDEN;

/* Wake up from a pause.  */
extern void _gst_wakeup (void)
  ATTRIBUTE_HIDDEN;

/* System call wrappers that talk to GIOChannels.  */
extern mst_Boolean _gst_is_pipe (int fd)
  ATTRIBUTE_HIDDEN;

extern ssize_t _gst_read (int fd,
			gchar *buf,
			gsize count)
  ATTRIBUTE_HIDDEN;

extern gint _gst_close (int fd)
  ATTRIBUTE_HIDDEN;

extern ssize_t _gst_pwrite (int fd,
			   gchar *buf,
			   gsize count,
			   off_t offset)
  ATTRIBUTE_HIDDEN;

extern ssize_t _gst_pread (int fd,
			  gchar *buf,
			  gsize count,
			  off_t offset)
  ATTRIBUTE_HIDDEN;

extern off_t _gst_lseek (int fd,
       			 off_t offset,
			 GSeekType type)
  ATTRIBUTE_HIDDEN;

extern ssize_t _gst_write (int fd,
			 gchar *buf,
			 gsize count)
  ATTRIBUTE_HIDDEN;

#endif /* GST_EVENTS_H */
