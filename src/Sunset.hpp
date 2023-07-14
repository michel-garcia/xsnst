#pragma once
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

struct RGBColor {
    double r = 1.0;
    double g = 1.0;
    double b = 1.0;
};

class Sunset {
    public:
        Sunset();
        ~Sunset();
        bool IsEnabled();
        void Enable(int temp);
        void Enable(RGBColor color);
        void Disable();
        static RGBColor TempToColor(int temp);
    private:
        Display *display;
        XRRScreenResources *res;
};
