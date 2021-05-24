#pragma warning(disable : 4996)
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>


using namespace std;

string retrieveString(char* endTime, int max) {

    size_t len = 0;
    while ((len < max) && (endTime[len] != '\0')) {
        len++;
    }

    return string(endTime, len);

}

int main(){
    int count = 0;
    auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());

    while (true) {
        
        int google = (system("ping www.google.com"));
        int bing = (system("ping www.bing.com"));
        int usa = (system("ping www.usa.gov"));
        

        if (google == 0 || bing == 0 || usa == 0) {
            cout << "\nInternet is Connected" << endl;
            
            //count resets when connection is achieved
            if (count > 0) {
                cout << "Internet reconnected at: " << endl;
                time_t now = time(0);
                char* endTime = ctime(&now);
                string countString = to_string(count);
                string fileLine = retrieveString(endTime, 24);
                fileLine += ",";
                fileLine += countString;
                cout << endTime << endl;
                cout << "Log created" << endl;
                cout << fileLine << endl;

                //make file
                fstream connectionLog;
                connectionLog.open("connectionLog.csv", ios::app);
                if (!connectionLog) {
                    cout << "data file not created!";
                }
                else {
                    //create log when the user reconnects
                    connectionLog << fileLine << endl;
                    connectionLog.close();
                }
            }
            count = 0;
        }

        else {
            cout << "not connected" << endl;
            if (count == 0) {
                time_t now = time(0);
                char* startTime = ctime(&now);
                cout << startTime << endl;
            }
            count++;
        }

        //repeat
        this_thread::sleep_for(chrono::seconds(60));
    }
}