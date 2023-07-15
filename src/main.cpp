#include <string.h>
#include <format>
#include <string>
#include "Sunset.hpp"

void bail(std::string message) {
    printf("xsnst: %s\n", message.c_str());
    printf("Try 'xsnst --help' for more information.\n");
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        bail("missing option argument");
        return 1;
    }
    Sunset sunset;
    std::string option = argv[1];
    if (option == "--enable" || option == "-e") {
        if (argc > 2) {
            int temp = std::atoi(argv[2]);
            if (temp > 0) {
                sunset.Enable(temp);
                return 0;
            }
        }
        bail("missing temperature argument");
        return 1;
    }
    if (option == "--disable" || option == "-d") {
        sunset.Disable();
        return 0;
    }
    if (option == "--status" || option == "-s") {
        bool enabled = sunset.IsEnabled();
        printf(enabled ? "enabled" : "disabled");
        return 0;
    }
    if (option == "--help" || option == "-h") {
        printf(
            "Usage: xsnst [OPTIONS...]\n"
            "\n"
            "  -h, --help                   Display this help message\n"
            "\n"
            "  -e, --enable [TEMP]          Enable temperature adjustments\n"
            "  -d, --disable                Disable temperature adjustments\n"
            "  -s, --status                 Show status of temperature adjustments\n"
        );
        return 0;
    }
    bail(std::format("unrecognized option '{}'", option));
    return 1;
}
