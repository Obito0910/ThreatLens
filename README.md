# 📖 ThreatLens — Complete Usage Guide

> A step-by-step guide to using every feature of ThreatLens Malware Analysis Simulator

---

## 📋 Table of Contents

- [Starting the Program](#-starting-the-program)
- [Login](#-login)
- [Main Menu](#-main-menu)
- [Analyze a File](#-1-analyze-a-file)
- [View Last Result](#-2-view-last-analysis-result)
- [Generate Report](#-3-generate-report)
- [View Statistics](#-4-view-global-statistics)
- [View History](#-5-view-my-analysis-history)
- [Quarantine a File](#-6-quarantine-a-file)
- [View Quarantine List](#-7-view-quarantine-list)
- [Logout & Exit](#-8-logout--9-exit)
- [Understanding Results](#-understanding-results)
- [File Locations](#-file-locations)
- [Common Errors](#-common-errors)

---

## 🚀 Starting the Program

Open **PowerShell** or **CMD** inside the ThreatLens folder and run:

```powershell
.\ThreatLens.exe
```

You will see the banner and system initialization:

```
  ***************************************************************************************
 ████████╗██╗  ██╗██████╗ ███████╗ █████╗ ████████╗    ██╗     ███████╗███╗   ██╗███████╗
 ╚══██╔══╝██║  ██║██╔══██╗██╔════╝██╔══██╗╚══██╔══╝    ██║     ██╔════╝████╗  ██║██╔════╝
    ██║   ███████║██████╔╝█████╗  ███████║   ██║       ██║     █████╗  ██╔██╗ ██║███████╗
    ██║   ██╔══██║██╔══██╗██╔══╝  ██╔══██║   ██║       ██║     ██╔══╝  ██║╚██╗██║╚════██║
    ██║   ██║  ██║██║  ██║███████╗██║  ██║   ██║       ███████╗███████╗██║ ╚████║███████║
    ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝   ╚═╝       ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝
  ***************************************************************************************
  +-------------------------------------------------------+
  |        MALWARE ANALYSIS SIMULATOR  v1.0               |
  |        OOP Lab Semester Project                       |
  +-------------------------------------------------------+

============================================================
               SYSTEM INITIALIZATION
============================================================
[>] Initializing logger...
[✓] Logger initialized
[>] Loading authentication system...
[✓] Loaded 5 users
[>] Initializing analysis engine...
[✓] Engine initialized with 4 analyzers
[>] Initializing report generator...
[✓] Report generator ready
[>] Initializing quarantine manager...
[✓] Quarantine manager ready
[✓] System initialized successfully!

Press Enter to continue...
```

Press **Enter** to proceed to login.

---

## 🔐 Login

After startup you will see the **Welcome Menu**:

```
============================================================
                       WELCOME
============================================================
[i] Please login to access the system
------------------------------------------------------------
  1. Login
  2. Exit
------------------------------------------------------------
Choice:
```

Type `1` and press Enter, then enter your credentials:

```
============================================================
                      USER LOGIN
============================================================
Username: john_doe
Password: password123
```

### ✅ Successful Login

```
[✓] Login successful!
Welcome:   john_doe
Role:      Senior Analyst
```

### ❌ Failed Login

```
[✗] Login failed: Authentication Error: Invalid password for user: john_doe
```

> Try again with correct credentials. See the credentials table below.

### 🔑 Available Accounts

| Username | Password | Role |
|----------|----------|------|
| `admin` | `admin123` | Administrator |
| `john_doe` | `password123` | Senior Analyst |
| `alice` | `alice456` | Analyst |
| `bob` | `bob789` | Junior Analyst |
| `test_user` | `test` | Analyst |

---

## 🏠 Main Menu

After login you will see the main menu with your account info:

```
============================================================
                      MAIN MENU
============================================================
User:                john_doe
Role:                Senior Analyst
Analyses:            0
------------------------------------------------------------
  1. Analyze File
  2. View Last Analysis Result
  3. Generate Report
  4. View Global Statistics
  5. View My Analysis History
  6. Quarantine Last Analyzed File
  7. View Quarantine List
  8. Logout
  9. Exit
------------------------------------------------------------
Choice:
```

---

## 🔬 1. Analyze a File

**Choose option `1` from the main menu.**

```
============================================================
                     FILE ANALYSIS
============================================================
Enter file path:
```

Type the path to the file you want to analyze:

```
Enter file path: samples/suspicious_sample.txt
```

### What Happens Next

The system runs **4 analyzers** on the file one by one:

```
[✓] File loaded: suspicious_sample.txt
Size: 516 bytes

[>] Running analysis...

========================================
   STARTING ANALYSIS
========================================
User:      john_doe
File:      suspicious_sample.txt
Analyzers: 4
========================================

[AnalysisEngine] Running: Hash Analyzer...
[HashAnalyzer] Hash: 53312314

[AnalysisEngine] Running: String Analyzer...
[StringAnalyzer] Found 7 suspicious strings (Risk +70)

[AnalysisEngine] Running: Signature Analyzer...
[SignatureAnalyzer] File hash clean (not in database)

[AnalysisEngine] Running: Metadata Analyzer...
[MetadataAnalyzer] No suspicious metadata detected
```

### Analysis Result Display

```
============================================================
                  ANALYSIS RESULTS
============================================================
File:                suspicious_sample.txt
Hash:                53312314
Risk Score:          70 / 100  [████████████████████████░░░░░░░░]
Verdict:             DANGEROUS

------------------------------------------------------------
Findings (10):

  1. Hash computed: 53312314
  2. Suspicious string found: "- cmd.exe"
  3. Suspicious string found: "- powershell"
  4. Suspicious string found: "- registry"
  5. Suspicious string found: "- keylogger"
  6. Suspicious string found: "- download from http://malicious-site.com"
  7. Suspicious string found: "- socket connection"
  8. Suspicious string found: "- CreateRemoteThread API"
  9. No matching malware signatures found
  10. File extension: .txt (acceptable)
```

### Testing With Sample Files

| File | Expected Verdict |
|------|-----------------|
| `samples/safe_sample.txt` | ✅ SAFE (Risk: 0) |
| `samples/suspicious_sample.txt` | 🚨 DANGEROUS (Risk: 70) |

---

## 📊 2. View Last Analysis Result

**Choose option `2` from the main menu.**

Displays the full result of the **most recently analyzed file** without re-running analysis.

```
============================================================
               LAST ANALYSIS RESULT
============================================================
File:                suspicious_sample.txt
Hash:                53312314
Timestamp:           2026-05-14 00:04:37
Risk Score:          70 / 100  [████████████████████████░░░░░░░░]
Verdict:             DANGEROUS

------------------------------------------------------------
Findings (10):
  1. Hash computed: 53312314
  2. Suspicious string found: "- cmd.exe"
  ...
```

> ⚠️ If no analysis has been done yet, you will see:
> ```
> [!] No analysis has been performed yet.
> ```

---

## 📝 3. Generate Report

**Choose option `3` from the main menu.**

Saves a **detailed text report** of the last analysis to the `reports/` folder.

```
============================================================
                  REPORT GENERATION
============================================================
[>] Generating detailed report...
[✓] Report generated successfully!
Location:            reports/suspicious_sample_20260514_000611_report.txt
```

### What's Inside the Report File

```
============================================
        MALWARE ANALYSIS REPORT
============================================

ANALYST INFORMATION
-------------------------------------------
Analyst:       john_doe
Role:          Senior Analyst
Analysis Date: 2026-05-14 00:04:37

FILE INFORMATION
-------------------------------------------
File Name:     suspicious_sample.txt
File Size:     516 bytes
File Hash:     53312314

ANALYSIS RESULTS
-------------------------------------------
Risk Score:    70 / 100
Verdict:       DANGEROUS
Total Findings: 10

DETAILED FINDINGS
-------------------------------------------
1. Hash computed: 53312314
2. Suspicious string found: "- cmd.exe"
...

RISK ASSESSMENT
-------------------------------------------
Risk Level: HIGH
This file shows strong indicators of malicious behavior.

RECOMMENDATIONS
-------------------------------------------
- DO NOT execute this file.
- IMMEDIATELY quarantine the file.
- Scan the system for additional malware.
- Review system logs for signs of compromise.
- Change passwords if sensitive data may be exposed.
- Report to security team immediately.

============================================
        END OF REPORT
============================================
```

> 📁 All reports are saved in the `reports/` folder with a timestamp in the filename.

---

## 📈 4. View Global Statistics

**Choose option `4` from the main menu.**

Shows system-wide cumulative statistics:

```
============================================================
                  GLOBAL STATISTICS
============================================================
Files Analyzed:      3
Threats Detected:    2
Total Bytes:         1511
Log Entries:         14
Registered Users:    5
Quarantined Files:   1
Threat Rate:         66 / 100
```

| Stat | Meaning |
|------|---------|
| Files Analyzed | Total files analyzed since startup |
| Threats Detected | Files with risk score > 20 |
| Total Bytes | Total data processed |
| Log Entries | Total lines written to analysis.log |
| Threat Rate | Percentage of files flagged as threats |

---

## 🕐 5. View My Analysis History

**Choose option `5` from the main menu.**

Shows **your personal** analysis history (last 50 analyses):

```
============================================================
               MY ANALYSIS HISTORY
============================================================
Total Analyses:      2

------------------------------------------------------------
Recent Analyses:

1. suspicious_sample.txt - DANGEROUS  (Risk: 70)
2. safe_sample.txt       - SAFE       (Risk: 0)
```

> Each user has their own independent history. Logging out does not erase it within the same session.

---

## 🗃️ 6. Quarantine a File

**Choose option `6` from the main menu.**

Attempts to quarantine the last analyzed file.

### ✅ Successful Quarantine (DANGEROUS files only)

```
============================================================
                   QUARANTINE FILE
============================================================
[>] Attempting to quarantine file...

[✓] File has been quarantined successfully!
File:                suspicious_sample.txt
Quarantined by:      john_doe
```

### ❌ Quarantine Denied (SAFE or SUSPICIOUS files)

```
[!] File was not quarantined (not dangerous enough)
Verdict:             SAFE
[i] Only DANGEROUS files can be quarantined
```

> The quarantine action is **logged** in `logs/quarantine.log` automatically.

---

## 📋 7. View Quarantine List

**Choose option `7` from the main menu.**

Shows all currently quarantined files:

```
============================================================
                  QUARANTINED FILES
============================================================
Total Quarantined:   1

------------------------------------------------------------
1. samples/suspicious_sample.txt
```

> If no files are quarantined:
> ```
> [i] No files in quarantine.
> ```

---

## 🚪 8. Logout / 9. Exit

### Logout (Option 8)
Logs out the current user and returns to the Welcome/Login screen. The engine and statistics are **preserved**.

```
[✓] Logged out successfully
```

### Exit (Option 9)
Shuts down the entire system and exits the program.

```
============================================================
                  SYSTEM SHUTDOWN
============================================================
[>] Cleaning up resources...
[✓] System shutdown complete
[✓] Thank you for using Malware Analysis Simulator!
```

---

## 🎯 Understanding Results

### Risk Score Breakdown

```
  0 ────────────────────────────────────── 100
  │         │              │               │
  ▼         ▼              ▼               ▼
SAFE     SAFE          SUSPICIOUS      DANGEROUS
 0        20              50              100
```

### How Risk Score is Calculated

| Analyzer | Max Risk Added | Trigger |
|----------|---------------|---------|
| String Analyzer | +10 per match | Each suspicious keyword found |
| Metadata Analyzer | +20 | Dangerous file extension |
| Metadata Analyzer | +15 | Suspicious filename pattern |
| Metadata Analyzer | +10 | Suspicious file size |
| Signature Analyzer | +50 | Known malware hash match |

### Verdict Colors in Terminal

```
✅ SAFE       → Green
⚠️ SUSPICIOUS → Yellow
🚨 DANGEROUS  → Red
```

---

## 📂 File Locations

| File/Folder | Purpose |
|-------------|---------|
| `data/users.txt` | User credentials database |
| `data/signatures.txt` | Known malware hash signatures |
| `data/suspicious_strings.txt` | Suspicious keyword patterns |
| `data/dangerous_extensions.txt` | Blacklisted file extensions |
| `logs/analysis.log` | Full analysis audit log |
| `logs/quarantine.log` | Quarantine event log |
| `reports/` | Generated analysis reports |
| `samples/` | Test files for analysis |

---

## ⚠️ Common Errors

| Error | Cause | Fix |
|-------|-------|-----|
| `File Open Error: Cannot open file` | Wrong file path | Check the path and try again |
| `Authentication Error: User not found` | Wrong username | Check `data/users.txt` for valid users |
| `Authentication Error: Invalid password` | Wrong password | Re-enter the correct password |
| `No analysis has been performed yet` | Option 2/3/6 used before analyzing | Run option 1 first |
| `File was not quarantined` | File verdict is not DANGEROUS | Only DANGEROUS files can be quarantined |
| `Cannot create report file` | `reports/` folder missing | Run `mkdir reports` in the project folder |
| `Logger Failed to initialize` | `logs/` folder missing | Run `mkdir logs` in the project folder |

---

## 💡 Quick Tips

- Always **analyze first** (option 1) before generating reports or quarantining
- Use `samples/safe_sample.txt` to test a **clean** file analysis
- Use `samples/suspicious_sample.txt` to test a **dangerous** file analysis
- Reports are saved with **timestamps** so you won't overwrite old ones
- The **logs/analysis.log** file keeps a permanent record of everything
- Add your own keywords to `data/suspicious_strings.txt` to customize detection

---

<div align="center">

**🛡️ ThreatLens — Analyze. Detect. Protect.**

[Back to README](README.md) • [GitHub](https://github.com/Obito0910/ThreatLens)

</div>
