
#include <iostream>

#include "FileReader.h"
#include "DataFrame.h"
#include "Util.h"
#include <fstream>

#define LOG1(x) std::cout << "Data successful loaded: " << x << std::endl
#define LOG2(x) std::cout << "Rows successfully loaded: " << x << std::endl
#define GET_BOTH std::cout << "Please enter month and year: \n"
#define GET_YEAR std::cout << "Please enter year: \n"
#define PRINT_LOOP(x) for (size_t i = 0; i < x; i++)
#define NO_DATA_WARNING(x) \
    if (x == 0)            \
    std::cout << "No data.\n"

//const std::string path = "C:\\Users\\kokwa\\OneDrive\\Desktop\\ICT283 Assignment 1\\ICT283_Asign1_Chan_Kok_Wai_33924804\\data\\";

const std::string path = "C:/Users/kokwa/OneDrive/Desktop/ICT283_Assignment2/data/";
int main()

{
    Vector<std::string> paths;
    // paths.push_back(path + "MetData-31-3a.csv");

    const auto testFile1 = path + "Metdata-Jan-Dec2007.csv";
    const auto testFile2 = path + "Metdata-Jan-Dec2008.csv";
    const auto testFile3 = path + "Metdata-Jan-Dec2009.csv";
    const auto testFile4 = path + "Metdata-Jan-Dec2016.csv";
    const auto testFile5 = path + "MetData_Jan01-2010-Jan01-2011-ALL.csv";
    const auto testFile6 = path + "MetData_Jan01-2011-Jan01-2012-ALL.csv";
    const auto testFile7 = path + "MetData_Jan01-2012-Jan01-2013-ALL.csv";
    const auto testFile8 = path + "MetData_Jan01-2013-Jan01-2014-ALL.csv";
    const auto testFile9 = path + "MetData_Mar01-2014-Mar01-2015-ALL.csv";
    const auto testFile10 = path + "MetData_Mar01-2015-Mar01-2016-ALL.csv";

    FileReader reader;
    const auto rowData = reader.readDataFromFile(testFile1);

    const auto colNames = reader.readColNamesFromFile(testFile1);

    LOG1(rowData.size());

    LOG2(colNames.size());


    DataFrame df(rowData, colNames);


    std::cout << "Size then: " << df.size() << std::endl;

    //Reading data from all remaining files
    df.appendData(reader.readDataFromFile(testFile2));
    df.appendData(reader.readDataFromFile(testFile3));
    df.appendData(reader.readDataFromFile(testFile4));
    df.appendData(reader.readDataFromFile(testFile5));
    df.appendData(reader.readDataFromFile(testFile6));
    df.appendData(reader.readDataFromFile(testFile7));
    df.appendData(reader.readDataFromFile(testFile8));
    df.appendData(reader.readDataFromFile(testFile9));
    df.appendData(reader.readDataFromFile(testFile10));


    int choice;

    do{
Menu:

    std::cout << "\n1. The average wind speed and average ambient air temperature for a specified month and year.\n2. Average wind speed and average ambient air temperature for each month of a specified year. \n3. Total solar radiation in kWh / m2 for each month of a specified year.\n4. Average wind speed(km / h), average ambient air temperature and total solar radiation in kWh / m2 for each month of a specified year.\n5. Find highest solar radiation times for date \n6. Exit the program. \nEnter your choice. \n";

    std::cin >> choice;
    int year, month,day;
    DataFrame _df;
    std::ofstream outfile;
    std::string out_path = "OutputResult.csv";
    Vector<std::tuple<Date, float>> temp, ws, sr;

    switch (choice)
    {
    case 1:
        GET_BOTH;
        cin >> month >> year;
        _df = df.filter(month, year);
        if (_df.size() == 0)
        {
            std::cout << get_month_string(month) << " " << year << " : No Data.\n";
            break;
        }
        ws = _df.reduce("S");
        temp = _df.reduce("T");
        std::cout << year << std::endl;
        PRINT_LOOP(ws.size())
        {
            std::cout << std::get<0>(ws[i]) << " : " << std::get<1>(ws[i]) << " km/h, " << std::get<1>(temp[i]) << " degrees C\n";
        }
        break;
    case 2:
        GET_YEAR;
        cin >> year;
        _df = df.filter(year);
        NO_DATA_WARNING(_df.size());
        ws = _df.reduce("S");
        temp = _df.reduce("T");
        std::cout << year << std::endl;
        PRINT_LOOP(ws.size())
        {
            std::cout << std::get<0>(ws[i]) << " : " << std::get<1>(ws[i]) << " km/h, " << std::get<1>(temp[i]) << " degrees C\n";
        };
        break;
    case 3:
        GET_YEAR;
        cin >> year;
        _df = df.filter(year);
        NO_DATA_WARNING(_df.size());
        _df = _df.filter("SR", [](double sr) {
            if (sr > 100)
                return true;
            else
                return false;
        });
        _df = _df.map("SR", [](double sr) {
            return sr * 1 / 6000;
        });
        sr = _df.reduce("SR");
        std::cout << year << std::endl;
        PRINT_LOOP(sr.size())
        {
            std::cout << std::get<0>(sr[i]) << " : " << std::get<1>(sr[i]) << " kWh/m2\n";
        };
        break;
    case 4:
        GET_YEAR;
        cin >> year;
        _df = df.filter(year);
        outfile.open(out_path);
        if (_df.size())
        {
            ws = _df.reduce("S");
            temp = _df.reduce("T");
            _df = _df.filter("SR", [](double sr) {
                if (sr > 100)
                    return true;
                else
                    return false;
            });
            _df = _df.map("SR", [](double sr) {
                return sr * 1 / 6000;
            });
            sr = _df.reduce("SR");
            outfile << std::get<0>(sr[0]).GetYear() << std::endl;
            PRINT_LOOP(ws.size())
            outfile << std::get<0>(ws[i]) << "," << std::get<1>(ws[i]) << "," << std::get<1>(temp[i]) << "," << std::get<1>(sr[i]) << std::endl;
            std:: cout << "SUCCESSFUL!!, The data for the year has being output" << std::endl;
        }
        else
            outfile << year << std::endl
                    << "No data.\n";
        ;
        break;
    case 5:
        std::cout <<"Please enter date format as (dd mm yyyy): ";
        std::cin >> day >>month >> year;
        df.MaxSolarRadiationsOnDate(Date(day, std::to_string(month), year));
        break;

    }while(choice != 6);
    return 0;
 }



    /*
    case 6:
        exit(0);
    default:
        goto Menu; */
        }



    //newDF.printRows(10);

