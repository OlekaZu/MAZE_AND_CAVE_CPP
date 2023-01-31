#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <QBrush>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLine>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPen>
#include <QTimer>

#include "../Controller/controller.h"

constexpr unsigned short int Side = 500;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace maze {
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

protected slots:
  void mousePressEvent(QMouseEvent *event) override;
  void on_tabWidget_currentChanged(int index);

private:
  std::unique_ptr<Ui::MainWindow> ui_;
  std::unique_ptr<QGraphicsScene> scene_;
  std::unique_ptr<Controller> sender_;
  std::unique_ptr<QTimer> timer_;
  QString home_path_;
  double step_x_;
  double step_y_;
  std::pair<size_t, size_t> begin_point_;
  std::pair<size_t, size_t> end_point_;
  std::pair<std::vector<size_t>, std::vector<size_t>> maze_map_;
  std::vector<size_t> cave_array_;
  size_t rows_;
  size_t columns_;
  unsigned short int coords_flag_;
  QPen pen_;
  QColor color_;
  void GetStep();
  void DrawCave();
  void DrawBorder();
  void DrawMaze();
  void ClearMazeVars();
  void SceneClear();
  std::pair<size_t, size_t> GetCoords(QColor color);
  void DrawRect(size_t x, size_t y, QColor color);
  void GetWay();

private slots:
  void on_maze_open_pushButton_clicked();
  void on_maze_generate_pushButton_clicked();
  void on_cave_open_pushButton_clicked();
  void on_cave_generate_pushButton_clicked();
  void on_cave_auto_pushButton_clicked();
  void on_cave_stop_pushButton_clicked();
  void on_cave_step_pushButton_clicked();
  void on_maze_safe_pushButton_clicked();
};
} // namespace maze
#endif // SRC_VIEW_MAINWINDOW_H
