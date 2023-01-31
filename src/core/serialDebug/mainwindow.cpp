/*
    Copyright (C) 2023 Melvin Pynadath

    This file is part of ArduinoWrapper.

    ArduinoWrapper is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ArduinoWrapper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ArduinoWrapper.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"

#include <sstream>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), serial(SerialIPC::getInstance()), timer(new QTimer(this)) {
    ui->setupUi(this);
    connect(timer, &QTimer::timeout, this, &::MainWindow::read_serial);
    timer->start(1);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_inputLine_returnPressed() {
    QString k = ui->inputLine->text();
    ui->inputLine->clear();
    qDebug() << "Enter Key pressed:" << k;
}

void MainWindow::read_serial() {
    std::stringstream ss;
    while (serial->available() > 0) {
        unsigned char temp = serial->read();
        ss << temp;
    }
    QTextCursor cursor = ui->stdOutBox->textCursor();
    ui->stdOutBox->moveCursor(cursor.End);
    QString temp_2 = QString::fromStdString(ss.str());
    ui->stdOutBox->insertPlainText(temp_2);
    ui->stdOutBox->moveCursor(cursor.End);
}
