#pragma once

#include <mutex>
#include <queue>
#include <string>
#include "pscore/common/macros.h"

namespace pscore {

//! The task queue standard interfaces.
template <typename TaskT>
class TaskQueue {
 public:
  virtual size_t size() const = 0;
  virtual bool empty() const  = 0;

  virtual bool Push(TaskT&& task) = 0;

  virtual bool Pop() = 0;

  virtual TaskT& front()             = 0;
  virtual const TaskT& front() const = 0;
};

//! Queue with priority considered.
template <typename TaskT>
class OrderedTaskQueue : public TaskQueue<TaskT> {
 public:
  size_t size() const override { return queue_.size(); }
  bool empty() const override { return queue_.empty(); }

 protected:
  std::priority_queue<TaskT> queue_;
};

//! Threadsafe ordered queue.
template <typename TaskT>
class ThreadsafeOrderedTaskQueue : public OrderedTaskQueue<TaskT> {
 public:
  bool Push(TaskT&& task) override {
    std::unique_lock<std::mutex> lock(mu_);
    this->queue_.push(std::move(task));
    return true;
  }

  bool Pop() override {
    std::unique_lock<std::mutex> lock(mu_);
    if (this->empty()) return false;
    this->queue_.pop();
    return true;
  }

  TaskT& front() override {
    std::unique_lock<std::mutex> lock(mu_);
    CHECK(!this->empty());
    return this->queue_.front();
  }

  const TaskT& front() const override {
    std::unique_lock<std::mutex> lock(mu_);
    CHECK(!this->empty());
    return this->queue_.front();
  }

 private:
  std::mutex mu_;
};

}  // namespace pscore
