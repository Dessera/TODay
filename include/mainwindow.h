#pragma once

#include <qmainwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow final : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() final;

private:
  Ui::MainWindow* ui;
};