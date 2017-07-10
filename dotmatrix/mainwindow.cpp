/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "imagemodel.h"
#include "mainwindow.h"
#include "pixeldelegate.h"
#include "maindialog.h"
#include "qdebug.h"


#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif

//! [0]
MainWindow::MainWindow()
{
//! [0]
    currentPath = QDir::homePath();
    model = new ImageModel(this);

    QWidget *centralWidget = new QWidget;

//! [1]
    view = new QTableView;
    view->setShowGrid(false);
    view->horizontalHeader()->hide();
    view->verticalHeader()->hide();
    view->horizontalHeader()->setMinimumSectionSize(1);
    view->verticalHeader()->setMinimumSectionSize(1);
    view->setModel(model);
//! [1]

//! [2]
    PixelDelegate *delegate = new PixelDelegate(this);
    view->setItemDelegate(delegate);
//! [2]

//! [3]
    QLabel *pixelSizeLabel = new QLabel(tr("Pixel size:"));
    pixelSizeSpinBox = new QSpinBox;
    pixelSizeSpinBox->setMinimum(1);
    pixelSizeSpinBox->setMaximum(32);
    pixelSizeSpinBox->setValue(12);
//! [3]

    QMenu *fileMenu = new QMenu(tr("&File"), this);
    QAction *openAction = fileMenu->addAction(tr("&Open"));
    openAction->setShortcuts(QKeySequence::Open);
    QPixmap pix(":/images/open.png");
    QIcon icon(pix);
    openAction->setIcon(icon);

    QAction *savePltAction = fileMenu->addAction(tr("&Save as Plt"));
    savePltAction->setShortcuts(QKeySequence::Save);
    QPixmap pix1(":/images/save.png");
    QIcon icon1(pix1);
    savePltAction->setIcon(icon1);

    QAction *saveVectorAction = fileMenu->addAction(tr("&Save as Vector"));
    saveVectorAction->setIcon(icon1);

    QAction *webAction = fileMenu->addAction(tr("www.laser-cutz.com"));

//    printAction = fileMenu->addAction(tr("&Print..."));
//    printAction->setEnabled(false);
//    printAction->setShortcut(QKeySequence::Print);

    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcuts(QKeySequence::Quit);

    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    QAction *aboutAction = helpMenu->addAction(tr("&About"));

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();
    menuBar()->addMenu(helpMenu);

    connect(openAction, &QAction::triggered, this, &MainWindow::chooseImage);
    connect(savePltAction, &QAction::triggered, this, &MainWindow::saveImage);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutBox);
//! [4]
    typedef void (QSpinBox::*QSpinBoxIntSignal)(int);
    connect(pixelSizeSpinBox, static_cast<QSpinBoxIntSignal>(&QSpinBox::valueChanged),
            delegate, &PixelDelegate::setPixelSize);
    connect(pixelSizeSpinBox, static_cast<QSpinBoxIntSignal>(&QSpinBox::valueChanged),
            this, &MainWindow::updateView);

//! [4]

    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(pixelSizeLabel);
    controlsLayout->addWidget(pixelSizeSpinBox);
    controlsLayout->addStretch(1);

//toolbar
    QPushButton *openBtn = new QPushButton("");
    QPushButton *saveBtn = new QPushButton("");
    QPushButton *maxBtn = new QPushButton("");
    QPushButton *minBtn = new QPushButton("");
    QLabel *widthLabel = new QLabel("W*H");
    widthEdit = new QLineEdit();
    QLabel *heightLabel = new QLabel("*");
    heightEdit = new QLineEdit();
    QComboBox *unitCombo = new QComboBox();
    QLabel *dotsizeLabel = new QLabel("DotSize");
    sizeCombo = new QComboBox();
    QCheckBox *check = new QCheckBox("Ignore Black");
    openBtn->setMinimumSize(30,25);
    openBtn->setStyleSheet("QPushButton{border-style:none;background-image:url(':/images/open.png')} QPushButton:pressed{border-style:none;background-image:url(':/images/open_on.png')}");
    saveBtn->setMinimumSize(30,25);
    saveBtn->setStyleSheet("QPushButton{border-style:none;background-image:url(':/images/save.png')} QPushButton:pressed{border-style:none;background-image:url(':/images/save_on.png')}");
    maxBtn->setMinimumSize(25,25);
    maxBtn->setStyleSheet("QPushButton{border-style:none;background-image:url(':/images/increase.png')} QPushButton:pressed{border-style:none;background-image:url(':/images/increase_on.png')}");
    minBtn->setMinimumSize(25,25);
    minBtn->setStyleSheet("QPushButton{border-style:none;background-image:url(':/images/decrease.png')} QPushButton:pressed{border-style:none;background-image:url(':/images/decrease-_on.png')}");
    unitCombo->insertItem(0,"mm");
    unitCombo->insertItem(1,"inch");
    for(int i = 1;i<=32;i+=1)
    {
        sizeCombo->insertItem(i,QString::number(i));
    }
    widthEdit->setText(QString::number(view->geometry().width()));
    heightEdit->setText(QString::number(view->geometry().height()));
    //widthEdit->setText(QString::number(view->columnWidth(0)));
    //heightEdit->setText(QString::number(view->rowHeight(0)));
    qDebug()<<"view_width = "<<view->geometry().width();
    qDebug()<<"view_height = "<<view->geometry().height();
    qDebug()<<"view_height = "<<view->columnWidth(1);
    qDebug()<<"view_height = "<<view->rowHeight(1);


    QObject::connect(maxBtn,SIGNAL(clicked()),this,SLOT(spinMaxFunction()));
    QObject::connect(minBtn,SIGNAL(clicked()),this,SLOT(spinMinFunction()));

    QObject::connect(widthEdit,SIGNAL(returnPressed()),this,SLOT(widthReturnFunction()));
    QObject::connect(heightEdit,SIGNAL(returnPressed()),this,SLOT(heightReturnFunction()));

    QObject::connect(sizeCombo,SIGNAL(activated(QString)),this,SLOT(sizeChangeFunction()));
    QObject::connect(openBtn,SIGNAL(clicked()),this,SLOT(chooseImage()));
    QObject::connect(saveBtn,SIGNAL(clicked()),this,SLOT(saveImage()));

    QHBoxLayout *toolLayout = new QHBoxLayout;
    toolLayout->addWidget(openBtn);
    toolLayout->addWidget(saveBtn);
    toolLayout->addWidget(maxBtn);
    toolLayout->addWidget(minBtn);
    toolLayout->addWidget(widthLabel);
    toolLayout->addWidget(widthEdit);
    toolLayout->addWidget(heightLabel);
    toolLayout->addWidget(heightEdit);
    toolLayout->addWidget(unitCombo);
    toolLayout->addWidget(dotsizeLabel);
    toolLayout->addWidget(sizeCombo);
    toolLayout->addWidget(check);
    toolLayout->addStretch(1);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(toolLayout);
    mainLayout->addWidget(view);
    //mainLayout->addLayout(controlsLayout);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    setWindowTitle(tr("Pixelator"));
    resize(640, 480);
//! [5]
    this->setWindowTitle("Dot Matrix Converter");
}
//! [5]
//!
//!
void MainWindow::sizeChangeFunction()
{

//    PixelDelegate *pixel = new PixelDelegate();
    int value =  sizeCombo->currentText().toInt();
//    pixel->setPixelSize(value);
//    qDebug()<<"sizecombo value = "<< value;
//    updateView();
    pixelSizeSpinBox->setValue(value);
}

void MainWindow::spinMaxFunction()
{
    PixelDelegate *pixel = new PixelDelegate();
    int value =  pixelSizeSpinBox->value();
    qDebug()<<"pixelSizeSpinbox = "<< value;
    pixel->setPixelSize(value);
    pixelSizeSpinBox->setValue(value+1);
    updateView();
}

void MainWindow::spinMinFunction()
{
    PixelDelegate *pixel = new PixelDelegate();
    int value =  pixelSizeSpinBox->value();
    pixel->setPixelSize(value);
    pixelSizeSpinBox->setValue(value-1);
    updateView();
}

void MainWindow::widthReturnFunction()
{
    int ii = widthEdit->text().toInt();
    for(int i = 0;i<640;i++)
    {
        view->setColumnWidth(i,ii/64);
    }

}

void MainWindow::heightReturnFunction()
{
    int ii = heightEdit->text().toInt();
    for(int i = 0;i<480;i++)
    {
        view->setRowHeight(i,ii/48);
    }
}

void MainWindow::chooseImage()
{
    openfilename = QFileDialog::getOpenFileName(this,
        tr("Choose an image"), currentPath, "*");

    if (!openfilename.isEmpty())
        openImage(openfilename);
}
/////////////////
void MainWindow::exportSVG()
{

}
void MainWindow::exportPNG()
{

}


void MainWindow::saveImage()
{

}

void MainWindow::openImage(const QString &fileName)
{
    openfilename = fileName;
    QImage image;

    if (image.load(fileName)) {
        model->setImage(image);
        if (!fileName.startsWith(":/")) {
            currentPath = fileName;
            setWindowTitle(tr("%1 - Pixelator").arg(currentPath));
        }

       // printAction->setEnabled(true);
        updateView();
    }
}

void MainWindow::printImage()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    if (model->rowCount(QModelIndex())*model->columnCount(QModelIndex()) > 90000) {
        QMessageBox::StandardButton answer;
        answer = QMessageBox::question(this, tr("Large Image Size"),
                tr("The printed image may be very large. Are you sure that "
                   "you want to print it?"),
        QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::No)
            return;
    }

    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle(tr("Print Image"));

    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    QPainter painter;
    painter.begin(&printer);

    int rows = model->rowCount(QModelIndex());
    int columns = model->columnCount(QModelIndex());
    int sourceWidth = (columns + 1) * ItemSize;
    int sourceHeight = (rows + 1) * ItemSize;

    painter.save();

    double xscale = printer.pageRect().width() / double(sourceWidth);
    double yscale = printer.pageRect().height() / double(sourceHeight);
    double scale = qMin(xscale, yscale);

    painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                      printer.paperRect().y() + printer.pageRect().height() / 2);
    painter.scale(scale, scale);
    painter.translate(-sourceWidth / 2, -sourceHeight / 2);

    QStyleOptionViewItem option;
    QModelIndex parent = QModelIndex();

    QProgressDialog progress(tr("Printing..."), tr("Cancel"), 0, rows, this);
    progress.setWindowModality(Qt::ApplicationModal);
    float y = ItemSize / 2;

    for (int row = 0; row < rows; ++row) {
        progress.setValue(row);
        qApp->processEvents();
        if (progress.wasCanceled())
            break;

        float x = ItemSize / 2;

        for (int column = 0; column < columns; ++column) {
            option.rect = QRect(int(x), int(y), ItemSize, ItemSize);
            view->itemDelegate()->paint(&painter, option,
                                        model->index(row, column, parent));
            x = x + ItemSize;
        }
        y = y + ItemSize;
    }
    progress.setValue(rows);

    painter.restore();
    painter.end();

    if (progress.wasCanceled()) {
        QMessageBox::information(this, tr("Printing canceled"),
            tr("The printing process was canceled."), QMessageBox::Cancel);
    }
#else
    QMessageBox::information(this, tr("Printing canceled"),
        tr("Printing is not supported on this Qt build"), QMessageBox::Cancel);
#endif
}

void MainWindow::showAboutBox()
{
    mainDialog *about = new mainDialog();
    about->show();
}

//! [6]
void MainWindow::updateView()
{
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    //widthEdit->setText(QString::number(view->geometry().width()));
    //heightEdit->setText(QString::number(view->geometry().height()));
}
//! [6]
