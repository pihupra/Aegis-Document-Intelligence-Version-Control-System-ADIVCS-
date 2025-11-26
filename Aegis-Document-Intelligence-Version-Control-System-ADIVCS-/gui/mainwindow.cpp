#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Storage& storage, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), storage_(storage), versioning_(storage)
{
    ui->setupUi(this);
    setupUI();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupUI() {
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::onCreateDocument);
    connect(ui->addVersionButton, &QPushButton::clicked, this, &MainWindow::onAddVersion);
    connect(ui->listButton, &QPushButton::clicked, this, &MainWindow::onListVersions);
    connect(ui->diffButton, &QPushButton::clicked, this, &MainWindow::onDiffVersions);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearch);
}

void MainWindow::onCreateDocument() {
    bool ok;
    QString title = QInputDialog::getText(this, "Title", "Document Title:", QLineEdit::Normal, "", &ok);
    if(!ok) return;
    QString author = QInputDialog::getText(this, "Author", "Author:", QLineEdit::Normal, "", &ok);
    if(!ok) return;
    QString tags = QInputDialog::getText(this, "Tags", "Comma-separated Tags:", QLineEdit::Normal, "", &ok);
    if(!ok) return;
    QString content = QInputDialog::getMultiLineText(this, "Content", "Initial Content:");

    DocumentMeta m;
    m.title = title.toStdString();
    m.author = author.toStdString();
    for(auto &tag: tags.split(',')) m.tags.push_back(tag.toStdString());

    int id = storage_.createDocument(m, content.toStdString());
    QMessageBox::information(this, "Created", "Document ID=" + QString::number(id));
}

void MainWindow::onAddVersion() {
    bool ok;
    int id = QInputDialog::getInt(this, "Doc ID", "Enter Document ID:", 1, 1, 1000000, 1, &ok);
    if(!ok) return;
    QString content = QInputDialog::getMultiLineText(this, "New Version", "Enter Content:");
    storage_.addVersion(id, content.toStdString());
    QMessageBox::information(this, "Success", "Added version.");
}

void MainWindow::onListVersions() {
    int id = QInputDialog::getInt(this, "Doc ID", "Enter Document ID:");
    auto vers = storage_.getVersions(id);
    QString msg;
    for(auto &v : vers)
        msg += QString::number(v.versionId) + " - " + QString::number(v.timestamp) + "\n";
    QMessageBox::information(this, "Versions", msg);
}

void MainWindow::onDiffVersions() {
    int id = QInputDialog::getInt(this, "Doc ID", "Document ID:");
    int v1 = QInputDialog::getInt(this, "Version 1", "Enter v1:");
    int v2 = QInputDialog::getInt(this, "Version 2", "Enter v2:");

    auto diffs = versioning_.diffVersions(id, v1, v2);
    QString msg;
    for(auto &d : diffs) {
        QString prefix = d.type == DiffOp::Equal ? "  " : (d.type == DiffOp::Insert ? "+ " : "- ");
        msg += prefix + QString::fromStdString(d.line) + "\n";
    }
    QMessageBox::information(this, "Diff", msg);
}

void MainWindow::onSearch() {
    QString query = QInputDialog::getText(this, "Search", "Enter query:");
    auto res = storage_.searchMetaByTitleOrTag(query.toStdString());
    QString msg;
    for(auto &m : res)
        msg += QString::number(m.id) + " | " + QString::fromStdString(m.title) + "\n";
    QMessageBox::information(this, "Results", msg);
}
