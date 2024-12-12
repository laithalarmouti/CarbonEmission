#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include<sstream>
#include <limits>

using namespace std;

struct CarbonData {
    double electricityBill;
    double gasBill;
    double fuelBill;
    double wasteGenerated;
    double wasteRecycledPercentage;
    double kilometersTraveled;
    double fuelEfficiency;
};

//prototypes
void saveData(const CarbonData& data, const string& filename);
CarbonData loadData(const string& filename);
void calculateData(const CarbonData& data);
CarbonData getInputData();
void giveSuggestions(const CarbonData& data);
void plotCarbonEmissions(const vector<double>& emissions);

int main() {
    CarbonData data;
    string companyName;
    string filename;
    int choice;

    cout << "Carbon Footprint Monitoring Program\n";
    cout << "Enter your company name: ";
    cin.ignore();
    getline(cin, companyName);
    filename = companyName + "_carbon_data.txt";

    cout << "1. Input new data\n";
    cout << "2. Load data and generate report\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        data = getInputData();
        saveData(data, filename);
        cout << "Data saved successfully as " << filename << "!\n";
        calculateData(data); 
        giveSuggestions(data); 

        // Collecting emission data for plotting
        vector<double> emissions = {
            (data.electricityBill * 12 * 0.0005) + (data.gasBill * 12 * 0.0053) + (data.fuelBill * 12 * 2.32),
            data.wasteGenerated * 12 * (0.57 - (data.wasteRecycledPercentage / 100.0)),
            data.kilometersTraveled * (1/data.fuelEfficiency)* 2.31
        };

        // Plot the emissions data
        plotCarbonEmissions(emissions);
    } else if (choice == 2) {
        try {
            data = loadData(filename);
            calculateData(data);
            giveSuggestions(data); 
            
            vector<double> emissions = {
                (data.electricityBill * 12 * 0.0005) + (data.gasBill * 12 * 0.0053) + (data.fuelBill * 12 * 2.32),
                data.wasteGenerated * 12 * (0.57 - (data.wasteRecycledPercentage / 100.0)),
                data.kilometersTraveled * (1/data.fuelEfficiency) * 2.31
            };

            // Plot the emissions data
            plotCarbonEmissions(emissions);

        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } else {
        cout << "Invalid choice!\n";
    }

    return 0;
}

// Function to collect input data from the user
CarbonData getInputData() {
    CarbonData data;
    cout << "Enter your average monthly electricity bill (in euros): ";
    cin >> data.electricityBill;
    cout << "Enter your average monthly natural gas bill (in euros): ";
    cin >> data.gasBill;
    cout << "Enter your average monthly fuel bill for transportation (in euros): ";
    cin >> data.fuelBill;
    cout << "Enter the amount of waste you generate per month (in kilograms): ";
    cin >> data.wasteGenerated;
    cout << "Enter the percentage of waste recycled or composted: ";
    cin >> data.wasteRecycledPercentage;
    cout << "Enter the total kilometers traveled per year for business purposes: ";
    cin >> data.kilometersTraveled;
    cout << "Enter the average fuel efficiency of vehicles (liters per 100 kilometers): ";
    cin >> data.fuelEfficiency;
    return data;
}


void saveData(const CarbonData& data, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Error opening file.");
    }

    outFile << "Electricity Bill: " << data.electricityBill << " euros\n"
            << "Gas Bill: " << data.gasBill << " euros\n"
            << "Fuel Bill: " << data.fuelBill << " euros\n"
            << "Waste Generated: " << data.wasteGenerated << " kg\n"
            << "Waste Recycled Percentage: " << data.wasteRecycledPercentage << "%\n"
            << "Kilometers Traveled: " << data.kilometersTraveled << " km\n"
            << "Fuel Efficiency: " << data.fuelEfficiency << " liters/100 km\n";

 double energyCO2 = (data.electricityBill*12*0.0005) +
                       (data.gasBill*12*0.0053) +
                       (data.fuelBill*12*2.32);
    //Equation given returns negative values if recycling percentage is above 57? 
    //tried flooring rounding to 0 if it goes below 0, messed up the plotting part.
    double wasteCO2 = data.wasteGenerated*12*(0.57-(data.wasteRecycledPercentage/100.0));
    double travelCO2 = data.kilometersTraveled * (1.0 / data.fuelEfficiency) * 2.31;


    double totalCO2 = energyCO2 + wasteCO2 + travelCO2;

    // Add the total carbon footprint
    outFile << "---------------------------------\n";
    outFile << "Energy Usage Emissions: " << energyCO2 << " kgCO2/year\n";
    outFile << "Waste Emissions: " << wasteCO2 << " kgCO2/year\n";
    outFile << "Business Travel Emissions: " << travelCO2 << " kgCO2/year\n";
    outFile << "---------------------------------\n";
    outFile << "Total Carbon Footprint: " << totalCO2 << " kgCO2/year\n";

    outFile.close();
}

CarbonData loadData(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Error opening the file.");
    }

    CarbonData data;
    std::string line;

    // Read and parse each line to extract the numbers only from report
    std::getline(inFile, line);
    std::istringstream(line.substr(line.find(":") + 1)) >> data.electricityBill;

    std::getline(inFile, line);
    std::istringstream(line.substr(line.find(":") + 1)) >> data.gasBill;

    std::getline(inFile, line);
    std::istringstream(line.substr(line.find(":") + 1)) >> data.fuelBill;

    std::getline(inFile, line);
    std::istringstream(line.substr(line.find(":") + 1)) >> data.wasteGenerated;

    std::getline(inFile, line);
    std::istringstream(line.substr(line.find(":") + 1)) >> data.wasteRecycledPercentage;

    std::getline(inFile, line);
    std::istringstream(line.substr(line.find(":") + 1)) >> data.kilometersTraveled;

    std::getline(inFile, line);
    std::istringstream(line.substr(line.find(":") + 1)) >> data.fuelEfficiency;

    inFile.close();
    return data;
}

//calculations
void calculateData(const CarbonData& data) {
    double energyCO2 = (data.electricityBill*12*0.0005) +
                       (data.gasBill*12*0.0053) +
                       (data.fuelBill*12*2.32);
    //Equation given returns negative values if recycling percentage is above 57? 
    //tried flooring rounding to 0 if it goes below 0, messed up the plotting part.
    double wasteCO2 = data.wasteGenerated*12*(0.57-(data.wasteRecycledPercentage/100.0));
    double travelCO2 = data.kilometersTraveled * (1.0 / data.fuelEfficiency) * 2.31;


    double totalCO2 = energyCO2 + wasteCO2 + travelCO2;

    //Report
    cout << fixed << setprecision(2);
    cout << "\nCarbon Footprint Report:\n";
    cout << "---------------------------------\n";
    cout << "Energy Usage Emissions: " << energyCO2 << " kgCO2/year\n";
    cout << "Waste Emissions: " << wasteCO2 << " kgCO2/year\n";
    cout << "Business Travel Emissions: " << travelCO2 << " kgCO2/year\n";
    cout << "-----------------------------\n";
    cout << "Total Carbon Footprint: " << totalCO2 << " kgCO2/year\n";
}

// Suggestions
void giveSuggestions(const CarbonData& data) {
    cout << "\nSuggestions to Reduce Carbon Emissions:\n";
    cout << "---------------------------------\n";

    double energyCO2 = (data.electricityBill * 12 * 0.0005) +
                       (data.gasBill * 12 * 0.0053) +
                       (data.fuelBill * 12 * 2.32);
    double wasteCO2 = data.wasteGenerated * 12 * (0.57 - (data.wasteRecycledPercentage / 100.0));
    double travelCO2 = data.kilometersTraveled * (1.0 / data.fuelEfficiency) * 2.31;

    if (energyCO2 > wasteCO2 && energyCO2 > travelCO2) {
        cout << "- Consider installing energy-efficient appliances and using renewable energy sources like solar panels.\n";
        cout << "- Implement energy-saving practices such as turning off unused equipment and optimizing heating/cooling systems.\n";
    }

    if (wasteCO2 > energyCO2 && wasteCO2 > travelCO2) {
        cout << "- Increase the percentage of waste recycled or composted.\n";
        cout << "- Reduce waste generation by adopting reusable materials and improving waste management practices.\n";
    }

    if (travelCO2 > energyCO2 && travelCO2 > wasteCO2) {
        cout << "- Use fuel-efficient vehicles, such as hybrids or electric cars, for business travel.\n";
        cout << "- Optimize travel routes to minimize distance and adopt carpooling practices.\n";
    }

    cout << "---------------------------------\n";
}


void plotCarbonEmissions(const vector<double>& emissions) {
    // Create a txt file store temp data, which will be overwritten
    ofstream dataFile("emissions_data.txt");
    dataFile << "Energy " << emissions[0] << endl;
    dataFile << "Waste " << emissions[1] << endl;
    dataFile << "Travel " << emissions[2] << endl;
    dataFile.close();

//plotting to gnuplot
    system("gnuplot -e \"set title 'Carbon Emissions'; \
                        set xlabel 'Category'; \
                        set ylabel 'Emissions (kgCO2)'; \
                        set style data histograms; \
                        set style fill solid 1.0; \
                        set boxwidth 0.5; \
                        set xtics rotate by -45; \
                        plot 'emissions_data.txt' using 2:xtic(1) with boxes lc rgb 'blue' title 'Emissions'; \
                        pause -1\"");
}