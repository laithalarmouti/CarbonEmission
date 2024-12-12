Carbon Footprint Monitoring Program
-------------------------------------------------------------------------------------
This program allows you to monitor and track your carbon footprint based on various activities such as waste, energy usage, and business travel. The program uses `gnuplot` to visualize the data and provide actionable insights into reducing emissions.

Requirements
-GNUPlot (version 5.2 or above)
-Works on Linux/Windows OS

Installing GNUPlot
1-Linux
  	-Using CMD:
	-Open your terminal.
	-Update your package list:
		BASH:
		sudo apt-get update
	-Install gnuplot:
		sudo apt-get install gnuplot
Sometime you have to manually add PATH to your system variables 
	Add the bin directory to your system's PATH environment variable.

alternatively you can head to https://www.gnuplot.info/download/ and use the installer, however you still have to check your system variables. (Will be shown how in the report)
---------------------------------------------------------------------------------------
2-Windows
alternatively you can head to https://www.gnuplot.info/download/ and use the installer, however you still have to check your system variables. (Will be shown how in the report).


After successfully installing GNUPlot, you can compile and run the code without any issues as it is the only dependency!

---------------------------------------------------------------------------------------

Usage

After running the code, you will be prompted with two available choices, either insert data to calculate your emissions or load previous data from previous calculations, Questions will be prompted on your terminal, answer them and after finishing the questions a graph plot will popup showing the chart, along with printed report on your terminal, along with suggestions to reduce their emissions!

All reports are saved on the scripts directory, make sure to place it in a tidy neat place to find the reports easily.

the user will be asked for their name/company name, initially, if the data with such a name already exists it will be overwritten to be updated, else they can just view their previous history by simply press 2 instead of 1.




#################################################################################################################

#Sample Terminal input and output 
Enter your company name: LaithCorp
1. Input new data
2. Load data and generate report
Enter your choice: 1
Enter your average monthly electricity bill (in euros): 200
Enter your average monthly natural gas bill (in euros): 50
Enter your average monthly fuel bill for transportation (in euros): 100
Enter the amount of waste you generate per month (in kilograms): 500
Enter the percentage of waste recycled or composted: 30
Enter the total kilometers traveled per year for business purposes: 20000
Enter the average fuel efficiency of vehicles (liters per 100 kilometers): 15

Data saved successfully as aithCorp_carbon_data.txt!  

Carbon Footprint Report:
---------------------------------
Energy Usage Emissions: 2788.38 kgCO2/year
Waste Emissions: 1620.00 kgCO2/year
Business Travel Emissions: 3080.00 kgCO2/year
-----------------------------
Total Carbon Footprint: 7488.38 kgCO2/year

Suggestions to Reduce Carbon Emissions:
---------------------------------
- Use fuel-efficient vehicles, such as hybrids or electric cars, for business travel.
- Optimize travel routes to minimize distance and adopt carpooling practices.
---------------------------------



########################################################################################################

#Sample report file output

Electricity Bill: 200 euros
Gas Bill: 50 euros
Fuel Bill: 100 euros
Waste Generated: 500 kg
Waste Recycled Percentage: 30%
Kilometers Traveled: 20000 km
Fuel Efficiency: 15 liters/100 km
---------------------------------
Energy Usage Emissions: 2788.38 kgCO2/year
Waste Emissions: 1620 kgCO2/year
Business Travel Emissions: 3080 kgCO2/year
---------------------------------
Total Carbon Footprint: 7488.38 kgCO2/year


########################################################################################################
Please try with testcases and valid numbers for accurate graph plotting ZOOM out if necessary.
