#pragma once

#include <qabstractitemmodel.h>
#include <qdatetime.h>
#include <qmetatype.h>
#include <qstring.h>

#include "today/common.h"

enum class TODAY_PUBLIC TodoTaskStatus
{
  InProgress,
  Done
};

enum class TODAY_PUBLIC TodoTaskPriority
{
  Low,
  Medium,
  High
};

struct TODAY_PUBLIC TodoTask
{
  constexpr static int INVALID_ID = -1;
  constexpr static TodoTask* INVALID_TASK = nullptr;

  using ConstPtr = const TodoTask*;
  using Ptr = TodoTask*;

  int id;
  QString name;
  QString description;

  QDateTime start;
  QDateTime end;

  TodoTaskStatus status{ TodoTaskStatus::InProgress };
  TodoTaskPriority priority{ TodoTaskPriority::Medium };

  int parent_id{ INVALID_ID };

  static bool is_valid(TodoTask::ConstPtr task);
  static bool is_valid(TodoTask::Ptr task);

  static ConstPtr from_index(const QModelIndex& index);
  static Ptr from_index_mut(const QModelIndex& index);
};

Q_DECLARE_METATYPE(TodoTaskStatus)
Q_DECLARE_METATYPE(TodoTaskPriority)
Q_DECLARE_METATYPE(TodoTask)
