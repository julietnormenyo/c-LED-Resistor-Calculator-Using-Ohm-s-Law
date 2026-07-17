#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

struct LEDReport {
    string ledLabel;
    double supplyVoltage;
    double ledForwardVoltage;
    double ledCurrent_mA;
    double resistorValue;
    double powerRating;
    string validityStatus; 
    string currentStatus; 
    string safetyStatus;
    string recommendation;
};

class LEDCalculator {
private:
    vector<LEDReport> reports;
    static const double POWER_SAFETY_FACTOR;

    string doubleToString(double val) {
        stringstream ss;
        ss << (int)ceil(val);
        return ss.str();
    }

    bool validateInputs(double Vs, double Vf, double I_mA) {
        if (Vs <= 0 || Vf <= 0 || I_mA <= 0) {
            return false;
        }
        if (Vs <= Vf) {
            return false;
        }
        return true;
    }

    void classifyDesign(double resistor, double I_mA, double power, LEDReport &rep) {
        
        if (resistor > 0) {
            rep.validityStatus = "Valid";
            rep.recommendation = "Design accepted";
        } else {
            rep.validityStatus = "Invalid!";
            rep.recommendation = "Design not accepted";
        }

        if (I_mA > 30) {
            rep.currentStatus = "Unsafe!";
            rep.safetyStatus = "UNSAFE";
            rep.recommendation = "Unsafe! LED current may be too high for a standard led";
        } 

        else if (resistor < 10) {
            rep.currentStatus = "Unsafe";
            rep.safetyStatus = "REQUIRING REVIEW";
            rep.recommendation = "Resistor value is very low. High current risk. Double check values.";
        } else if (power > 0.5) {
            rep.currentStatus = "Safe";
            rep.safetyStatus = "REQUIRING REVIEW";
            rep.recommendation = "Power dissipation is high. Use at least a " + 
                doubleToString(power * POWER_SAFETY_FACTOR) + "W resistor or reconsider current.";
        } else {
            rep.currentStatus = "Safe";
            rep.safetyStatus = "SAFE";
            rep.recommendation = "Design is within safe limits. Use a standard " + 
                doubleToString(power * POWER_SAFETY_FACTOR) + "W resistor.";
        }
    }

    void calculate(double Vs, double Vf, double I_mA, LEDReport &rep) {
        double I_A = I_mA / 1000.0;
        rep.resistorValue = (Vs - Vf) / I_A;
        rep.powerRating = (Vs - Vf) * I_A;
        classifyDesign(rep.resistorValue, I_mA, rep.powerRating, rep); 
    }

    void displayReport(const LEDReport &rep, int index) {
        cout << "\n========== LED CIRCUIT DESIGN REPORT #" << index + 1 << " ==========\n";
        cout << fixed << setprecision(2);
        cout << "LED Label/Colour : " << rep.ledLabel << "\n";
        cout << "Supply Voltage (Vs) : " << rep.supplyVoltage << " V\n";
        cout << "LED Forward Voltage : " << rep.ledForwardVoltage << " V\n";
        cout << "Desired LED Current : " << rep.ledCurrent_mA << " mA\n";
        cout << "---------------------------------------------------\n";
        cout << "Calculated Resistor : " << rep.resistorValue << " Ohms\n";
        cout << "Min Power Dissipated: " << rep.powerRating << " W\n";
        cout << "Recommended Power : " << ceil(rep.powerRating * POWER_SAFETY_FACTOR) << " W resistor\n";
        cout << "---------------------------------------------------\n";
        cout << "Validity : " << rep.validityStatus << " | " << rep.recommendation << "\n"; 
        cout << "LED Current Status : " << rep.currentStatus << "\n"; 
        cout << "Overall Safety : " << rep.safetyStatus << "\n";
        cout << "===================================================\n";
    }

    void saveToFile() {
        ofstream file("LED_Resistor_Report.txt");
        if (!file) {
            cout << "Error: Could not save file.\n";
            return;
        }
        file << "========== LED RESISTOR VALUE CALCULATOR SYSTEM REPORT ==========\n\n";
        for (int i = 0; i < reports.size(); i++) {
            file << "REPORT #" << i + 1 << "\n";
            file << fixed << setprecision(2);
            file << "LED Label/Colour : " << reports[i].ledLabel << "\n";
            file << "Supply Voltage : " << reports[i].supplyVoltage << " V\n";
            file << "LED Forward Voltage : " << reports[i].ledForwardVoltage << " V\n";
            file << "Desired LED Current : " << reports[i].ledCurrent_mA << " mA\n";
            file << "Calculated Resistor : " << reports[i].resistorValue << " Ohms\n";
            file << "Validity : " << reports[i].validityStatus << "\n";
            file << "LED Current Status : " << reports[i].currentStatus << "\n";
            file << "Overall Safety : " << reports[i].safetyStatus << "\n";
            file << "Recommendation : " << reports[i].recommendation << "\n";
            file << "---------------------------------------------------\n\n";
        }
        file.close();
        cout << "\nReport saved successfully to 'LED_Resistor_Report.txt'\n";
    }

public:
    void run() {
        cout << "==============================================\n";
        cout << " LED RESISTOR VALUE CALCULATOR SYSTEM \n";
        cout << "==============================================\n\n";

        int numCalculations;
        cout << "How many LED calculations do you want to perform? [Max 10]: ";
        cin >> numCalculations;
        if (numCalculations < 1) numCalculations = 1;
        if (numCalculations > 10) numCalculations = 10;

        for (int i = 0; i < numCalculations; i++) {
            cout << "\n--- Enter details for LED #" << i + 1 << " ---\n";
            LEDReport rep;

            cout << "Enter LED Colour or Label: ";
            cin.ignore();
            getline(cin, rep.ledLabel);

            cout << "Enter Supply Voltage (V): ";
            cin >> rep.supplyVoltage;
            cout << "Enter LED Forward Voltage (V): ";
            cin >> rep.ledForwardVoltage;
            cout << "Enter Desired LED Current (mA): ";
            cin >> rep.ledCurrent_mA;

            if (!validateInputs(rep.supplyVoltage, rep.ledForwardVoltage, rep.ledCurrent_mA)) {
                rep.resistorValue = -1; 
                rep.powerRating = 0;
                rep.validityStatus = "Invalid!";
                rep.currentStatus = "N/A";
                rep.safetyStatus = "INVALID";
                rep.recommendation = "Design not accepted. Check that Vs > Vf > 0 and Current > 0.";
                cout << "\n[ERROR] Invalid inputs detected.\n";
            } else {
                calculate(rep.supplyVoltage, rep.ledForwardVoltage, rep.ledCurrent_mA, rep);
            }
            reports.push_back(rep);
            displayReport(rep, i);
        }
        saveToFile();
        cout << "\nThank you for using the LED Resistor Calculator!\n";
    }
};

const double LEDCalculator::POWER_SAFETY_FACTOR = 2.0;

int main() {
    LEDCalculator system;
    system.run();
    return 0;
}
