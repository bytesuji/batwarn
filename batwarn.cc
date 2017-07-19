#include <libnotify/notify.h>
#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>
#include "exec.h"

using std::cerr;
using std::stoi;
using std::this_thread::sleep_for;
using std::chrono::seconds;

int main() {
	notify_init("batwarn");
	static unsigned long prev_time = 0;

	while (true) { 
		bool should_notify = {
			stoi(exec("cat /sys/class/power_supply/BAT0/capacity")) <= 10 && 
			time(0) - prev_time >= 300 && 
			exec("cat /sys/class/power_supply/BAT0/status")[0] == 'D'
		};

		cerr << should_notify << std::endl;

		if (should_notify) {
			NotifyNotification* n = 
				notify_notification_new("Warning! 10% charge remains.", "Plug in your laptop.", "battery-caution");
			notify_notification_set_timeout(n, 300000);

			if (!notify_notification_show(n, 0)) {
				cerr << "show has failed!\n";
				return -1;		
			}

			prev_time = time(0);
		}

		sleep_for(seconds(5));
	}

	notify_uninit();
	return 0;
}
