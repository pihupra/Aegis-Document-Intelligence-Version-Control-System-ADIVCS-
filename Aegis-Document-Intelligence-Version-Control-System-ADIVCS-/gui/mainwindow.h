#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <vector>

#include "storage.h"
#include "versioning.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Storage& storage, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Storage& storage_;
    Versioning versioning_;

    void setupUI();

private slots:
    void onCreateDocument();
    void onAddVersion();
    void onListVersions();
    void onDiffVersions();
    void onSearch();
};
