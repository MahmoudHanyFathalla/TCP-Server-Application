#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), curl(nullptr)
{
    ui->setupUi(this);

    // Initialize libcurl globally
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Initialize libcurl easy handle
    curl = curl_easy_init();

    // Perform the CURL operations
    performCurlOperations();
}

MainWindow::~MainWindow()
{
    // Cleanup libcurl easy handle
    if (curl) {
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl globally
    curl_global_cleanup();

    // Delete the user interface
    delete ui;
}

void MainWindow::performCurlOperations()
{
    try {
        // Check if libcurl easy handle is initialized
        if (curl) {
            // Set the URL to retrieve information about a post from JSONPlaceholder API
            curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts");

            // Set the callback function for writing received data
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

            // Create a string to store the raw response
            std::string response;

            // Set the string as the data to be written to
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);



            // Perform the HTTP request
            CURLcode res = curl_easy_perform(curl);

            // Check if the HTTP request was successful
            if (res != CURLE_OK) {
                qCritical() << "curl_easy_perform() failed:" << curl_easy_strerror(res);

                // Get and log the HTTP response code in case of failure
                long httpCode = 0;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
                qCritical() << "HTTP response code:" << httpCode;
            } else {
                // Log the raw response
                qDebug() << "Raw Response:" << QString::fromStdString(response);

                // Parse the JSON response
                try {
                    json jsonResponse = json::parse(response);
                    qDebug() << "Parsed Response:" << QString::fromStdString(jsonResponse.dump());
                } catch (const json::parse_error& e) {
                    qCritical() << "JSON parsing error:" << e.what();
                    qCritical() << "Raw JSON Response:" << QString::fromStdString(response);
                }
            }
        }
    } catch (const std::exception& e) {
        // Log any standard C++ exceptions that may occur
        qCritical() << "Exception occurred:" << e.what();
    } catch (...) {
        // Log any unknown exceptions that may occur
        qCritical() << "Unknown exception occurred";
    }
}


size_t MainWindow::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    // Calculate the total size of the received data
    size_t realsize = size * nmemb;

    // Cast the user data pointer to a std::string pointer
    std::string* result = static_cast<std::string*>(userp);

    // Append the received data to the result string
    result->append(static_cast<char*>(contents), realsize);

    // Return the total size of the received data
    return realsize;
}
