# 📚 Library Book Management System

> A comprehensive **Data Structures & Algorithms** mini project built in C — implementing 8 data structures, 6 sorting algorithms, and 3 searching techniques inside a single, unified library management application.

---

## 🗂️ Table of Contents

- [About the Project](#-about-the-project)
- [Data Structures Implemented](#-data-structures-implemented)
- [Algorithms Implemented](#-algorithms-implemented)
- [Features](#-features)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Menu Overview](#-menu-overview)
- [Project Structure](#-project-structure)
- [Time Complexity Summary](#-time-complexity-summary)
- [Sample Output](#-sample-output)
- [Course Syllabus Coverage](#-course-syllabus-coverage)
- [License](#-license)

---

## 🔍 About the Project

This project was built as a **DSA mini project** for the subject *Data Structures and Algorithms*. Instead of isolated examples, every data structure and algorithm from the syllabus is integrated into a single working **Library Book Management System** — showing how multiple structures work together in a real-world scenario.

A library administrator can add/delete books, search by ID or title, browse interactively, manage a waitlist, sort the collection, get genre recommendations, and much more — all driven by the appropriate underlying data structure.

---

## 🧱 Data Structures Implemented

| # | Data Structure | Role in This Project |
|---|---------------|----------------------|
| 1 | **Array** | Stores book genre categories |
| 2 | **Singly Linked List** | Master book list — add, delete, traverse |
| 3 | **Doubly Linked List** | Interactive book browser (forward / backward) |
| 4 | **Stack (ADT)** | Recently viewed books + string reversal + postfix eval |
| 5 | **Queue (ADT)** | Member waitlist using circular array |
| 6 | **Binary Search Tree** | Fast O(log n) search by Book ID |
| 7 | **Hash Table** | O(1) average title lookup with separate chaining |
| 8 | **Graph** | Genre recommendation graph with DFS and BFS |

---

## ⚙️ Algorithms Implemented

### Sorting
| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) |

### Searching
| Algorithm | Time Complexity | Prerequisite |
|-----------|----------------|--------------|
| Linear Search | O(n) | None |
| Binary Search | O(log n) | Sorted array |
| Hash-based Search | O(1) avg | Hash table |

### Other
- **Recursion** — BST insert, BST search, inorder / preorder / postorder traversals, recursive DFS
- **Graph Traversal** — DFS (recursive) and BFS (iterative with queue)
- **Stack Applications** — String reversal, Postfix (Polish Notation) expression evaluation
- **Collision Resolution** — Separate chaining in Hash Table

---

## ✨ Features

- 📖 Add, delete, and display books using a **Singly Linked List**
- ↔️ Browse books forward and backward with a **Doubly Linked List**
- 🔍 Search by Book ID using a **Binary Search Tree** (recursive)
- 🔎 Search by title using a **Hash Table** (O(1) avg lookup)
- 🕓 Track recently viewed books with a **Stack**
- 📋 Manage member waitlists with a **Queue** (circular array)
- 📊 Sort books using all **6 sorting algorithms** with a single menu
- 🌐 Explore related genres via **Graph DFS and BFS**
- 🌳 View BST **inorder, preorder, postorder** traversals
- 🔁 **Reverse strings** and **evaluate postfix expressions** using a Stack
- 💾 Pre-loaded with 7 sample books on startup

---

## 🚀 Getting Started

### Prerequisites

- GCC compiler (any version supporting C99 or later)
- Linux / macOS / Windows (with MinGW or WSL)

### Installation

```bash
# Clone the repository
git clone https://github.com/your-username/library-book-management-dsa.git

# Navigate into the project folder
cd library-book-management-dsa

# Compile
gcc -Wall -o library library_management.c

# Run
./library
```

On **Windows** with MinGW:
```bash
gcc -Wall -o library.exe library_management.c
library.exe
```

---

## 💻 Usage

On launch, the program loads 7 sample books and presents an interactive menu. All operations are menu-driven — just enter the option number and follow the prompts.

```
  ╔══════════════════════════════════════════════════════╗
  ║         LIBRARY BOOK MANAGEMENT SYSTEM              ║
  ║     Mini Project — Data Structures & Algorithms     ║
  ╚══════════════════════════════════════════════════════╝

  Loading sample data ...
  7 sample books loaded.
```

---

## 📋 Menu Overview

```
  ┌─────────────────────────── MENU ───────────────────────────┐
  │  1.  Add Book                (Linked List + BST + Hash)    │
  │  2.  Delete Book             (Linked List)                 │
  │  3.  Display All Books       (Singly Linked List)          │
  │  4.  Browse Books            (Doubly Linked List)          │
  │  5.  Search by ID            (Binary Search Tree)          │
  │  6.  Search by Title         (Hash Table)                  │
  │  7.  Recently Viewed Books   (Stack ADT)                   │
  │  8.  Waitlist Management     (Queue ADT)                   │
  │  9.  Sort Books              (6 Sorting Algorithms)        │
  │  10. Search by ID            (Linear / Binary Search)      │
  │  11. BST Traversals          (Recursion)                   │
  │  12. Genre Recommendations   (Graph DFS / BFS)             │
  │  13. Stack Applications      (String Reverse / Postfix)    │
  │  14. Display Categories      (Array)                       │
  │   0. Exit                                                  │
  └────────────────────────────────────────────────────────────┘
```

---

## 📁 Project Structure

```
library-book-management-dsa/
│
├── library_management.c      # Complete source code (single file)
├── README.md                 # This file
└── DSA_Mini_Project_Report.docx  # Full project report
```

The single C file is organised into clearly commented sections:

```
library_management.c
├── Constants & Macros
├── Book Structure (shared typedef)
├── [1] Array — Genre Categories
├── [2] Singly Linked List
├── [3] Doubly Linked List
├── [4] Stack ADT + Applications
├── [5] Queue ADT
├── [6] Binary Search Tree (recursive)
├── [7] Hash Table (chaining)
├── Sorting Algorithms (×6)
├── Searching Algorithms (×2)
├── [8] Graph — DFS & BFS
├── Sample Data Loader
└── Main Menu Controller
```

---

## ⏱️ Time Complexity Summary

| Operation | Data Structure | Complexity |
|-----------|---------------|------------|
| Add book | Singly Linked List (head insert) | O(1) |
| Delete book | Singly Linked List | O(n) |
| Search by ID | Binary Search Tree | O(log n) avg |
| Search by title | Hash Table | O(1) avg |
| Linear Search | Array | O(n) |
| Binary Search | Sorted Array | O(log n) |
| BST Traversal | BST (recursive) | O(n) |
| Genre DFS / BFS | Graph | O(V + E) |
| Merge / Heap Sort | Array | O(n log n) |
| Bubble / Select Sort | Array | O(n²) |

---

## 🖥️ Sample Output

### Display All Books
```
  ID    Title                            Author                 Genre        Price   Status
  ----  -----                            ------                 -----        -----   ------
  107   Atomic Habits                    James Clear            Self-Help    379.00  Available
  106   A Brief History of Time          Stephen Hawking        Science      450.00  Available
  105   Harry Potter & Sorcerer's Stone  J.K. Rowling           Fantasy      399.00  Available
  104   Murder on the Orient Express     Agatha Christie        Mystery      349.00  Issued
  103   Sapiens                          Yuval Noah Harari      History      499.00  Available
  102   Clean Code                       Robert C. Martin       Technology   599.00  Available
  101   The Great Gatsby                 F. Scott Fitzgerald    Fiction      299.00  Available
```

### BST Inorder Traversal (sorted by ID)
```
  [101] The Great Gatsby
  [102] Clean Code
  [103] Sapiens
  [104] Murder on the Orient Express
  [105] Harry Potter & Sorcerer's Stone
  [106] A Brief History of Time
  [107] Atomic Habits
```

### Genre Recommendation — DFS from Fiction
```
  DFS from 'Fiction':
  -> Fiction
  -> Mystery
  -> Romance
  -> Fantasy

  BFS Genre Traversal:
  -> Fiction  -> Mystery  -> Fantasy  -> Romance
```

### Stack Application — Postfix Evaluation
```
  Enter postfix (e.g. 3 4 + 2 *): 3 4 + 2 *
  Result = 14
```

---

## 📘 Course Syllabus Coverage

| Syllabus Topic | Implemented As |
|---------------|----------------|
| Linear Data Structures | Array, Stack, Queue, Singly LL, Doubly LL |
| Non-Linear Data Structures | BST, Graph |
| Stack as ADT | `Stack` struct with push/pop/peek |
| Stack Applications | String reversal, Postfix (Polish Notation) evaluation |
| Queue as ADT | `Queue` struct with circular array |
| Linear representation of Queue | Circular array with front/rear/size |
| Singly Linked List | Master book list |
| Doubly Linked List | Book browser |
| Linked representation of Stack/Queue | (via chaining in Hash Table nodes) |
| Binary Search Tree | Book search by ID, all 3 traversals |
| Graph Representation | Adjacency matrix (10×10) |
| Graph Traversal (DFS) | Recursive DFS on genre graph |
| Graph Traversal (BFS) | Iterative BFS with integer queue |
| Recursion | BST insert, BST search, all BST traversals, DFS |
| Bubble Sort | `bubbleSort()` |
| Selection Sort | `selectionSort()` |
| Insertion Sort | `insertionSort()` |
| Quick Sort | `quickSort()` with Lomuto partition |
| Merge Sort | `mergeSort()` with auxiliary arrays |
| Heap Sort | `heapSort()` with `heapify()` |
| Linear Search | `linearSearch()` |
| Binary Search | `binarySearch()` on sorted array |
| Hashing & Hash Functions | Polynomial rolling hash, mod prime 53 |
| Collision Resolution | Separate chaining (linked list per bucket) |
| Time & Space Complexity | Documented per function and in report |
| Asymptotic Notations | O(1), O(log n), O(n), O(n log n), O(n²), O(V+E) |

---

## 📄 License

This project is submitted as an academic mini project for educational purposes.  
Feel free to use, modify, and extend it for learning.

---

<div align="center">
  <sub>Built with ❤️ for the DSA course | C Language | Single-file implementation</sub>
</div>
