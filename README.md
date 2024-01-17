# ImageProcessor

A console C++ application for applying filters to BMP pictures. The application uses no third-party library.

## Usage

To use the program, you must use a command like ```{path to the program} {path to input file} {path to output file} -{filter1 name} [filter1 args...] -{filter2 name} [filter2 args...] ...```

You can learn more using the program help message: ```{path to the program}``` without any other arguments.

## Filters available

  * `Crop`
  * `EdgeDetection`
  * `GaussianBlur`
  * `GrayScale`
  * `Minecraft`
  * `Negative`
  * `Sharpening`
  * `Zhmih`
  * `UltraZhmih`

The instructions for using each filter are in the help message.
