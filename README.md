# 📱 btOS — Lightweight Linux Mobile Environment

[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Qt5](https://img.shields.io/badge/Qt-5.15%20Widgets-41CD52?logo=qt&logoColor=white)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-064F8C?logo=cmake&logoColor=white)](https://cmake.org/)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Embedded-E95420?logo=linux&logoColor=white)](https://www.kernel.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

> **btOS** is an intentional, privacy-first mobile operating environment built in pure **C++17 and Qt Widgets**. Engineered to combat digital distraction and algorithmic addiction, btOS provides a deterministic, distraction-free handheld shell that runs efficiently on low-power Linux hardware.

---

## 🏗️ Systems Architecture

btOS is architected around a Model-View-Controller (MVC) design pattern. Presentation views never touch databases, network sockets, or window stacks.

### Core Architecture Pillars
1. **Dumb Presentation Views:** UI screens capture user gestures, render state, and emit intent signals (`applicationLaunchRequest`, `sendSmsRequested`). They hold zero business logic.
2. **Deterministic Lifecycle Coordinator (`btShell`):** Manages window stacks, coordinates view transitions, and controls app lifecycle transitions (`btAPP_SETUP()` on launch, `btAPP_CLOSED()` on exit).
3. **Hardware Services Layer (IPC & Daemons):** Persistent background services communicate with Linux system daemons over FreeDesktop D-Bus and handle asynchronous I/O without blocking the GUI thread.

---

## ✨ Features (In Progress)

### ✅  Minimalist Design System
* **Not based on CSS:** Uses modern QSS design with structured `theme` class for simplicity.
* **Mobile in mind:** Dynamic UI that can adapt to any screen size. 

### 🚧 Linux Cellular Integration (ModemManager via D-Bus)
* Integrates directly with `org.freedesktop.ModemManager1` over Linux D-Bus IPC.
* Asynchronously monitors incoming cellular SMS messages without polling.
* Capable of sending and receiving text messages over physical cellular basebands on Linux phone hardware.

### 🚧 On-Device Edge Intelligence (`llama.cpp`)
* Background worker thread hosting a quantized edge language model via `llama.cpp`.
* Performs local, zero-cloud on-device text summarization and smart replies.
* Complete data privacy: 100% offline, zero network telemetry, zero third-party cloud dependencies.

### 🚧 Decoupled Data Persistence (SQLite)
* Local SQLite relational database with parameterized queries (SQL injection immune).
* Thread-safe background persistence for SMS history, user preferences, and notes.

---

## 🛠️ Application Developer API

Writing an application for btOS is meant to be clean and modular. Every app subclasses `btApplication` and communicates with the shell through a dynamic lifecycle:

```cpp
#include "src/core/btApplication.h"
#include "src/ui/theme.h"

class NotesApp : public btApplication {
    Q_OBJECT
public:
    explicit NotesApp(QWidget* parent = nullptr) : btApplication(parent) {
        appName = "Notes";
    }

    void btAPP_SETUP() override {
        // Heavy UI tree allocated ONLY when launched
        application = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(application);

        QLabel* title = new QLabel("My Notes", application);
        Theme::markAsTitle(title);
        layout->addWidget(title);
    }

    QWidget* btAPP_RETURN() override { return application; }

    void btAPP_CLOSED() override {
        // Resources freed immediately upon exit
        delete application;
        application = nullptr;
    }

    QString returnAppName() override { return appName; }
};
```

---

## 🚀 Getting Started

### Prerequisites (Ubuntu / Debian / postmarketOS)

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    qtbase5-dev \
    libqt5widgets5 \
    libqt5dbus5 \
    libqt5sql5-sqlite
```

### Build & Run

```bash
# 1. Clone the repository
git clone https://github.com/darien-castro/btOS.git
cd btOS

# 2. Configure with CMake
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 3. Compile
cmake --build build -j$(nproc)

# 4. Launch btOS
./build/btOS
```

---

## 🗺️ Engineering Roadmap

| Phase | Milestone | Focus Areas | Status |
| :---: | :--- | :--- | :---: |
| **1** | **Decoupled Shell Core** | Event-driven navigation, 'dumb' applications, engineered lifecycles | **✅ Complete** |
| **2** | **UI Design** | QSS, cards | **✅ Complete** |
| **3** | **SQLite Storage Service** | Basic query capabilities, dynamic storage, reactive notes | **🟡 In Progress** |
| **4** | **ModemManager D-Bus** | Cellular SMS reception/dispatch via FreeDesktop D-Bus | **⚪ Planned** |
| **5** | **Edge AI Worker (`llama.cpp`)** | On-device quantized summarization on background worker thread | **⚪ Planned** |
| **6** | **Quality & CI/CD** | Automated `QTest` test suite + GitHub Actions CI workflow | **⚪ Planned** |

---

## 📄 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.
