#pragma once

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

  int id;
  QString name;
  QString description;

  QDateTime start;
  QDateTime end;

  TodoTaskStatus status{ TodoTaskStatus::InProgress };
  TodoTaskPriority priority{ TodoTaskPriority::Medium };

  int parent_id{ INVALID_ID };
};

Q_DECLARE_METATYPE(TodoTaskStatus)
Q_DECLARE_METATYPE(TodoTaskPriority)
Q_DECLARE_METATYPE(TodoTask)
