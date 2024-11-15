#include "mainwindow.h"
#include "today/todotask/todotask.h"
#include <qapplication.h>

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
      "Task 3",
      "Description 3",
      {},
      {},
      TodoTaskStatus::Done,
      TodoTaskPriority::Medium,
      3,
    },
  } };

  auto* model = new TodoTaskModel{ tasks };
  QTreeView view;

  view.setModel(model);
  view.show();

  return QApplication::exec();
}
