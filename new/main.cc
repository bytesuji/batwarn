#include <fstream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

const int WARN_LIM = 25;
const int CRIT_LIM = 5;
const string WARN_CMD = "i3-nagbar -m \"Warning: battery is low (";
const string CRIT_CMD = "i3-nagbar -m \"BATTERY IS CRITICALLY LOW: (";


unsigned get_capac() {
    ifstream bat_file("/sys/class/power_supply/BAT0/capacity");
    string capac;
    getline(bat_file, capac);
    bat_file.close();

    return atoi(capac.c_str());
}

bool is_on_ac() {
    ifstream state_file("/sys/class/power_supply/BAT0/status");
    string status;
    getline(state_file, status);
    state_file.close();

    if (status == "Charging")
        return true;
    else
        return false;
}

int main() {
    while (true) {
        int current_capac = get_capac();
        if (current_capac <= CRIT_LIM && !is_on_ac()) {
            stringstream cmd;
            cmd << CRIT_CMD << current_capac << "%)\"";
            system(cmd.str().c_str());
            this_thread::sleep_for(chrono::minutes(2));
        }

        else if (current_capac <= WARN_LIM && !is_on_ac()) {
            stringstream cmd;
            cmd << WARN_CMD << current_capac << "%)\"";
            system(cmd.str().c_str());
            this_thread::sleep_for(chrono::minutes(15));
        }

        this_thread::sleep_for(chrono::seconds(5));
    }

    return 0;
}
