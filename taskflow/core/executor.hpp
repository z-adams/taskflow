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
using the inherited task scheduler.

*/
class Executor : public TaskScheduler
{
  public:
    explicit Executor(size_t N = std::thread::hardware_concurrency());

    ~Executor();

    void _spawn(size_t N);
  private:
    std::vector<std::thread> _threads;
};

// Constructor
inline Executor::Executor(size_t N) : TaskScheduler() {

  if (N == 0) {
    TF_THROW("no cpu workers to execute taskflows");
  }
  _spawn(N);
}

inline Executor::~Executor() {

  for (auto& t : _threads) {
    t.join();
  }
}


// Procedure: _spawn
inline void Executor::_spawn(size_t N) {

  _threads.resize(N);
  for (size_t id = 0; id < N; ++id)
  {
    std::shared_ptr<Worker> worker = _register_worker(&_threads[id]);
    _threads[id] = std::thread([this](std::shared_ptr<Worker> w) -> void
        {
            execute_tasks(*w);
        }, worker);
  }
}

}  // end of namespace tf -----------------------------------------------------
