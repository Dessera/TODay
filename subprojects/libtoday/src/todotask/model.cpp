#include "today/todotask/model.h"
#include "qabstractitemmodel.h"
#include "today/todotask/todotask.h"

TodoTaskModel::TodoTaskModel(QList<TodoTask> tasks, QObject* parent)
  : QAbstractItemModel(parent)
  , m_tasks(std::move(tasks))
{
}

TodoTaskModel::~TodoTaskModel() {}

int
TodoTaskModel::rowCount(const QModelIndex& parent) const
{
  auto* parent_task = TodoTaskModel::from_index(parent);
  auto count =
    this
      ->tasks((parent_task != nullptr) ? parent_task->id : TodoTask::INVALID_ID)
      .size();
  return static_cast<int>(count);
}

int
TodoTaskModel::columnCount(const QModelIndex& /*parent*/) const
{
  return 1;
}

QVariant
TodoTaskModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return {};
  }

  auto* task = TodoTaskModel::from_index(index);
  if (task == nullptr) {
    return {};
  }

  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    return task->name;
  }

  return {};
}

QVariant
TodoTaskModel::headerData(int /*section*/,
                          Qt::Orientation orientation,
                          int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return "Task";
  }

  return {};
}

QModelIndex
TodoTaskModel::index(int row, int column, const QModelIndex& parent) const
{
  if (row < 0 || row >= this->rowCount(parent) || column < 0 ||
      column >= this->columnCount(parent)) {
    return {};
  }

  auto* parent_task = TodoTaskModel::from_index(parent);
  auto current_tasks = this->tasks(
    (parent_task != nullptr) ? parent_task->id : TodoTask::INVALID_ID);
  if (row >= current_tasks.size()) {
    return {};
  }
  auto* task = current_tasks.at(row);
  return this->createIndex(row, column, task);
}

QModelIndex
TodoTaskModel::parent(const QModelIndex& index) const
{
  auto* task = TodoTaskModel::from_index(index);
  if (task == nullptr) {
    return {};
  }

  if (task->parent_id == TodoTask::INVALID_ID) {
    return {};
  }

  auto* parent_task = this->get_parent(task);
  if (parent_task == nullptr) {
    return {};
  }

  int v_row = this->row_of_task(task);
  return this->createIndex(v_row, 0, parent_task);
}

QModelIndex
TodoTaskModel::sibling(int row, int column, const QModelIndex& index) const
{
  if (row < 0 || column < 0 || !index.isValid()) {
    return {};
  }

  auto* current_task = TodoTaskModel::from_index(index);
  if (current_task == nullptr) {
    return {};
  }

  auto tasks = this->tasks(current_task->parent_id);
  if (row >= tasks.size()) {
    return {};
  }

  auto* sibling_task = tasks.at(row);
  return this->createIndex(row, column, sibling_task);
}

bool
TodoTaskModel::hasChildren(const QModelIndex& parent) const
{
  auto* parent_task = TodoTaskModel::from_index(parent);
  if (parent_task == nullptr) {
    return true;
  }

  auto tasks = this->tasks(parent_task->id);
  return !tasks.isEmpty();
}

TodoTask*
TodoTaskModel::from_index(const QModelIndex& index)
{
  if (!index.isValid()) {
    return nullptr;
  }

  return static_cast<TodoTask*>(index.internalPointer());
}

TodoTask*
TodoTaskModel::get_parent(TodoTask* task) const
{
  if (task->parent_id == TodoTask::INVALID_ID) {
    return nullptr;
  }

  TodoTask* parent_task = nullptr;
  for (const auto& t : m_tasks) {
    if (t.id == task->parent_id) {
      parent_task = &t;
      break;
    }
  }
  return parent_task;
}

int
TodoTaskModel::row_of_task(TodoTask* task) const
{
  auto tasks = this->tasks(task->parent_id);
  return static_cast<int>(tasks.indexOf(task));
}

QList<TodoTask*>
TodoTaskModel::tasks(int parent_id) const
{
  auto filtered = QList<TodoTask*>{};
  for (auto& task : m_tasks) {
    if (task.parent_id == parent_id) {
      filtered.append(&task);
    }
  }
  return filtered;
}
