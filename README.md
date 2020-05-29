<!-- PROJECT SHIELDS -->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->

<br />

<p align="center">
  <a href="https://github.com/JairajJangle/Open-CV-Catalogue">
    <img src="assets/app_logo.png" alt="Logo" width="100">
  </a>


  <h3 align="center">OpenCV Catalogue</h3>

  <p align="center">
    A GUI application to view and test all OpenCV operations
    <br />
    <a href="https://github.com/JairajJangle/Open-CV-Catalogue"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/JairajJangle/Open-CV-Catalogue">View Demo</a>
    ·
    <a href="https://github.com/JairajJangle/Open-CV-Catalogue/issues">Report Bug</a>
    ·
    <a href="https://github.com/JairajJangle/Open-CV-Catalogue/issues">Request Feature</a>
  </p>

</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites for contribution](#prerequisites-for-contribution)
  * [Run the standalone application](#run-the-standalone-application)
* [Application usage](#application-usage)
  * [1. Select Input source](#1-select-input-source)
  * [2. Select OpenCV Operation](#2-select-opencv-operation)
  * [3. Adjusting OpenCV Operation parameters](#3-adjusting-opencv-operation-parameters)
* [For Developers: Project Structure](#for-developers-project-structure)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Support the project development](#support-the-project-development)



<!-- ABOUT THE PROJECT -->

## About The Project
TODO: Add gif

<p align="center">
  <a href="https://github.com/JairajJangle/Open-CV-Catalogue">
    <img src="media/screenshot_canny.png" alt="Logo" width="756" >
  </a>
</p>

OpenCV Catalogue is a stand alone application which is made to let OpenCV beginnners and veterans test any OpenCV operation without a need to code. This awesome GUI application lets the user control all parameters of an OpenCV operation using GUI elements such as Sliders/Seekbars, Input Text Box, Radio Buttons and Check Boxes.

This project is still in development and as of now covers primitive OpenCV operations. But, with the power of open sourcing, this application can be made to cover all the OpenCV operations, very soon.

This repository also contain release packages with standalone GUI application which anyone can run it on their Linux system. OpenCV Catalogue is primarily saves user's time with figuring out what parameter causes what changes on the output.

Features:
* Select camera, image files and video files as input source
* Real time ajustment of paramters of selected OpenCV operation
* Provide's link to official OpenCV documentation to selected OpenCV operation
* Paramter adjustment can be done with Seekbars, Text Boxes, Check Boxes, Radio Buttons.

Coming Soon:
* Exploded View of OpenCV operations to give more insights
* Multi-threading to keep GUI lag free while testing compute-heavy operations
* Chaining of various OpenCV operations in a sequence
* Support for CUDA operations

### Built With
* [C++](https://devdocs.io/cpp/)
* [QT](https://www.qt.io/)
* [OpenCV](https://opencv.org/)



<!-- GETTING STARTED -->

## Getting Started

Get started with contributing to OpenCV Catalogue

### Prerequisites for contribution
* [Install OpenCV](https://docs.opencv.org/trunk/df/d65/tutorial_table_of_content_introduction.html): Go for 3.x+ version
* [Install QT libs + QT Creator](https://www.qt.io/download-open-source)
* For development, supported platforms: Linux, MacOS, Windows

### Run the standalone application
```sh
cd <.AppImage File Location>
chmod +x <name of .AppImage File>
./<name of .AppImage File>
```



<!-- USAGE EXAMPLES -->

## Application usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

### 1. Select Input source
<p align="center">
  <a href="https://github.com/JairajJangle/Open-CV-Catalogue">
    <img src="media/screenshot_select_input_camera.jpg" alt="Input_Cam" width="512" >
  </a>
</p>
<p align="center">
 <em>Select Camera as Input Source</em>
</p>

<p align="center">
  <b>OR</b>
</p>

<p align="center">
  <a href="https://github.com/JairajJangle/Open-CV-Catalogue">
    <img src="media/screenshot_select_input_file.jpg" alt="Input_File" width="512" >
  </a>
</p>
<p align="center">
  <em>Select Video/Image file as Input Source</em>
</p>

- Confirm the source selection by clicking on <img src="assets/done.png" alt="Logo" width="24"> button. 
- Select "Mirror" option to make the input Matrix mirrored along Y-axis

### 2. Select OpenCV Operation
<p align="center">
  <a href="https://github.com/JairajJangle/Open-CV-Catalogue">
    <img src="media/screenshot_menu.png" alt="Input_File" width="756" >
  </a>
</p>
<p align="center">
  <em>Select OpenCV Operation from the "Examples" Menu</em>
</p>

### 3. Adjusting OpenCV Operation parameters
<p align="center">
  <a href="https://github.com/JairajJangle/Open-CV-Catalogue">
    <img src="media/screenshot_adjust_params.png" alt="Input_File" width="756" >
  </a>
</p>
<p align="center">
  <em>GUI to adjust selected operation paramters is in the right side</em>
</p>

### 4. OpenCV Catalogue GUI summary
<p align="center">
  <a href="https://github.com/JairajJangle/Open-CV-Catalogue">
    <img src="media/picture_gui.jpg" alt="Input_File" width="756" >
  </a>
</p>
<p align="center">
  <em>Convenient GUI for parameter value adjustment</em>
</p>


- Each OpenCV operation has it's own parameter control GUI
- Changing parameters values reflect the changes in real time
- Clicking on <img src="assets/info.png" alt="Logo" width="22"> button at the top right corner besides the selected operation name will reveal the official OpenCV documentation for the selected operation in your internet browser.
- Various GUI elements are used:

   - Seekbar for definite ranging values
   - Check box for binary options
   - Text Input Field for indefinite values and decimal values
   - Radio Buttons to select one out of many options

## For Developers: Project Structure
```bash
.
├── assets
│   ├── app_logo.png
│   ├── demo_video.gif
│   ├── done.png
│   ├── done_sel.png
│   ├── info.png
│   ├── info_sel.png
│   ├── liberapay_donate.png
│   ├── minimize.png
│   ├── minimize_sel.png
│   ├── opencv_logo.png
│   ├── paypal_donate.png
│   ├── undock.png
│   └── undock_sel.png
├── CustomWidgets
│   ├── applyresetbuttonlayout.h
│   ├── ClickableLabel
│   │   ├── clickablelabel.cpp
│   │   └── clickablelabel.h
│   ├── errorlabel.h
│   ├── focusawarelineedit.cpp
│   ├── focusawarelineedit.h
│   ├── hybridadjustlayout.h
│   ├── HybridSlider
│   │   ├── hybridslider.cpp
│   │   ├── hybridslider.h
│   │   └── hybridslider.ui
│   ├── lineeditlayout.h
│   └── sliderlayout.h
├── LICENSE.txt
├── main.cpp
├── media
│   ├── picture_gui.jpg
│   ├── screenshot_adjust_params.png
│   ├── screenshot_canny.png
│   ├── screenshot_histogram.png
│   ├── screenshot_hsv.png
│   ├── screenshot_menu.png
│   ├── screenshot_select_input_camera.jpg
│   └── screenshot_select_input_file.jpg
├── OpenCV_Catalogue.pro
├── OpenCV_Catalogue.pro.user
├── OpenCVFunction
│   ├── backgroundsubtract.h
│   ├── blur.h
│   ├── cannyedge.h
│   ├── colorpicker.h
│   ├── colorspaces.h
│   ├── erosiondilation.h
│   ├── harriscornerdetector.h
│   ├── histogram.h
│   ├── houghcircles.h
│   ├── houghlines.h
│   ├── imageflip.h
│   └── thresholding.h
├── README.md
├── res.qrc
├── Utils
│   ├── baseconfigwidget.h
│   ├── captureinputsource.h
│   ├── constants.h
│   └── utils.h
└── Window
    ├── AboutDialog
    │   ├── aboutdialog.cpp
    │   ├── aboutdialog.h
    │   └── aboutdialog.ui
    └── MainWindow
        ├── mainwindow.cpp
        ├── mainwindow.h
        └── mainwindow.ui
```


_TODO:_ _For more examples, please refer to the [Documentation](https://example.com)_


<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/JairajJangle/Open-CV-Catalogue/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the GNU GPL v3 License. See `LICENSE` for more information.



<!-- CONTACT -->

## Contact

Jairaj Jangle - 🐦[@JairajJangle](https://twitter.com/JairajJangle) | ✉️ jairaj.jangle@gmail.com

Project Link: [https://github.com/JairajJangle/Open-CV-Catalogue](https://github.com/JairajJangle/Open-CV-Catalogue)

## Support the project development

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

<p align="center">
  <a href="https://liberapay.com/FutureJJ/donate">
    <img src="https://liberapay.com/assets/widgets/donate.svg" alt="Input_Cam" width="100" > 
  </a>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <a href="https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=PPXTF24LWH86U">
    <img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif" alt="Input_Cam" width="120" >
  </a>
</p>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [Img Shields](https://shields.io)
* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Pages](https://pages.github.com)
* [Best-README-Template](https://github.com/othneildrew/Best-README-Template)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/JairajJangle/Open-CV-Catalogue.svg?style=flat-square
[contributors-url]: https://github.com/JairajJangle/Open-CV-Catalogue/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/JairajJangle/Open-CV-Catalogue.svg?style=flat-square
[forks-url]: https://github.com/JairajJangle/Open-CV-Catalogue/network/members
[stars-shield]: https://img.shields.io/github/stars/JairajJangle/Open-CV-Catalogue.svg?style=flat-square
[stars-url]: https://github.com/JairajJangle/Open-CV-Catalogue/stargazers
[issues-shield]: https://img.shields.io/github/issues/JairajJangle/Open-CV-Catalogue.svg?style=flat-square
[issues-url]: https://github.com/JairajJangle/Open-CV-Catalogue/issues
[license-shield]: https://img.shields.io/github/license/JairajJangle/Open-CV-Catalogue.svg?style=flat-square
[license-url]: https://github.com/JairajJangle/Open-CV-Catalogue/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/jairaj-jangle-35aab3137/
[product-screenshot]: media/screenshot_canny.jpg

```

```