<div align="center">

```
 ████████╗██╗  ██╗██████╗ ███████╗ █████╗ ████████╗    ██╗     ███████╗███╗   ██╗███████╗
 ╚══██╔══╝██║  ██║██╔══██╗██╔════╝██╔══██╗╚══██╔══╝    ██║     ██╔════╝████╗  ██║██╔════╝
    ██║   ███████║██████╔╝█████╗  ███████║   ██║       ██║     █████╗  ██╔██╗ ██║███████╗
    ██║   ██╔══██║██╔══██╗██╔══╝  ██╔══██║   ██║       ██║     ██╔══╝  ██║╚██╗██║╚════██║
    ██║   ██║  ██║██║  ██║███████╗██║  ██║   ██║       ███████╗███████╗██║ ╚████║███████║
    ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝       ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝
```

# 🛡️ ThreatLens — Malware Analysis Simulator

**A powerful, console-based malware analysis tool built in C++**

![C++](https://img.shields.io/badge/Language-C++11-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![OOP](https://img.shields.io/badge/Paradigm-OOP-brightgreen?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

*OOP Lab Semester Project — 2nd Semester*

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Project Structure](#-project-structure)
- [OOP Concepts](#-oop-concepts-demonstrated)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Analyzers](#-analyzers)
- [Sample Credentials](#-sample-credentials)
- [Screenshots](#-screenshots)
- [Contributors](#-contributors)

---

## 🔍 Overview

**ThreatLens** is a console-based malware analysis simulator developed in **C++11** that demonstrates core Object-Oriented Programming concepts. It simulates how real antivirus software analyzes suspicious files using multiple analysis techniques including hash computation, string pattern matching, signature detection, and metadata inspection.

> ⚠️ *This is an educational simulator. It does not perform real malware removal.*

---

## ✨ Features

| Feature | Description |
|--------|-------------|
| 🔐 **User Authentication** | Login/logout system with role-based access |
| 🔬 **Multi-Analyzer Engine** | 4 analyzers running in sequence |
| 📊 **Risk Scoring** | Dynamic 0–100 risk score with verdict |
| 📝 **Report Generation** | Detailed text reports saved to file |
| 🗃️ **Quarantine Manager** | Simulated quarantine for dangerous files |
| 📜 **Activity Logging** | Full audit trail of all actions |
| 🎨 **Colorful Console UI** | ANSI-colored output with ASCII banner |
| 📈 **Analysis History** | Per-user and global statistics tracking |

---

## 📁 Project Structure

```
ThreatLens/
│
├── 📂 src/                         # Source files
│   ├── main.cpp                    # Entry point
│   ├── AnalysisEngine.cpp          # Core orchestrator
│   ├── AnalysisResult.cpp          # Result container
│   ├── Analyzer.cpp                # Abstract base class
│   ├── HashAnalyzer.cpp            # Hash computation
│   ├── StringAnalyzer.cpp          # String pattern matching
│   ├── SignatureAnalyzer.cpp       # Signature database matching
│   ├── MetadataAnalyzer.cpp        # File metadata inspection
│   ├── AuthenticationManager.cpp   # User login/logout
│   ├── QuarantineManager.cpp       # File quarantine simulation
│   ├── ReportGenerator.cpp         # Report file generation
│   ├── Logger.cpp                  # Activity logging
│   ├── FileSample.cpp              # File representation
│   ├── User.cpp                    # User model
│   ├── ConsoleUI.cpp               # Colored console output
│   └── Exceptions.cpp              # Custom exceptions
│
├── 📂 include/                     # Header files
│   ├── History.h                   # Template history class
│   ├── Utility.h                   # Template utility functions
│   └── ...                         # All other headers
│
├── 📂 data/                        # Configuration data
│   ├── users.txt                   # User credentials
│   ├── signatures.txt              # Known malware signatures
│   ├── suspicious_strings.txt      # Suspicious keyword database
│   └── dangerous_extensions.txt    # Dangerous file extensions
│
├── 📂 samples/                     # Test files
│   ├── safe_sample.txt
│   └── suspicious_sample.txt
│
├── 📂 logs/                        # Auto-generated logs
│   ├── analysis.log
│   └── quarantine.log
│
├── 📂 reports/                     # Auto-generated reports
│
└── README.md
```

---

## 🧠 OOP Concepts Demonstrated

```
┌─────────────────────────────────────────────────────────────┐
│                    OOP CONCEPTS MAP                         │
├──────────────────────┬──────────────────────────────────────┤
│ Concept              │ Where Used                           │
├──────────────────────┼──────────────────────────────────────┤
│ Abstraction          │ Analyzer (pure virtual functions)    │
│ Inheritance          │ HashAnalyzer, StringAnalyzer, etc.   │
│ Polymorphism         │ analyze() called via base pointer    │
│ Encapsulation        │ Private members in all classes       │
│ Composition          │ AnalysisEngine owns Analyzer[]       │
│ Aggregation          │ ReportGenerator uses AnalysisResult  │
│ Templates            │ History<T>, Utility::clamp<T>        │
│ Operator Overloading │ +=, >, <, ==, <<                     │
│ Exception Handling   │ Custom exception hierarchy           │
│ Static Members       │ Counters in FileSample, Logger       │
│ Friend Functions     │ operator<< in AnalysisResult         │
│ Copy Constructor     │ FileSample, AnalysisResult, User     │
│ File I/O             │ Logger, ReportGenerator, data files  │
└──────────────────────┴──────────────────────────────────────┘
```

---

## 🚀 Getting Started

### Prerequisites

- **g++** with C++11 support (MinGW / MSYS2 on Windows)
- Windows Terminal or PowerShell (for colored output)

### Installation

```bash
# Clone the repository
git clone https://github.com/Obito0910/ThreatLens.git
cd ThreatLens

# Create required directories
mkdir logs reports
```

### Compilation

```powershell
g++ -std=c++11 -Wall -o ThreatLens.exe `
  src/Exceptions.cpp src/FileSample.cpp src/AnalysisResult.cpp `
  src/Analyzer.cpp src/HashAnalyzer.cpp src/StringAnalyzer.cpp `
  src/SignatureAnalyzer.cpp src/MetadataAnalyzer.cpp src/User.cpp `
  src/AnalysisEngine.cpp src/Logger.cpp src/ReportGenerator.cpp `
  src/AuthenticationManager.cpp src/QuarantineManager.cpp `
  src/ConsoleUI.cpp src/main.cpp -I./include
```

### Run

```powershell
.\ThreatLens.exe
```

---

## 🖥️ Usage

### Main Menu Options

```
  1. Analyze File              → Run all analyzers on a file
  2. View Last Analysis Result → See the most recent result
  3. Generate Report           → Save full report to file
  4. View Global Statistics    → System-wide analysis stats
  5. View My Analysis History  → Your personal history
  6. Quarantine Last File      → Quarantine dangerous files
  7. View Quarantine List      → See quarantined files
  8. Logout
  9. Exit
```

### Analyzing a File

```
Enter file path: samples/suspicious_sample.txt

[>] Running analysis...

Risk Score:   70 / 100  [████████████████████████░░░░░░░░░░░░░░░░]
Verdict:      DANGEROUS
```

---

## 🔬 Analyzers

```
┌─────────────────────┬────────────────────────────────────────────┐
│ Analyzer            │ What it does                               │
├─────────────────────┼────────────────────────────────────────────┤
│ 🔑 Hash Analyzer    │ Computes file checksum for identification   │
│ 🔍 String Analyzer  │ Searches for 28 suspicious keyword patterns │
│ 🧬 Signature Anal.  │ Matches hash against malware database       │
│ 📋 Metadata Anal.   │ Checks extension, size, filename patterns   │
└─────────────────────┴────────────────────────────────────────────┘
```

### Verdict System

| Risk Score | Verdict | Meaning |
|-----------|---------|---------|
| 0 – 20 | ✅ SAFE | File appears clean |
| 21 – 50 | ⚠️ SUSPICIOUS | Exercise caution |
| 51 – 100 | 🚨 DANGEROUS | Immediate action required |

---

## 🔑 Sample Credentials

| Username | Password | Role |
|----------|----------|------|
| `admin` | `admin123` | Administrator |

---

## 🏗️ Class Architecture

```
                    ┌─────────────┐
                    │   Analyzer  │  ← Abstract Base Class
                    │  (abstract) │
                    └──────┬──────┘
           ┌───────────────┼───────────────┐
    ┌──────▼──────┐ ┌──────▼──────┐ ┌──────▼──────┐ ┌──────▼──────┐
    │HashAnalyzer │ │StringAnalyz.│ │SignatureAnal│ │MetadataAnal.│
    └─────────────┘ └─────────────┘ └─────────────┘ └─────────────┘
           │                │
           └────────────────┘
                    │ uses (polymorphism)
           ┌────────▼────────┐        ┌──────────────┐
           │ AnalysisEngine  │◄───────│ FileSample   │
           │  (Composition)  │        └──────────────┘
           └────────┬────────┘
                    │ produces
           ┌────────▼────────┐
           │ AnalysisResult  │
           └────────┬────────┘
          ┌─────────┴──────────┐
   ┌──────▼──────┐    ┌────────▼────────┐
   │   Logger    │    │ ReportGenerator │
   └─────────────┘    └─────────────────┘
```

---

## 📄 License

This project is licensed under the **MIT License** — feel free to use it for educational purposes.

---

## 👨‍💻 Contributors

<div align="center">

| | |
|---|---|
| **Developer** | [@Obito0910](https://github.com/Obito0910) |
| **Project Type** | OOP Lab Semester Project |
| **Institution** | 2nd Semester — CYS |
| **Language** | C++11 |

</div>

---

<div align="center">

**⭐ Star this repo if you found it helpful!**

Made with ❤️ and lots of C++ 

</div>
