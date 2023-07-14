#include "Sunset.hpp"
#include <math.h>
#include <algorithm>

Sunset::Sunset() {
    this->display = XOpenDisplay(0);
    int screen = DefaultScreen(this->display);
    Window window = RootWindow(this->display, screen);
    this->res = XRRGetScreenResourcesCurrent(this->display, window);
}

Sunset::~Sunset() {
    XFree(this->res);
    XCloseDisplay(this->display);
}

bool Sunset::IsEnabled() {
    for (int i = 0; i < this->res->ncrtc; i++) {
        RRCrtc crtc = this->res->crtcs[i];
        int size = XRRGetCrtcGammaSize(this->display, crtc);
        XRRCrtcGamma *gamma = XRRGetCrtcGamma(this->display, crtc);
        for (int j = 0; j < size; j++) {
            int red = gamma->red[j];
            int green = gamma->green[j];
            int blue = gamma->blue[j];
            if (red != green || green != blue) {
                XFree(gamma);
                return true;
            }
        }
        XFree(gamma);
    }
    return false;
}

void Sunset::Enable(int temp) {
    RGBColor color = TempToColor(temp);
    Enable(color);
}

void Sunset::Enable(RGBColor color) {
    for (int i = 0; i < this->res->ncrtc; i++) {
        RRCrtc crtc = this->res->crtcs[i];
        int size = XRRGetCrtcGammaSize(this->display, crtc);
        XRRCrtcGamma *gamma = XRRAllocGamma(size);
        for (int j = 0; j < size; j++) {
            double factor = 65535.0 * j / size;
            gamma->red[j] = color.r * factor;
            gamma->green[j] = color.g * factor;
            gamma->blue[j] = color.b * factor;
        }
        XRRSetCrtcGamma(this->display, crtc, gamma);
        XFree(gamma);
    }
}

void Sunset::Disable() {
    RGBColor color;
    Enable(color);
}

// based on the article How to Convert Temperature to RGB by Tanner Helland
// tannerhelland.com/2012/09/18/convert-temperature-rgb-algorithm-code.html
RGBColor Sunset::TempToColor(int temp) {
    RGBColor color;
    double factor = (double) temp / 100;
    if (temp <= 6600) {
        color.r = 255;
        color.g = 99.4708025861 * std::log(factor) - 161.1195681661;
    } else {
        color.r = 329.698727446 * std::pow(factor - 60, -0.1332047592);
        color.g = 288.1221695283 * std::pow(factor - 60, -0.0755148492);
    }
    if (temp <= 1900) {
        color.b = 0;
    } else if (temp >= 6600) {
        color.b = 255;
    } else {
        color.b = 138.5177312231 * std::log(factor - 10) - 305.0447927307;
    }
    color.r = std::clamp(color.r / 255, 0.0, 1.0);
    color.g = std::clamp(color.g / 255, 0.0, 1.0);
    color.b = std::clamp(color.b / 255, 0.0, 1.0);
    return color;
}
