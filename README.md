# 🏋️‍♂️ SGP – Sistema di Gestione Palestra

> A modular C CLI application designed for managing gym subscriptions, lessons, and bookings, built with dynamic data structures and automated oracle-based testing.

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![JSON](https://img.shields.io/badge/json-5E5C5C?style=for-the-badge&logo=json&logoColor=white)
![GNU Make](https://img.shields.io/badge/GNU%20Make-0A0A0A.svg?style=for-the-badge&logo=GNU-Make&logoColor=white)

## 📖 Table of Contents
- [About the Project](#about-the-project)
- [Educational Goals](#educational-goals)
- [Key Features](#key-features)
- [Data Architecture & Persistence](#data-architecture--persistence)
- [Testing Architecture](#testing-architecture)
- [Getting Started](#getting-started)
- [Authors & License](#authors--license)

## <a id="about-the-project"></a>🚀 About the Project
**SGP (Sistema di Gestione Palestra)** is a terminal-based (CLI) management system developed in C. It provides a robust core for handling the daily operations of a gym, allowing administrators to track client subscriptions, schedule lessons, and generate monthly operational reports.

Developed as the final project for the *Programmazione e Strutture Dati* (Programming and Data Structures) course at the **University of Salerno**.

## <a id="educational-goals"></a>🎓 Educational Goals
The project was engineered to apply fundamental computer science concepts in a low-level environment:
- **Dynamic Memory Management:** Safe allocation and deallocation of memory to prevent leaks.
- **Complex Data Structures:** Extensive use of Linked Lists and Binary Search Trees (BSTs) to optimize data retrieval and storage.
- **Modularity:** Strict separation of concerns across different C modules and headers.
- **Automated QA:** Implementation of an automated testing suite comparing outputs against Oracle files.

## <a id="key-features"></a>✨ Key Features
- **Client & Subscription Management:** Register new clients and systematically verify the validity of their memberships.
- **Advanced Booking System:** Allow clients to make reservations with built-in business logic to prevent double-bookings and handle full classes.
- **Automated JSON Reporting:** Generate comprehensive monthly activity reports, serialized automatically into structured JSON format.

## <a id="data-architecture--persistence"></a>🗄️ Data Architecture & Persistence
- **Centralized Data Access:** All JSON parsing and serialization logic is strictly confined to the `Persistenza_Dati` module.
- **cJSON Integration:** The application uses the bundled **cJSON** library to serialize C structs (like Lists and Trees) into structured JSON files.
- **Dedicated Data Stores:** Information is persistently saved in distinct JSON databases: `Clienti.json`, `Lezioni.json`, and `Prenotazioni.json`.

## <a id="testing-architecture"></a>🧪 Testing Architecture
The repository is split into two main branches to separate production code from quality assurance. 
The `test` branch houses an automated suite verifying three macro-components:
1. **Clients:** Insertion, validation, and duplicate handling.
2. **Bookings:** Data correctness, nonexistent clients, and schedule availability.
3. **Reports:** Monthly generation, JSON structure, and data coherence.

*Every test run saves logs in the `esiti/` directory and automatically compares the application's output with pre-verified **Oracle files**.*

## <a id="getting-started"></a>🛠️ Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites
- A C compiler like `GCC` or `Clang`.
- `Make` installed on your system.

### Installation & Execution

1. **Clone the repository:**
   ```sh
   git clone https://github.com/ZSR22/sgp-gym-manager.git
   cd sgp-gym-manager
   ```

2. **Production Mode (`main` branch):**
   ```sh
   git checkout main
   make        # Compiles all source files into the 'SGP' executable
   make run    # Compiles and directly executes the CLI application
   ```

3. **Testing Mode (`test` branch):**
   ```sh
   git checkout test
   make test   # Compiles the 'SGP_TEST' executable and runs the test suite
   ```

4. **Clean Build:**
   ```sh
   make clean  # Cleans up executables, object files, and logs
   ```

## <a id="authors--license"></a>👨‍💻 Authors & License

- **Gianmarco Raimondi** 
- **Salvatore Zurino**

*B.Sc. Computer Science - University of Salerno (June 2025).*

**Disclaimer:** This project was developed solely for educational purposes and academic evaluation. It is not intended for commercial distribution or production environments.