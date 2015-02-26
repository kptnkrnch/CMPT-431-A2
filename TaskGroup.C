// Penn Parallel Primitives Library
// Author: Prof. Milo Martin
// University of Pennsylvania
// Spring 2010

#include "ppp.h"
#include "TaskGroup.h"

namespace ppp {

  namespace internal {
    // Task-based scheduling variables
    TaskQueue* g_queues_ptr = NULL;
    atomic<int> g_stop_counter;  
  }

  using namespace internal;

  void TaskGroup::spawn(Task& t) {
    assert(g_queues_ptr != NULL);
    TaskQueue& queue = g_queues_ptr[ppp::get_thread_id()];  // ASSIGNMENT: use per-thread task queue with "get_thread_id()"
    m_wait_counter.fetch_and_inc();
    t.setCounter(&m_wait_counter);
    queue.enqueue(&t);
  }
  
  void process_tasks(const atomic<int>* counter)
  {
    TaskQueue& queue = g_queues_ptr[ppp::get_thread_id()];  // ASSIGNMENT: use per-thread task queue with "get_thread_id()"

    while (counter->get() != 0) {
      PPP_DEBUG_EXPR(queue.size());
       
      // Dequeue from local queue
      Task* task = queue.dequeue();
      // ASSIGNMENT: add task stealing

      if (task != NULL) {
        task->execute(); // overloaded method
        task->post_execute(); // cleanup, method of base class
      } else {
      	int id = ppp::get_thread_id() + 1;
      	for (int n = 0; n < ppp::get_thread_count() - 1; n++) {
      		if (id >= ppp::get_thread_count()) {
      			id = 0;
      		}
      		TaskQueue& temp = g_queues_ptr[id];
      		task = temp.steal();
      		if (task != NULL) {
				task->execute(); // overloaded method
				task->post_execute(); // cleanup, method of base class
				break;
		  	}
		  	id++;
      	}
      }
    }
  }
}

