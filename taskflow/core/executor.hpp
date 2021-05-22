#pragma once

#include "task_scheduler.hpp"

/**
@file executor.hpp
@brief executor include file
*/

namespace tf
{

// ----------------------------------------------------------------------------
// Executor Definition
// ----------------------------------------------------------------------------


/** @class Executor

@brief execution interface for running a taskflow graph

An executor object manages a set of worker threads to run taskflow(s)
using an efficient work-stealing scheduling algorithm.

*/
class Executor : public TaskScheduler
{
  public:
    explicit Executor(size_t N = std::thread::hardware_concurrency());
};

// Constructor
inline Executor::Executor(size_t N) : TaskScheduler(N) {}

}  // end of namespace tf -----------------------------------------------------
