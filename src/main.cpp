#include "mainwindow.h"
#include <qapplication.h>
#include <qstyleditemdelegate.h>

#include <qtreeview.h>
#include <today/todotask/model.h>

int
main(int argc, char* argv[])
{
  QApplication app{ argc, argv };
  // MainWindow window;
  // window.show();

  QList<TodoTask> tasks{ {
    { 1, "Task 1", "Description 1", {}, {}, TodoTaskStatus::InProgress },
    { 2, "Task 2", "Description 2", {}, {}, TodoTaskStatus::Done },
    { 3, "Task 3", "Description 3", {}, {} },
    {
      4,
      "Task 3 - 1",
      "Description 3 - 1",
      {},
      {},
      TodoTaskStatus::Done,
      TodoTaskPriority::Medium,
      3,
    },
  } };

  auto* model = new TodoTaskModel{ tasks };
  auto* delegate = new QStyledItemDelegate{};
  QTreeView view;

  QObject::connect(model,
                   &TodoTaskModel::dataChanged,
                   [](const QModelIndex& topLeft,
                      const QModelIndex& bottomRight,
                      const QVector<int>& roles) {
                     qDebug()
                       << "Data changed: " << topLeft << bottomRight << roles;
                   });

  view.setModel(model);
  view.setItemDelegate(delegate);

  view.show();

  return QApplication::exec();
}
