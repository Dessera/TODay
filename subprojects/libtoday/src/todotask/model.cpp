#include <algorithm>
#include <qabstractitemmodel.h>
#include <ranges>

#include "today/todotask/model.h"
#include "today/todotask/todotask.h"

TodoTaskModel::TodoTaskModel(QList<TodoTask> tasks, QObject* parent)
  : QAbstractItemModel(parent)
  , m_tasks(std::move(tasks))
{
}

TodoTaskModel::~TodoTaskModel() = default;

int
TodoTaskModel::rowCount(const QModelIndex& parent) const
{
  const auto* parent_task = TodoTask::from_index(parent);
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
  const auto* task = TodoTask::from_index(index);
  if (!TodoTask::is_valid(task)) {
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
    return "任务名称";
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

  const auto* parent_task = TodoTask::from_index(parent);
  auto current_tasks = this->tasks(
    (parent_task != nullptr) ? parent_task->id : TodoTask::INVALID_ID);
  if (row >= current_tasks.size()) {
    return {};
  }
  const auto* task = current_tasks.at(row);
  return this->createIndex(row, column, task);
}

QModelIndex
TodoTaskModel::parent(const QModelIndex& index) const
{
  const auto* task = TodoTask::from_index(index);
  if (!TodoTask::is_valid(task)) {
    return {};
  }

  const auto* parent_task = this->get_parent(task);
  if (!TodoTask::is_valid(parent_task)) {
    return {};
  }

  int v_row = this->row_of_task(task);
  int v_column = index.column();
  return this->createIndex(v_row, v_column, parent_task);
}

QModelIndex
TodoTaskModel::sibling(int row, int column, const QModelIndex& index) const
{
  if (row < 0 || column < 0 || !index.isValid()) {
    return {};
  }

  const auto* current_task = TodoTask::from_index(index);
  if (!TodoTask::is_valid(current_task)) {
    return {};
  }

  auto tasks = this->tasks(current_task->parent_id);
  if (row >= tasks.size()) {
    return {};
  }

  const auto* sibling_task = tasks.at(row);
  return this->createIndex(row, column, sibling_task);
}

bool
TodoTaskModel::hasChildren(const QModelIndex& parent) const
{
  const auto* parent_task = TodoTask::from_index(parent);
  if (!TodoTask::is_valid(parent_task)) {
    return true;
  }

  auto tasks = this->tasks(parent_task->id);
  return !tasks.isEmpty();
}

Qt::ItemFlags
TodoTaskModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);
  if (!index.isValid()) {
    return flags;
  }

  flags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
  return flags;
}

bool
TodoTaskModel::setData(const QModelIndex& index,
                       const QVariant& value,
                       int role)
{
  if (role != Qt::EditRole) {
    return false;
  }

  auto* task = TodoTask::from_index_mut(index);
  if (!TodoTask::is_valid(task)) {
    return false;
  }

  task->name = value.toString();
  emit dataChanged(index, index);
  return true;
}

TodoTask::ConstPtr
TodoTaskModel::get_parent(TodoTask::ConstPtr task) const
{
  if (!TodoTask::is_valid(task)) {
    return TodoTask::INVALID_TASK;
  }

  auto it_parent =
    std::find_if(m_tasks.begin(), m_tasks.end(), [task](const auto& t) {
      return t.id == task->parent_id;
    });
  return it_parent != m_tasks.end() ? &(*it_parent) : nullptr;
}

int
TodoTaskModel::row_of_task(TodoTask::ConstPtr task) const
{
  auto tasks = this->tasks(task->parent_id);
  return static_cast<int>(tasks.indexOf(task));
}

QList<TodoTask::ConstPtr>
TodoTaskModel::tasks(int parent_id) const
{
  namespace views = std::views;
  namespace ranges = std::ranges;
  return m_tasks | views::filter([parent_id](const auto& task) {
           return task.parent_id == parent_id;
         }) |
         views::transform([](const auto& task) { return &task; }) |
         ranges::to<QList<TodoTask::ConstPtr>>();
}
