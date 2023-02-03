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

#include <qdebug.h>

#include <sstream>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), serial(SerialIPC::getInstance()), timer(new QTimer(this)), to_send() {
    ui->setupUi(this);
    ui->lineEndingSelector->addItem("No Line Ending");
    ui->lineEndingSelector->addItem("New Line");
    ui->lineEndingSelector->addItem("Cariage Return");
    ui->lineEndingSelector->addItem("Both NL & CR");
    connect(timer, &QTimer::timeout, this, &::MainWindow::read_serial);
    connect(timer, &QTimer::timeout, this, &::MainWindow::write_serial);
    timer->start(1);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_inputLine_returnPressed() {
    QString inputStr = ui->inputLine->text();
    ui->inputLine->clear();
    QTextCursor cursor = ui->stdInBox->textCursor();
    ui->stdInBox->moveCursor(cursor.End);
    if (ui->lineEndingSelector->currentText() == "Both NL & CR") {
        inputStr.append("\r\n");

    } else if (ui->lineEndingSelector->currentText() == "New Line") {
        inputStr.append("\n");

    } else if (ui->lineEndingSelector->currentText() == "Cariage Return") {
        inputStr.append("\r");
    }
    ui->stdInBox->insertPlainText(inputStr);
    to_send.append(inputStr.toStdString());
    ui->stdInBox->moveCursor(cursor.End);
    write_serial();
}

void MainWindow::read_serial() {
    std::stringstream ss;
    while (serial->c_available() > 0) {
        unsigned char temp = serial->c_read();
        ss << temp;
    }
    auto str_temp = ss.str();
    if (str_temp.size() > 0) {
        QTextCursor cursor = ui->stdOutBox->textCursor();
        ui->stdOutBox->moveCursor(cursor.End);
        ui->stdOutBox->insertPlainText(QString::fromStdString(str_temp));
        ui->stdOutBox->moveCursor(cursor.End);
    }
}

void MainWindow::write_serial() {
    while ((serial->c_availableForWrite() > 0) && (to_send.size() > 0)) {
        serial->c_write(to_send.front());
        to_send.erase(to_send.begin());
        qDebug() << QString::fromStdString(to_send);
    }
}
