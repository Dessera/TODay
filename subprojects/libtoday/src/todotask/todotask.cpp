#include "today/todotask/todotask.h"

bool
TodoTask::is_valid(TodoTask::ConstPtr task)
{
  return task != TodoTask::INVALID_TASK && task->id != TodoTask::INVALID_ID;
}

bool
TodoTask::is_valid(TodoTask::Ptr task)
{
  return is_valid(static_cast<TodoTask::ConstPtr>(task));
}

TodoTask::ConstPtr
TodoTask::from_index(const QModelIndex& index)
{
  if (!index.isValid()) {
    return TodoTask::INVALID_TASK;
  }

  return static_cast<TodoTask::ConstPtr>(index.internalPointer());
}

TodoTask::Ptr
TodoTask::from_index_mut(const QModelIndex& index)
{
  if (!index.isValid()) {
    return TodoTask::INVALID_TASK;
  }

  return static_cast<TodoTask::Ptr>(index.internalPointer());
}