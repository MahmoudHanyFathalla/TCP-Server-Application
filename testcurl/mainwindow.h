#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

using json = nlohmann::json;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CURL* curl;

    void performCurlOperations();
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif // MAINWINDOW_H
