#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h> // For Windows
#else
#include <cstdlib> // For Linux and macOS
#endif

// Function to clear the terminal screen
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
}

using namespace std;

// the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET "\033[0m"
#define GRAY "\033[90m"   /* Gray */
#define RED "\033[31m"    /* Red */
#define GREEN "\033[32m"  /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define WHITE "\033[37m"  /* White */
#define BLUE "\033[34m"   /* Blue */

string serialPort = "COM6";
int baudRate = 9600;

bool connected = false;

bool fanOpened = false;
bool lightingOpened = false;
bool irrigationOpened = false;

string enter;

int fanLevel;
int lightingLevel;
int irrigationLevel;

random_device rd;
mt19937 gen(rd());

uniform_real_distribution<double> temperature_dist(0, 60);
double temperature = temperature_dist(gen);

uniform_int_distribution<int> moisture_dist(0, 100);
int moisture = moisture_dist(gen);

void sleep()
{
    chrono::seconds sleepDuration(1);
    this_thread::sleep_for(sleepDuration);
}

void connectSensors(string serialPort, int baudRate)
{
    if (serialPort != "" || baudRate > 0)
    {
        cout << "Connecting to " << YELLOW << serialPort << RESET << " at " << YELLOW << baudRate << RESET << " baud rate" << endl;
        sleep();
        cout << "Connected to " << GREEN << serialPort << RESET << " at " << GREEN << baudRate << RESET << " baud rate" << endl;
        sleep();
        cout << "---" << endl;

        connected = true;
    }
    else
    {
        cout << RED << "Can't connect to the sensors due to unexpected error." << RESET << endl;
        sleep();
        cout << "Please try again later." << endl;
        sleep();
        cout << "---" << endl;

        connected = false;
    }
}

void disconnectSensors()
{
    cout << "Disonnecting to " << YELLOW << serialPort << RESET << " at " << YELLOW << baudRate << RESET << " baud rate" << endl;
    sleep();
    cout << "Disonnected to " << RED << serialPort << RESET << " at " << RED << baudRate << RESET << " baud rate" << endl;
    sleep();
    cout << "---" << endl;

    connected = false;
}

void setSerialPort(string serialPort)
{
}

void setBaudRate(int baudRate)
{
}

void displayTemp()
{
    sleep();
    if (connected)
    {
        uniform_int_distribution<int> randomOperation_dist(0, 1);
        int randomOperation = randomOperation_dist(gen);
        if (randomOperation == 0)
        {
            temperature += (temperature / 20);
        }
        else if (randomOperation == 1)
        {
            temperature -= (temperature / 20);
        }

        if (temperature >= 20 && temperature <= 30)
        {
            cout << "Temperature: " << GREEN << int(temperature) << " degrees" << RESET << endl;
            cout << GREEN << "Temperature level is optimal!" << RESET << endl;
        }
        else if (temperature >= 15 && temperature <= 35)
        {
            cout << "Temperature: " << YELLOW << int(temperature) << " degrees" << RESET << endl;
            cout << YELLOW << "Temperature is getting out of limits! Please check the status!" << RESET << endl;
        }
        else
        {
            cout << "Temperature: " << RED << int(temperature) << " degrees" << RESET << endl;
            cout << RED << "Temperature is out of limits. Please check the fan! Temperature can be harmfull for plants!" << RESET << endl;
        }
    }
}

void displayMoisture()
{
    sleep();
    if (connected)
    {
        uniform_int_distribution<int> randomOperation_dist(0, 1);
        int randomOperation = randomOperation_dist(gen);
        if (randomOperation == 0)
        {
            moisture += (moisture / 20);
        }
        else if (randomOperation == 1)
        {
            moisture -= (moisture / 20);
        }

        if (moisture >= 40 && moisture <= 70)
        {
            cout << "Moisture: " << GREEN << moisture << "%" << RESET << endl;
            cout << GREEN << "Moisture level is optimal!" << RESET << endl;
            sleep();
        }
        else if (moisture >= 30 && moisture <= 80)
        {
            cout << "Moisture: " << YELLOW << moisture << "%" << RESET << endl;
            cout << YELLOW << "Moisture is getting out of limits! Please check the status!" << RESET << endl;
            sleep();
        }
        else
        {
            cout << "Moisture: " << RED << moisture << "%" << RESET << endl;
            cout << RED << "Moisture is out of limits. Please check the fan! Moisture can be harmfull for plants!" << RESET << endl;
            sleep();
        }
    }
}

void turnOnFan(int fanLevel)
{
    if (connected)
    {
        sleep();
        cout << "Fan is being turned on..." << endl;
        sleep();

        temperature = temperature - (fanLevel / 10);
        moisture = moisture - (fanLevel / 5);

        fanOpened = true;

        cout << "Fan turned on!" << endl;
        cout << "Please check the temperature and moisture values." << endl;
        cout << "---" << endl;
    }
    else
    {
        cout << RED << "Please connect to sensors first!" << RESET << endl;
    }
}

void turnOffFan(int fanLevel)
{
    if (connected)
    {
        sleep();
        cout << "Fan is being turned off..." << endl;
        sleep();

        temperature = temperature + (fanLevel / 10);
        moisture = moisture + (fanLevel / 5);

        fanOpened = false;

        cout << "Fan turned off!" << endl;
        cout << "Please check the temperature and moisture values." << endl;
        cout << "---" << endl;
    }
    else
    {
        cout << RED << "Please connect to sensors first!" << RESET << endl;
    }
}

void turnOnLighting(int lightingLevel)
{
    if (connected)
    {
        sleep();
        cout << "Lighting is being turned on..." << endl;
        sleep();

        temperature = temperature + (lightingLevel / 100);
        moisture = moisture - (lightingLevel / 50);

        lightingOpened = true;

        cout << "Lighting turned on!" << endl;
        cout << "Please check the temperature and moisture values." << endl;
        cout << "---" << endl;
    }
    else
    {
        cout << RED << "Please connect to sensors first!" << RESET << endl;
    }
}

void turnOffLighting(int lightingLevel)
{
    if (connected)
    {
        sleep();
        cout << "Lighting is being turned off..." << endl;
        sleep();

        temperature = temperature - (lightingLevel / 100);
        moisture = moisture + (lightingLevel / 50);

        lightingOpened = false;

        cout << "Lighting turned off!" << endl;
        cout << "Please check the temperature and moisture values." << endl;
        cout << "---" << endl;
    }
    else
    {
        cout << RED << "Please connect to sensors first!" << RESET << endl;
    }
}

void turnOnIrrigation(int irrigationLevel)
{
    if (connected)
    {
        sleep();
        cout << "Irrigation is being turned on..." << endl;
        sleep();

        temperature = temperature - (irrigationLevel / 50);
        moisture = moisture + (irrigationLevel / 10);

        irrigationOpened = true;

        cout << "Irrigation system turned on!" << endl;
        cout << "Please check the temperature and moisture values." << endl;
        cout << "---" << endl;
    }
    else
    {
        cout << RED << "Please connect to sensors first!" << RESET << endl;
    }
}

void turnOffIrrigation(int irrigationLevel)
{
    if (connected)
    {
        sleep();
        cout << "Irrigation is being turned off..." << endl;
        sleep();

        temperature = temperature - (irrigationLevel / 50);
        moisture = moisture + (irrigationLevel / 10);

        irrigationOpened = false;

        cout << "Irrigation system turned off!" << endl;
        cout << "Please check the temperature and moisture values." << endl;
        cout << "---" << endl;
    }
    else
    {
        cout << RED << "Please connect to sensors first!" << RESET << endl;
    }
}

void printMenu()
{
    cout << "GREENHOUSE AUTOMATION SYSTEM" << endl;
    cout << "---" << endl;
    if (!connected)
    {
        cout << "Serial Port: " << BLUE << serialPort << RESET << endl;
        cout << "Baud Rate: " << BLUE << baudRate << RESET << endl;
    }
    else
    {
        cout << "Serial Port: " << GREEN << serialPort << RESET << endl;
        cout << "Baud Rate: " << GREEN << baudRate << RESET << endl;
    }
    cout << "---" << endl;

    if (!connected)
    {
        cout << "1. Connect to sensors" << endl;
    }
    else
    {
        cout << "1. Disconnect to sensors" << endl;
    }

    cout << "2. Set Serial Port" << endl;
    cout << "3. Set Baud Rate" << endl;
    string status;
    if (connected)
    {
        status = WHITE;
    }
    else
    {
        status = GRAY;
    }
    cout << status << "4. Display Temparature and Moisture" << RESET << endl;

    if (!fanOpened)
    {
        cout << status << "5. Turn ON the fan system." << RESET << endl;
    }
    else
    {
        cout << status << "5. Turn OFF the fan system." << RESET << endl;
    }

    if (!lightingOpened)
    {
        cout << status << "6. Turn ON the lighting system." << RESET << endl;
    }
    else
    {
        cout << status << "6. Turn OFF the lighting system." << RESET << endl;
    }

    if (!irrigationOpened)
    {
        cout << status << "7. Turn ON the irrigation system." << RESET << endl;
    }
    else
    {
        cout << status << "7. Turn OFF the irrigation system." << RESET << endl;
    }

    cout << status << "8. Only display mode" << RESET << endl;
    cout << "9. EXIT" << endl;
    cout << "---" << endl;
}

int main()
{
    while (true)
    {
        clearScreen();
        printMenu();

        cout << "Please select a operation from list: ";
        int choice;
        cin >> choice;
        if(cin.fail()) {
            throw runtime_error("Invalid input. Please enter a valid choice.");
        }

        cin.clear();
        cin.ignore();

        switch (choice)
        {
        case 1:
            if (!connected)
            {
                connectSensors(serialPort, baudRate);
            }
            else
            {
                disconnectSensors();
            }
            cout << "Please press any key to continue: ";
            cin >> enter;
            continue;

        case 2:
            cout << "Please enter a serial port: ";
            cin >> serialPort;
            setSerialPort(serialPort);
            cout << "Please press any key to continue: ";
            cin >> enter;
            continue;

        case 3:
            cout << "Please enter a baud rate: ";
            cin >> baudRate;
            setBaudRate(baudRate);
            cout << "Please press any key to continue: ";
            cin >> enter;
            continue;

        case 4:
            displayTemp();
            displayMoisture();
            cout << "---" << endl;
            cout << "Please press any key to continue: ";
            cin >> enter;
            continue;

        case 5:
            if (!fanOpened)
            {
                cout << "---" << endl;
                cout << "Enter the power level of fan (1-100): ";
                cin >> fanLevel;
                turnOnFan(fanLevel);
            }
            else
            {
                turnOffFan(fanLevel);
            }
            cout << "Please press any key to continue: ";
            cin >> enter;
            continue;

        case 6:
            if (!lightingOpened)
            {
                cout << "---" << endl;
                cout << "Enter the power level of lighting (1-100): ";
                cin >> lightingLevel;
                turnOnLighting(lightingLevel);
            }
            else
            {
                turnOffLighting(lightingLevel);
            }
            cout << "Please press any key to continue: ";
            cin >> enter;
            continue;

        case 7:
            if (!irrigationOpened)
            {
                cout << "---" << endl;
                cout << "Enter the power level of irrigation (1-100): ";
                cin >> fanLevel;
                turnOnIrrigation(irrigationLevel);
            }
            else
            {
                turnOffIrrigation(irrigationLevel);
            }
            cout << "Please press any key to continue: ";
            cin >> enter;
            continue;

        case 8:
            if (connected)
            {
                while (true)
                {
                    displayTemp();
                    displayMoisture();
                    cout << "---" << endl;
                }
            }
            else
            {
                cout << RED << "Please connect to sensors first!" << RESET << endl;
                cout << "Please press any key to continue: ";
                cin >> enter;
                continue;
            }

        case 9:
            return 0;

        default:
            break;
        }
    }

    return 0;
}