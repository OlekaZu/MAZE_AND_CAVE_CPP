#include "mainwindow.h"

#include "ui_mainwindow.h"
using namespace maze;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>()),
      scene_(std::make_unique<QGraphicsScene>()),
      sender_(std::make_unique<Controller>()) {
  ui_->setupUi(this);
  ui_->tabWidget->setCurrentIndex(0);
  scene_->setSceneRect(0, 0, Side, Side);
  ui_->maze_widget->setScene(scene_.get());
  color_ = QColor(128, 128, 128, 255);
  pen_.setColor(color_);
  pen_.setWidth(2);
  coords_flag_ = 1;
  home_path_ = QDir::homePath();
  ui_->maze_safe_pushButton->setEnabled(false);
  timer_ = std::make_unique<QTimer>();
  connect(timer_.get(), &QTimer::timeout, this,
          &MainWindow::on_cave_step_pushButton_clicked);
}

MainWindow::~MainWindow() {}

void MainWindow::on_tabWidget_currentChanged(int index) {
  scene_->clear();
  scene_->setSceneRect(0, 0, Side, Side);
  if (index == 0) {
    timer_->stop();
    ClearMazeVars();
    ui_->maze_widget->setScene(scene_.get());
  } else if (index == 1) {
    coords_flag_ = 1;
    ui_->cave_widget->setScene(scene_.get());
  }
}

void MainWindow::on_maze_open_pushButton_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
      this, "Select the file with the extension .txt", home_path_,
      "TXT Files (*.txt)");
  if (!file_path.isEmpty()) {
    ClearMazeVars();
    ui_->maze_safe_pushButton->setEnabled(false);
    scene_->clear();
    home_path_ = QFileInfo(file_path).absolutePath();
    try {
      coords_flag_ = 2;
      sender_->OpenFile(file_path.toStdString());
      maze_map_ = sender_->GetMaze();
      sender_->CheckMaze();
      rows_ = sender_->GetRows();
      columns_ = sender_->GetColumns();
      ui_->file_name->setText(QFileInfo(file_path).fileName());
      ui_->open_maze_rows->setText(QString::number(rows_));
      ui_->open_maze_columns->setText(QString::number(columns_));
      GetStep();
      DrawBorder();
      DrawMaze();
    } catch (const std::out_of_range &error) {
      coords_flag_ = 1;
      QMessageBox::about(this, "Warning", error.what());
    }
  }
}

void MainWindow::on_cave_open_pushButton_clicked() {
  timer_->stop();
  QString file_path = QFileDialog::getOpenFileName(
      this, "Select the file with the extension .txt", home_path_,
      "TXT Files (*.txt)");
  if (!file_path.isEmpty()) {
    scene_->clear();
    home_path_ = QFileInfo(file_path).absolutePath();
    try {
      sender_->OpenFile(file_path.toStdString());
      sender_->CheckCave();
      cave_array_ = sender_->GetCave();
      rows_ = sender_->GetRows();
      columns_ = sender_->GetColumns();
      sender_->CreateCave(rows_, columns_, cave_array_);
      ui_->cave_auto_pushButton->setEnabled(true);
      ui_->cave_step_pushButton->setEnabled(true);
      ui_->cave_stop_pushButton->setEnabled(true);
      GetStep();
      DrawCave();
    } catch (const std::out_of_range &error) {
      QMessageBox::about(this, "Warning", error.what());
    }
  }
}

void MainWindow::GetStep() {
  step_x_ = Side / double(columns_);
  step_y_ = Side / double(rows_);
}

void MainWindow::DrawBorder() {
  scene_->addLine(QLine(Side, 0, 0, 0), pen_);
  scene_->addLine(QLine(0, Side, 0, 0), pen_);
}

void MainWindow::DrawMaze() {
  double x1 = 0.05, y1 = 0.05, x2 = 0.05, y2 = 0.05;
  size_t count_x1 = 0, count_x2 = 0;
  for (size_t i = 0, j = 0;
       i < maze_map_.first.size() && j < maze_map_.second.size(); ++i, ++j) {
    if (maze_map_.first[i])
      scene_->addLine(QLine(x1 + step_x_, y1 + step_y_, x1 + step_x_, y1),
                      pen_);
    if (maze_map_.second[j])
      scene_->addLine(QLine(x2, y2 + step_y_, x2 + step_x_, y2 + step_y_),
                      pen_);
    x1 += step_x_;
    x2 += step_x_;
    count_x1++;
    count_x2++;
    if (count_x1 == columns_) {
      count_x1 = 0;
      x1 = 0.05;
      y1 += step_y_;
    }
    if (count_x2 == columns_) {
      count_x2 = 0;
      x2 = 0.05;
      y2 += step_y_;
    }
  }
}

void MainWindow::on_maze_generate_pushButton_clicked() {
  ClearMazeVars();
  rows_ = ui_->maze_rows_spinBox->value();
  columns_ = ui_->maze_columns_spinBox->value();
  scene_->clear();
  if (rows_ && columns_) {
    coords_flag_ = 2;
    ui_->maze_safe_pushButton->setEnabled(true);
    maze_map_ = sender_->GenerateIdealLabyrinth(rows_, columns_);
    GetStep();
    DrawBorder();
    DrawMaze();
  } else {
    QMessageBox::about(this, "Warning",
                       "Input rows and cols for generating the labyrinth");
  }
}

void MainWindow::GetWay() {
  try {
    auto findway_coordinates = sender_->SolveLabyrinth(
        begin_point_, end_point_, rows_, columns_, maze_map_);
    QPen way;
    way.setColor(Qt::red);
    way.setWidth(2);
    for (size_t i = 0; i < (findway_coordinates.size() - 1); ++i) {
      scene_->addLine(
          QLine(findway_coordinates[i].second * step_x_ + step_x_ / 2,
                findway_coordinates[i].first * step_y_ + step_y_ / 2,
                findway_coordinates[i + 1].second * step_x_ + step_x_ / 2,
                findway_coordinates[i + 1].first * step_y_ + step_y_ / 2),
          way);
    }
    DrawRect(findway_coordinates[0].second, findway_coordinates[0].first,
             Qt::green);
  } catch (const std::out_of_range &error) {
    SceneClear();
    coords_flag_ = 2;
    QMessageBox::about(this, "Warning", error.what());
  }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  if (ui_->maze_widget->underMouse() && coords_flag_ > 1) {
    if (event->button() == Qt::LeftButton) {
      if (coords_flag_ == 2) {
        SceneClear();
        begin_point_ = GetCoords(Qt::green);
        coords_flag_ = 3;
      } else if (coords_flag_ == 3) {
        end_point_ = GetCoords(Qt::red);
        if (begin_point_.second == end_point_.second &&
            begin_point_.first == end_point_.first) {
          SceneClear();
          coords_flag_ = 2;
          QMessageBox::about(this, "Warning", "The coordinates match!");
        } else {
          coords_flag_ = 2;
          GetWay();
        }
      }
    } else if (event->button() == Qt::RightButton) {
      SceneClear();
      coords_flag_ = 2;
    }
  }
}

std::pair<size_t, size_t> MainWindow::GetCoords(QColor color) {
  size_t mult_x = 0, mult_y = 0;
  QPointF point_coord = ui_->maze_widget->mapFromGlobal(QCursor::pos());
  mult_x = trunc(point_coord.x() / step_x_);
  mult_y = trunc(point_coord.y() / step_y_);
  DrawRect(mult_x, mult_y, color);
  return std::make_pair(mult_y, mult_x);
}

void MainWindow::DrawRect(size_t x, size_t y, QColor color) {
  scene_->addRect(x * step_x_ + 1, y * step_y_ + 1, step_x_ - 3, step_y_ - 3,
                  QPen(color), QBrush(color));
}

void MainWindow::on_cave_generate_pushButton_clicked() {
  timer_->stop();
  rows_ = ui_->cave_rows_spinBox->value();
  columns_ = ui_->cave_columns_spinBox->value();
  int chance_value = ui_->cave_chance_spinBox->value();
  if (rows_ && columns_ && chance_value) {
    sender_->GenerateCave(rows_, columns_, chance_value);
    GetStep();
    DrawCave();
    ui_->cave_auto_pushButton->setEnabled(true);
    ui_->cave_step_pushButton->setEnabled(true);
    ui_->cave_stop_pushButton->setEnabled(true);
  } else {
    QMessageBox::about(this, "Warning",
                       "Input rows, cols and chance for born of a cell for "
                       "generating the cave");
  }
}

void MainWindow::on_cave_step_pushButton_clicked() {
  int birth_value = ui_->cave_birth_spinBox->value();
  int death_value = ui_->cave_death_spinBox->value();
  sender_->StepDrawCave(birth_value, death_value);
  GetStep();
  DrawCave();
}

void MainWindow::on_cave_auto_pushButton_clicked() {
  int freq_value = ui_->cave_freq_spinBox->value();
  if (freq_value)
    timer_->start(freq_value);
  else
    QMessageBox::about(this, "Warning",
                       "Input frequency value for auto mode the cave");
}

void MainWindow::on_cave_stop_pushButton_clicked() { timer_->stop(); }

void MainWindow::DrawCave() {
  scene_->clear();
  cave_array_.clear();
  cave_array_ = sender_->GetCaveArray();
  auto iter_value = cave_array_.begin();
  for (size_t row_value = 0; row_value < rows_; ++row_value) {
    for (size_t col_value = 0; col_value < columns_; ++col_value) {
      if (*iter_value == 1) {
        double cave_p_1 = step_x_ * col_value;
        double cave_p_2 = step_y_ * row_value;
        scene_->addRect(cave_p_1, cave_p_2, step_x_, step_y_, pen_,
                        QBrush(color_));
      }
      ++iter_value;
    }
  }
}

void MainWindow::ClearMazeVars() {
  ui_->file_name->setText("");
  ui_->open_maze_rows->setText("");
  ui_->open_maze_columns->setText("");
  coords_flag_ = 1;
}

void MainWindow::on_maze_safe_pushButton_clicked() {
  QString file_path =
      QFileDialog::getSaveFileName(this, "Save as...", "", "TXT Files (*.txt)");
  if (!file_path.isEmpty()) {
    QFile file(file_path);
    unsigned int count = 0;
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream writeStream(&file);
      writeStream << rows_ << " " << columns_ << "\n";
      for (unsigned int i = 0; i < maze_map_.first.size(); ++i) {
        writeStream << maze_map_.first[i] << " ";
        count++;
        if (count == columns_) {
          count = 0;
          writeStream << "\n";
        }
      }
      count = 0;
      writeStream << "\n";
      for (unsigned int j = 0; j < maze_map_.second.size(); ++j) {
        writeStream << maze_map_.second[j] << " ";
        count++;
        if (count == columns_) {
          count = 0;
          writeStream << "\n";
        }
      }
      file.close();
    }
  }
}

void MainWindow::SceneClear() {
  scene_->clear();
  DrawBorder();
  DrawMaze();
}
