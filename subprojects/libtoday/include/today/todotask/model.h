#pragma once

#include <qabstractitemmodel.h>
#include <qlist.h>

#include "today/common.h"
#include "today/todotask/todotask.h"

class TODAY_PUBLIC TodoTaskModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  TodoTaskModel(QList<TodoTask> tasks = {}, QObject* parent = nullptr);
  ~TodoTaskModel() override;

  [[nodiscard]] int rowCount(
    const QModelIndex& parent = QModelIndex()) const override;
  [[nodiscard]] int columnCount(
    const QModelIndex& parent = QModelIndex()) const override;

  [[nodiscard]] QVariant data(const QModelIndex& index,
                              int role = Qt::DisplayRole) const override;
  [[nodiscard]] QVariant headerData(int section,
                                    Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const override;

  [[nodiscard]] QModelIndex index(
    int row,
    int column,
    const QModelIndex& parent = QModelIndex()) const override;
  [[nodiscard]] QModelIndex parent(const QModelIndex& index) const override;
  [[nodiscard]] QModelIndex sibling(int row,
                                    int column,
                                    const QModelIndex& index) const override;
  [[nodiscard]] bool hasChildren(const QModelIndex& parent) const override;

  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex& index) const override;

  [[nodiscard]] bool setData(const QModelIndex& index,
                             const QVariant& value,
                             int role = Qt::EditRole) override;

private:
  [[nodiscard]] TodoTask::ConstPtr get_parent(TodoTask::ConstPtr task) const;
  [[nodiscard]] int row_of_task(TodoTask::ConstPtr task) const;

public:
  [[nodiscard]] QList<TodoTask::ConstPtr> tasks(
    int parent_id = TodoTask::INVALID_ID) const;

private:
  QList<TodoTask> m_tasks;
};