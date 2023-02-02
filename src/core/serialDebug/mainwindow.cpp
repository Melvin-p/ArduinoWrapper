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
    ui->lineEndingSelector->addItem("No Line Ending");
    ui->lineEndingSelector->addItem("New Line");
    ui->lineEndingSelector->addItem("Cariage Return");
    ui->lineEndingSelector->addItem("Both NL & CR");
    connect(timer, &QTimer::timeout, this, &::MainWindow::read_serial);
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
        ui->stdInBox->insertPlainText(inputStr.append("\r\n"));
    } else if (ui->lineEndingSelector->currentText() == "New Line") {
        ui->stdInBox->insertPlainText(inputStr.append("\n"));
    } else if (ui->lineEndingSelector->currentText() == "Cariage Return") {
        ui->stdInBox->insertPlainText(inputStr.append("\r"));
    } else {
        ui->stdInBox->insertPlainText(inputStr);
    }
    ui->stdInBox->moveCursor(cursor.End);
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

void MainWindow::on_inputLine_selectionChanged() {
}
