/*!The Treasure Box Library
 * 
 * TBox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * TBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with TBox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2015, ruki All rights reserved.
 *
 * @author		ruki
 * @file		thread_pool.h
 * @ingroup 	platform
 *
 */
#ifndef TB_PLATFORM_THREAD_POOL_H
#define TB_PLATFORM_THREAD_POOL_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

/// the thread pool task done func type
typedef tb_void_t 						(*tb_thread_pool_task_done_func_t)(tb_pointer_t priv);

/// the thread pool task exit func type
typedef tb_void_t 						(*tb_thread_pool_task_exit_func_t)(tb_pointer_t priv);

/// the thread pool task type
typedef struct __tb_thread_pool_task_t
{
	/// the task done func
	tb_thread_pool_task_done_func_t 	done;

	/// the task exit func for freeing the private data
	tb_thread_pool_task_exit_func_t 	exit;

	/// the task private data
	tb_pointer_t 						priv;

	/// is urgent task?
	tb_bool_t 							urgent;

}tb_thread_pool_task_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init thread pool
 *
 * @param worker_maxn 	the thread worker max count
 * @param stack 		the thread stack, using the default stack size if be zero 
 *
 * @return 				the thread pool handle
 */
tb_handle_t 			tb_thread_pool_init(tb_size_t worker_maxn, tb_size_t stack);

/*! exit thread pool
 *
 * @param pool 			the thread pool handle
 */
tb_void_t 				tb_thread_pool_exit(tb_handle_t pool);

/*! kill thread pool, all workers and waiting tasks 
 *
 * @param pool 			the thread pool handle
 */
tb_void_t 				tb_thread_pool_kill(tb_handle_t pool);

/*! the current worker count
 *
 * @param pool 			the thread pool handle
 *
 * @return 				the current worker count
 */
tb_size_t 				tb_thread_pool_worker_size(tb_handle_t pool);

/*! the current waiting task count
 *
 * @param pool 			the thread pool handle
 *
 * @return 				the current task count
 */
tb_size_t 				tb_thread_pool_task_size(tb_handle_t pool);

/*! post one task
 *
 * @param pool 			the thread pool handle
 * @param done 			the task done func
 * @param exit 			the task exit func, optional
 * @param priv 			the task private data
 * @param urgent 		is urgent task?
 *
 * @return 				the task handle
 */
tb_handle_t 			tb_thread_pool_task_post(tb_handle_t pool, tb_thread_pool_task_done_func_t done, tb_thread_pool_task_exit_func_t exit, tb_pointer_t priv, tb_bool_t urgent);

/*! post task list
 *
 * @param pool 			the thread pool handle
 * @param list 			the task list
 * @param size 			the task count
 * @param tasks 		the task handle list, optional
 *
 * @return 				tb_true or tb_false
 */
tb_bool_t 				tb_thread_pool_task_post_list(tb_handle_t pool, tb_thread_pool_task_t const* list, tb_size_t size, tb_handle_t* tasks);

/*! kill one task
 *
 * @param pool 			the thread pool handle
 * @param task 			the task handle
 */
tb_void_t 				tb_thread_pool_task_kill(tb_handle_t pool, tb_handle_t task);

/*! kill task list
 *
 * @param pool 			the thread pool handle
 * @param tasks 		the task handle list
 * @param size 			the task handle count
 */
tb_void_t 				tb_thread_pool_task_kill_list(tb_handle_t pool, tb_handle_t* tasks, tb_size_t size);

/*! kill all tasks
 *
 * @param pool 			the thread pool handle
 */
tb_void_t 				tb_thread_pool_task_kill_all(tb_handle_t pool);

/*! the thread pool instance
 *
 * @param pool 			the thread pool handle
 */
tb_handle_t 			tb_thread_pool_instance(tb_noarg_t);

#ifdef __tb_debug__
/*! dump all workers
 *
 * @param pool 			the thread pool handle
 */
tb_void_t 				tb_thread_pool_worker_dump(tb_handle_t pool);

/*! dump all tasks
 *
 * @param pool 			the thread pool handle
 */
tb_void_t 				tb_thread_pool_task_dump(tb_handle_t pool);
#endif

#endif
