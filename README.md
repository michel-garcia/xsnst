# XSunset

XSunset is an uncomplicated tool which sole goal is to adjust the display's color temperature.

## Why

I have been using redshift for a long time and while it works fine for the most part it has several features I do not use. This served as motivation to write this minimalist piece of software since I could not find a simpler alternative.

## Compile

You will need to satisfy the following dependencies first:

- x11
- xrandr

Then proceed to build and compile the project using meson:

```
meson setup build
meson compile -C build
```

Now you can run `./xsnst` as long as you are in the build directory.

If you wish to install it systemwide run:

```
meson install -C build
```

## Usage

The arguments have been written as straightforward as possible:

```
# Enabling night light:
xsnst --enable 3500

# Disabling night light:
xsnst --disable

# Checking status:
xsnst --status
```

A help message is also included under the `--help` switch, should you need a reminder of these.

## Credits

The temperature conversion algorithm used in this software is based on the article [How to Convert Temperature to RGB by Tanner Helland](https://tannerhelland.com/2012/09/18/convert-temperature-rgb-algorithm-code.html).
