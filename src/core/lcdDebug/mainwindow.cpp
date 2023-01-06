#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), lcdipc(LcdIPC::getInstance()), timer(new QTimer(this)) {
    ui->setupUi(this);
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    ui->plainTextEdit->setFont(font);
    bt_status = 0;
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(1);
}

MainWindow::~MainWindow() {
    delete ui;
    delete timer;
}

void MainWindow::keyPressEvent(QKeyEvent *ev) {
    if (ev->isAutoRepeat()) {
        return;
    } else if (!ev->isAutoRepeat()) {
        auto k = ev->key();
        switch (k) {
            case Qt::Key_W: {
                bt_status = bt_status | BUTTON_UP;
                break;
            }
            case Qt::Key_S: {
                bt_status = bt_status | BUTTON_DOWN;
                break;
            }
            case Qt::Key_A: {
                bt_status = bt_status | BUTTON_LEFT;
                break;
            }
            case Qt::Key_D: {
                bt_status = bt_status | BUTTON_RIGHT;
                break;
            }
            case Qt::Key_C: {
                bt_status = bt_status | BUTTON_SELECT;
                break;
            }
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev) {
    if (ev->isAutoRepeat()) {
        return;
    } else if (!ev->isAutoRepeat()) {
        auto k = ev->key();
        switch (k) {
            case Qt::Key_W: {
                bt_status = bt_status & ~BUTTON_UP;
                break;
            }
            case Qt::Key_S: {
                bt_status = bt_status & ~BUTTON_DOWN;
                break;
            }
            case Qt::Key_A: {
                bt_status = bt_status & ~BUTTON_LEFT;
                break;
            }
            case Qt::Key_D: {
                bt_status = bt_status & ~BUTTON_RIGHT;
                break;
            }
            case Qt::Key_C: {
                bt_status = bt_status & ~BUTTON_SELECT;
                break;
            }
        }
    }
}

void MainWindow::update() {
    lcdipc.setButton(bt_status);
    lcd value = lcdipc.getLcd();

    ui->plainTextEdit->clear();

    for (uint8_t i = 0; i < 7; i++) {
        for (uint16_t j = 0; j < 16; j++) {
            unsigned char row = value[j][i];
            for (uint8_t mask = 0x80; mask != 0; mask >>= 1) {
                if (row & mask) {
                    // write character if bit is 1
                    ui->plainTextEdit->insertPlainText("0");
                } else {
                    ui->plainTextEdit->insertPlainText(" ");
                }
            }
        }
        ui->plainTextEdit->appendPlainText("");
    }

    for (uint8_t i = 0; i < 7; i++) {
        for (uint16_t j = 16; j < 32; j++) {
            unsigned char row = value[j][i];
            for (uint8_t mask = 0x80; mask != 0; mask >>= 1) {
                if (row & mask) {
                    // write character if bit is 1
                    ui->plainTextEdit->insertPlainText("0");
                } else {
                    ui->plainTextEdit->insertPlainText(" ");
                }
            }
        }
        ui->plainTextEdit->appendPlainText("");
    }
}
