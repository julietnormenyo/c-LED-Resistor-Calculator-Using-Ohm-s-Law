Group--2.7
LED Resistor Value Calculator

A simple C++98 console application that calculates the current-limiting resistor, power dissipation, and safety status for LED circuits. It also generates a detailed report and saves it to a .txt file.
About

This project was built for Analog Electronics / Circuit Design to automate LED resistor calculations and validate if a design is safe to use with standard components.

Instead of doing manual math for every LED, this tool handles:

    Resistor calculation
    Power rating with safety factor
    Validity + Current + Power safety checks
    Multi-LED batch processing
    Automatic report export

Features

    Resistor Calculation: R = (Vs - Vf) / I
    Power Calculation: P = (Vs - Vf) * I with 2x safety factor
    2 New Safety Checks:

    Resistor Validity: Valid | Design accepted if R > 0
    LED Current Check: Unsafe! if current > 30mA

    Batch Mode: Calculate up to 10 LEDs in one run
    File Export: Saves all results to LED_Resistor_Report.txt
    Input Validation: Rejects invalid inputs like Vs <= Vf or I <= 0
    C++98 Compatible: Uses only standard library, no external dependencies

Tech Stack

    Language: C++98
    Libraries: <iostream>, <fstream>, <cmath>, <vector>, <iomanip>
    Platform: Windows / Linux / Mac

Getting Started

    Compile Using g++:bashg++ main.cpp -o LEDCalculatorUsing Dev-C++, Code::Blocks, or VS: Just open main.cpp and build.

    RUN bash./LEDCalculator

EXAMPLE OUTPUT ========== LED CIRCUIT DESIGN REPORT #1 ========== LED Label/Colour : White LED Supply Voltage (Vs) : 80.00 V LED Forward Voltage : 22.00 V Desired LED Current : 21.00 mA
Calculated Resistor : 2761.90 Ohms Min Power Dissipated: 1.22 W Recommended Power : 3.00 W resistor
Validity : Valid | Design accepted LED Current Status : Safe Overall Safety : REQUIRING REVIEW

Report saved successfully to 'LED_Resistor_Report.txt'

FILE STRUCTURE LED-Resistor-Calculator/ │ ├── main.cpp # Source code ├── LED_Resistor_Report.txt # Auto-generated report ├── README.md # This file

SAFETY NOTES Standard 5mm LEDs are typically rated for 20mA. This tool flags anything >30mA as Unsafe!Always choose a resistor wattage >= 2x the calculated power dissipation.This tool is for educational and prototyping use. Always double-check with a datasheet. LicenseThis project is licensed under the MIT License - free to use for learning and personal projects.

AUTHOR: GROUP 2.7 INTRODUCTION TO COMPUTER PROGRAMMING (C++) BEE 208
Suggested Role

Odoom Bright (01242600B) - Project lead
Dorcas Asamoah Kissi (01244084B) - Algorithm writer 
Michael Osei Bokor (01246900B) - Pseudocode writer
Awudu Wuzeima (01243137B) - Flowchart designer
Aboagye Jonas Frimpong (01241449B) - C++ programmer
Monney Christopher (01243455B) - C++ programmer
Ayitey Aaron (01246383B) - Testing lead 
Juliet Normenyo (01244425B) - GitHub manager
Oppong Duah Immanuel (01243256B) - Documentation lead
Naa Larley Aba Lartey Perida (01245581B) - Presentation lead
