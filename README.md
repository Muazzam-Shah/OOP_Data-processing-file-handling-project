# OOP_Data-processing-file-handling-project

## Overview

This project is an Object-Oriented Programming (OOP) application written in C++ that processes student and course data from Lahore and Peshawar campuses. It reads data from multiple text files, standardizes and aggregates the data, and generates various statistical reports. The project demonstrates the use of classes, file handling, and data processing techniques in C++.

## Features

- **Data Parsing:** Reads and parses student and course details from several input files.
- **Data Standardization:** 
  - Converts date formats (e.g., "DD-MM-YY" to "DD-Mon-YY").
  - Standardizes city names using predefined mappings.
- **Gender-based Name Extraction:** Extracts first names from student names and writes them into gender-specific files (`malenames.txt` and `femalenames.txt`).
- **Data Aggregation:** Combines individual data files into unified files:
  - `AllStudents.txt` for student data.
  - `AllDetails.txt` for course details.
- **Statistical Reporting:** Calculates and displays statistics such as:
  - Unique values and null counts in various columns.
  - Gender ratios (male vs. female).
  - Count of students taking more than five courses.
  - Campus-specific and combined analysis for Lahore and Peshawar.

## File Structure

- **Source Code:**
  - The main C++ source file contains the implementation.
  
- **Input Files:**
  - **Lahore Student Files:**  
    `Lhr_Student_94.txt`, `Lhr_Student_95.txt`, `Lhr_Student_96.txt`, `Lhr_Student_97.txt`, `Lhr_Student_98.txt`, `Lhr_Student_99.txt`, `Lhr_Student_100.txt`, `Lhr_Student_101.txt`, `Lhr_Student_102.txt`, `Lhr_Student_103.txt`, `Lhr_Student_104.txt`, `Lhr_Student_MS_101.txt`, `Lhr_Student_MS_102.txt`, `Lhr_Student_MS_103.txt`, `Lhr_Student_MS_104.txt`, `Transfer.txt`
  
  - **Lahore Course Files:**  
    `Lhr_Detail_94.txt`, `Lhr_Detail_95.txt`, `Lhr_Detail_96.txt`, `Lhr_Detail_97.txt`, `Lhr_Detail_98.txt`, `Lhr_Detail_99.txt`, `Lhr_Detail_100.txt`, `Lhr_Detail_101.txt`, `Lhr_Detail_102.txt`, `Lhr_Detail_103.txt`, `Lhr_Detail_104.txt`, `Lhr_Detail_MS_101.txt`, `Lhr_Detail_MS_102.txt`, `Lhr_Detail_MS_103.txt`, `Lhr_Detail_MS_104.txt`
  
  - **Peshawar Student Files:**  
    `BS_P_94_Student.txt`, `BS_P_95_Student.txt`, `BS_P_96_Student.txt`, `BS_P_97_Student.txt`, `BS_P_98_Student.txt`, `BS_P_99_Student.txt`, `BS_P_100_Student.txt`, `BS_P_101_Student.txt`, `BS_P_102_Student.txt`, `BS_P_103_Student.txt`, `BS_P_104_Student.txt`, `MS_P_101_Student.txt`, `MS_P_102_Student.txt`, `MS_P_103_Student.txt`, `MS_P_104_Student.txt`
  
  - **Peshawar Course Files:**  
    `BS_P_94_Reg.txt`, `BS_P_95_Reg.txt`, `BS_P_96_Reg.txt`, `BS_P_97_Reg.txt`, `BS_P_98_Reg.txt`, `BS_P_99_Reg.txt`, `BS_P_100_Reg.txt`, `BS_P_101_Reg.txt`, `BS_P_102_Reg.txt`, `BS_P_103_Reg.txt`, `BS_P_104_Reg.txt`, `MS_P_101_Reg.txt`, `MS_P_102_Reg.txt`, `MS_P_103_Reg.txt`, `MS_P_104_Reg.txt`

- **Output Files:**
  - `AllStudents.txt` – Combined student data.
  - `AllDetails.txt` – Combined course details.
  - `malenames.txt` – Extracted first names of male students.
  - `femalenames.txt` – Extracted first names of female students.

## How to Compile and Run

### Prerequisites

- A C++ compiler (e.g., g++)

### Compilation

Open a terminal in the project directory and compile the code using the following command:

```bash
g++ -o StudentDataProcessor main.cpp
```

### Execution

After compiling, run the executable:

```bash
./StudentDataProcessor
```

The program will prompt you to select an option for statistical analysis:

1. **Statistics for Lahore:** Displays unique values, null counts, and other statistics for Lahore campus data.
2. **Statistics for Peshawar:** Displays similar statistics for Peshawar campus data.
3. **Combined Statistics:** Provides aggregated statistics from both campuses, including average counts per semester and per batch.

Follow the on-screen instructions to view the desired reports.

## Code Structure

- **Classes:**
  - **Student:**  
    Contains attributes such as student ID, name, father's name, gender, address, city, date of birth, registration date, registration status, degree status, and last degree.
  
  - **Course:**  
    Contains attributes such as student ID, degree, semester, course code, marks, and discipline.

- **Key Functions:**
  - **ConvertDate():**  
    Converts dates from a numeric format to one with month abbreviations.
  
  - **standardizeCityName():**  
    Converts city names to lowercase, applies mappings for known abbreviations, and then capitalizes them appropriately.
  
  - **writeToGenderFile():**  
    Extracts the first name from a student's full name and writes it to the corresponding gender file if it isn’t already present.
  
  - **countStudentsWithMoreThanFiveCourses():**  
    Counts the number of unique students enrolled in more than five courses.
  
- **Main Function:**  
  Orchestrates the process by reading input files, aggregating data, writing output files, and generating statistical reports based on user selection.

## Usage Instructions

1. **Prepare Input Files:**  
   Ensure that all the required input files are present in the same directory as the executable.
   
2. **Run the Application:**  
   Execute the program and select the desired statistical analysis option when prompted.
   
3. **Review Output:**  
   The program generates combined data files and prints statistical reports to the console.

## Conclusion

This project illustrates the application of object-oriented programming concepts in C++ for real-world data processing and analysis. It handles file I/O, string manipulation, data standardization, and statistical computations, providing a comprehensive solution for managing student and course data across multiple campuses.
