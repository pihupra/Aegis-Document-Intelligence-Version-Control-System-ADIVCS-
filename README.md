# Aegis Document Intelligence Version Control System (ADIVCS)

A professional C++ project implementing a **document version control system** with **CLI and Qt5 GUI**, powered by **SQLite**.  
ADIVCS demonstrates advanced **C++ programming**, database management, diff algorithms, and GUI integration — ideal for portfolios and job applications.

---

## **Overview**

ADIVCS allows users to **create documents, track multiple versions, and compare changes** efficiently.  
It combines a **robust backend** with a **modern Qt GUI frontend** and a **lightweight CLI interface**, enabling both interactive and terminal-based usage.  
The project uses **SQLite** for persistent storage, ensuring data is saved across sessions.

---

## **Features**

- **Document Management**: Create documents with metadata (title, author, tags).  
- **Version Control**: Add multiple versions of each document with timestamp tracking.  
- **Diff Functionality**: Compare any two versions using the **Myers/LCS diff algorithm** to highlight additions, deletions, and unchanged lines.  
- **Search Capability**: Search documents by title or tags using SQL `LIKE` queries.  
- **CLI Interface**: Lightweight terminal menu for quick operations.  
- **GUI Interface**: Qt5 interactive interface with buttons and dialogs for full functionality.  
- **Persistent Storage**: All documents and versions are stored in an **SQLite database** automatically.

---

## **Architecture**

The project is divided into **three main layers**:

1. **Storage Layer**  
   - Handles all database operations: create documents, add versions, search, and retrieve metadata.  
   - Uses SQLite3 for lightweight and reliable persistence.

2. **Versioning Layer**  
   - Manages version comparison and diff computation using the **Myers / LCS algorithm**.  
   - Returns detailed line-by-line differences for GUI or CLI display.

3. **Interface Layer**  
   - **CLI**: Provides a menu-based terminal interface for all operations.  
   - **Qt GUI**: Offers a modern graphical interface with dialogs for document creation, version addition, search, and diff visualization.

---

## **Build & Run Instructions**

### **CLI Version**

```bash
g++ src/*.cpp main.cpp -o aegis_cli -std=c++17 -lsqlite3
./aegis_cli
