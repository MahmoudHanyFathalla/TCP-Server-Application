#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <pistache/endpoint.h>

class MyHandler : public Pistache::Http::Handler {
public:
    HTTP_PROTOTYPE(MyHandler)

    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response) override {
        response.send(Pistache::Http::Code::Ok, "Hello, World!");
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create Pistache HTTP server
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080)); // Choose your desired port
    auto opts = Pistache::Http::Endpoint::options().threads(1);
    auto server = std::make_shared<Pistache::Http::Endpoint>(addr);
    server->init(opts);
    server->setHandler(std::make_shared<MyHandler>());
    server->serveThreaded();
}

MainWindow::~MainWindow()
{
    delete ui;
}
