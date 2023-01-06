#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define BUTTON_UP 0x08      //!< Up button
#define BUTTON_DOWN 0x04    //!< Down button
#define BUTTON_LEFT 0x10    //!< Left button
#define BUTTON_RIGHT 0x02   //!< Right button
#define BUTTON_SELECT 0x01  //!< Select button

#include <stdint.h>

#include <QMainWindow>
#include <QTimer>

#include "../../library/lcd/lcdipc.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:

   private:
    Ui::MainWindow *ui;
    uint8_t bt_status;
    LcdIPC &lcdipc;
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
    QTimer *timer;

   private:
    void update();
};
#endif  // MAINWINDOW_H
