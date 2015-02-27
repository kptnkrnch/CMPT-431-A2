// Penn Parallel Primitives Library
// Author: Prof. Milo Martin
// University of Pennsylvania
// Spring 2010

#ifndef PPP_FOR_H
#define PPP_FOR_H

#include "ppp.h"
#include "Task.h"
#include "TaskGroup.h"

namespace ppp {
  namespace internal {
	  template <typename T>
	  class PForTask: public ppp::Task {
	  public:
	  	PForTask(int64_t _start, int64_t _end, T* _functor, int64_t _grainsize) {
	  		start = _start;
	  		end = _end;
	  		functor = _functor;
	  		grainsize = _grainsize;
	  	}
	  	
	  	void execute() {
	  		assert(start < end);
	
			if (end - start <= 1) {
				return;
			}
	
			if (end - start < grainsize) {
				functor->calculate(start, end);
				return;
			}
	
			int64_t pivot = (((end - start) / 2) + start);
			assert(pivot < end);
		
			ppp::TaskGroup tg;
			
			PForTask t1(start, pivot, functor, grainsize);
			PForTask t2(pivot, end, functor, grainsize);
			tg.spawn(t1);
			tg.spawn(t2);
			tg.wait();
	  	}
	  	
	  	private:
	  		int64_t start;
	  		int64_t end;
	  		T* functor;
	  		int64_t grainsize;
	  };
  }
  
  template <typename T>
  extern inline
  void parallel_for(int64_t start, int64_t end, T* functor, int64_t grainsize=0)
  {
    // ASSIGNMENT: make this parallel via recursive divide and conquer
	if (grainsize == 0) {
		grainsize = (end - start + 1) / (get_thread_count() * 4);
	}
	internal::PForTask<T> t(start, end, functor, grainsize);
	t.execute();
  }
}

#endif
