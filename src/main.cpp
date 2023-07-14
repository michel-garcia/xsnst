#include <string.h>
#include <string>
#include "Sunset.hpp"

int main(int argc, char *argv[]) {
    Sunset sunset;
    if (argc == 2 && strcmp(argv[1], "--disable") == 0) {
        sunset.Disable();
        return 0;
    }
    if (argc == 3 && strcmp(argv[1], "--enable") == 0) {
        int temp = std::atoi(argv[2]);
        if (temp > 0) {
            sunset.Enable(temp);
            return 0;
        }
    }
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printf(
            "Usage: xsnst [OPTIONS...]\n"
            "\n"
            "--help\t\tDisplays this help message\n"
            "\n"
            "--enable TEMP\tEnables night light using provided TEMP\n"
            "--disable\tDisables night light if active\n"
            "--status\tShows whether night light is enabled or not\n"
        );
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "--status") == 0) {
        bool enabled = sunset.IsEnabled();
        printf(enabled ? "enabled" : "disabled");
        return 0;
    }
    return 1;
}
