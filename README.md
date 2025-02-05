# TCP Server Application

## Overview

This project is a simple TCP server application built using Qt framework. It listens for incoming TCP connections on port 1234 and handles client connections by reading data sent from clients. The application is designed to be cross-platform and can be compiled for various operating systems, including Windows, macOS, and Linux.

## Features

- **TCP Server**: The application acts as a TCP server that listens for incoming connections on a specified port (default: 1234).
- **Client Handling**: It can handle multiple client connections simultaneously.
- **Data Reading**: The server reads data sent by clients and logs it to the console.
- **Cross-Platform**: Built using Qt, the application can be compiled and run on multiple platforms.

## Prerequisites

Before you can build and run this project, you need to have the following installed on your system:

- **CMake** (version 3.5 or higher)
- **Qt** (version 5 or 6)
- **C++ Compiler** (supporting C++17)

## Building the Project

### Step 1: Clone the Repository

First, clone the repository to your local machine:

```bash
git clone https://github.com/yourusername/tcp-server-app.git
cd tcp-server-app
```

### Step 2: Configure the Project with CMake

Create a build directory and configure the project using CMake:

```bash
mkdir build
cd build
cmake ..
```

### Step 3: Build the Project

Compile the project using your preferred build tool. For example, if you're using `make`, run:

```bash
make
```

### Step 4: Run the Application

After building the project, you can run the executable:

```bash
./untitled2
```

## Project Structure

The project is structured as follows:

- **CMakeLists.txt**: The CMake configuration file for building the project.
- **main.cpp**: The main entry point of the application.
- **mainwindow.cpp**: Implementation of the main window, including the TCP server logic.
- **mainwindow.h**: Header file for the main window class.
- **mainwindow.ui**: UI file for the main window, created using Qt Designer.

## Code Overview

### Main Window (MainWindow Class)

The `MainWindow` class is the core of the application. It sets up the TCP server and handles incoming client connections.

- **TCP Server Initialization**: The server is initialized in the `MainWindow` constructor and starts listening on port 1234.
- **New Connection Handling**: When a new client connects, the `newConnection` slot is triggered, and a new `QTcpSocket` is created to handle the connection.
- **Data Reading**: The `readData` slot reads data from the client socket and logs it to the console.

### Main Function

The `main` function initializes the Qt application, creates the main window, and starts the event loop.

## Customization

### Changing the Port

To change the port on which the server listens, modify the `listen` call in the `MainWindow` constructor:

```cpp
if (!tcpServer->listen(QHostAddress::Any, 1234)) {
    qDebug() << "Error: Unable to start the server";
    return;
}
```

Replace `1234` with your desired port number.

### Adding UI Elements

You can add additional UI elements by editing the `mainwindow.ui` file using Qt Designer. To open the file in Qt Designer, run:

```bash
designer mainwindow.ui
```

## Deployment

### Installing the Application

To install the application, run the following command from the build directory:

```bash
make install
```

This will install the application to the default installation directory.

### Cross-Platform Deployment

For cross-platform deployment, you can use Qt's deployment tools. For example, to create a macOS bundle, run:

```bash
macdeployqt untitled2.app
```

For Windows, you can use the `windeployqt` tool:

```bash
windeployqt untitled2.exe
```

## Troubleshooting

- **Server Not Starting**: If the server fails to start, ensure that the specified port is not already in use by another application.
- **Client Connection Issues**: Ensure that the client is connecting to the correct IP address and port.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

## Acknowledgments

- **Qt Framework**: For providing a powerful and cross-platform framework for building GUI applications.
- **CMake**: For simplifying the build process across different platforms.
