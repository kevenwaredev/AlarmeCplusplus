#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void playAlarm() {
#ifdef _WIN32
    Beep(750, 300);
    std::cout << "\a"; 
#endif
}

int main() {
    int alarmHour, alarmMinute;

    std::cout << "Defina a hora do alarme no formato (HH MM): ";
    std::cin >> alarmHour >> alarmMinute;

    while (true) {
        
        std::time_t currentTime = std::time(nullptr);
        std::tm localTime;

#ifdef _WIN32
        localtime_s(&localTime, &currentTime);
#else
        std::tm* localTimePtr = std::localtime(&currentTime);
        localTime = *localTimePtr;
#endif

        int currentHour = localTime.tm_hour;
        int currentMinute = localTime.tm_min;

        
        if (currentHour == alarmHour && currentMinute == alarmMinute) {
            playAlarm();
            std::cout << "Alarme! Sao " << currentHour << ":" << currentMinute << " agora!" << std::endl;
            break;
        }

        
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }

    return 0;
}
