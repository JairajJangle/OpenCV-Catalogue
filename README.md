 <!-- PROJECT SHIELDS -->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![Build Status][build-status-shield]][build-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->

<br />

<p align="center">
  <a href="https://github.com/JairajJangle/Open-CV-Catalogue">
    <img src="assets/app_logo.png" alt="Logo" width="120">
  </a>



  <h3 align="center">OpenCV Catalogue</h3>

  <p align="center">
    A GUI application to view and test all OpenCV operations
    <br />
    <a href="https://github.com/JairajJangle/Open-CV-Catalogue"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/JairajJangle/Open-CV-Catalogue/releases">Download</a>
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
  * [Run the standalone application](#run-the-standalone-application)
* [Application usage](#application-usage)
  * [1. Select Input source](#1-select-input-source)
  * [2. Select and Chain OpenCV Operations](#2-select-and-chain-opencv-operations)
  * [3. Adjusting OpenCV Operation parameters](#3-adjusting-opencv-operation-parameters)
  * [4. Record and Export Input-Output Stream](#4-record-and-export-input-output-stream)
  * [5. OpenCV Catalogue GUI summary](#5-opencv-catalogue-gui-summary)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Support the project development](#support-the-project-development)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->

## About The Project
<p align="center">
    <img src="assets/demo_video.gif" alt="Demo-Video-GIF" width="900" >
  </a>
</p>




<p align="center">
 <em>OpenCV Catalogue Application Demo Video illustrating isolation of Red color</em>
</p>




OpenCV Catalogue is a stand alone application which is made to let you test any OpenCV operation without a need to code. This awesome GUI application lets you control all parameters of an OpenCV operation using GUI elements such as Sliders/Seekbars, Input Text Box, Radio Buttons and Check Boxes. You can even form a series or chain of OpenCV operations, control individual operation parameters and view the output. Exporting realtime output is also supported. 

This project is still under development and as of now covers some primitive OpenCV operations. But, with the power of open sourcing, this application can be made to cover all the OpenCV operations, very soon.

This repository also contain release packages with **standalone** GUI application which anyone can run it on their Linux system. OpenCV Catalogue is primarily saves user's time with figuring out what parameter causes what changes on the output.

Features:
* Select camera, image and video file, network stream as input source
* Real time ajustment of paramters of selected OpenCV operation
* Chaining of various OpenCV operations in a sequence
* Provides link to official OpenCV documentation to selected OpenCV operation
* Record and export output
* View output of each operation in the chain using Exploded View (Experimental)

Planned features:
* OpenCV machine learning operations
* Support for CUDA based operations
* Two-Dimensional chaining of OpenCV operations

### Built With

* [C++](https://devdocs.io/cpp/)
* [QT](https://www.qt.io/)
* [OpenCV](https://opencv.org/) with [OpenCV Extra Modules](https://github.com/opencv/opencv_contrib)



<!-- GETTING STARTED -->

## Getting Started

### Run the standalone application
```sh
tar xjf opencv-catalogue.tar.bz2 
cd <OpenCV_Catalogue.sh file location>
chmod +x OpenCV_Catalogue.sh
./OpenCV_Catalogue.sh
```



<!-- USAGE EXAMPLES -->

## Application usage

### 1. Select Input source
<p align="center">
    <img src="media/screenshot_select_input_camera.png" alt="Input_Cam" width="225" >
    <img src="media/screenshot_select_input_file.png" alt="Input_File" width="225" >
    <img src="media/screenshot_select_input_network.png" alt="Input_Network" width="225" >
</p>
<p align="center">
  <em>Select one of the above input sources</em>
</p>

<p align="center">
    <img src="media/screenshot_source_apply.png" alt="Input_Network" width="800" >
</p>


- Confirm the source selection by clicking on <img src="assets/done.png" alt="Logo" width="24"> button. 
- Select "Mirror" option to make the input Matrix mirrored along Y-axis

### 2. Select and Chain OpenCV Operations
<p align="center">
    <img src="media/screenshot_menu.png" alt="Chain_Ops" width="1020" >
  </a>
</p>
<p align="center">
  <em>Select OpenCV Operation from the "Examples" Menu</em>
</p>


In the *Select and Chain OpenCV Operations box*(left side), click on:

![](media/plus_button.png)	button to add a OpenCV function in chain

![](media/minus_button.png)	button to remove the selected OpenCV function from chain

 ![](media/radio_button.png)	radio button to select the OpenCV operation for it's parameter adjustment

**NOTE:** on adding an incompatible OpenCV Operation to the chain, it will be automatically removed from the chain with a pop up dialog stating the error.


### 3. Adjusting OpenCV Operation parameters
<p align="center">
    <img src="media/screenshot_adjust_params.png" alt="Adjust_Params" width="756" >
  </a>
</p>
<p align="center">
  <em>GUI to adjust selected operation paramters is in the right side</em>
</p>


### 4. Record and Export Input-Output Stream<img align="right" width="200" height="200" src="media/screenshot_export.png"> 

- Select folder where you want to export the output to.
- Click on capture image(camera button) to capture and save current frame of input and output image.
- Or you can also start video recording to export the video of input and output in realtime, click on stop button to end and save the video recording. 

<!-- TODO: Add a screenshot here -->

### 5. OpenCV Catalogue GUI summary

<p align="center">
    <img src="media/picture_gui.png" alt="Gallery" width="850" >
  </a>
</p>
<p align="center">
  <em>Convenient GUI for parameter value adjustment</em>
</p>


- Each OpenCV operation has it's own parameter control GUI
- **Changing parameters** values reflect the changes in **real time**
- Clicking on <img src="assets/info.png" alt="Logo" width="22"> button at the top right corner besides the selected operation name will reveal the official OpenCV documentation for the selected operation in your internet browser.
- Click on **Switch Theme** button at the bottom right corner to swtich between Dark Mode and Light Mode Theme
- Two themes available: Dark and Light
- Various GUI elements are used:

   - **Seekbar** for definite ranging values
   - **Check box** for binary options
   - **Text Input Field** for indefinite values and decimal values
   - **Radio Buttons** to select one out of many options



<!-- ROADMAP -->

## Roadmap

See the [open issues](https://github.com/JairajJangle/Open-CV-Catalogue/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->

## Contributing

Check [CONTRIBUTING.md](https://github.com/JairajJangle/Open-CV-Catalogue/blob/master/CONTRIBUTING.md). 



<!-- LICENSE -->

## License

Distributed under the [GNU GPL v3 License](https://github.com/JairajJangle/Open-CV-Catalogue/blob/master/LICENSE.txt). 



<!-- CONTACT -->

## Contact

Jairaj Jangle - 🐦[@JairajJangle](https://twitter.com/JairajJangle) | ✉️ jairaj.jangle@gmail.com

Project Link: [https://github.com/JairajJangle/Open-CV-Catalogue](https://github.com/JairajJangle/Open-CV-Catalogue)

## Support the project development

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

<p align="center" valign="center">
  <a href="https://liberapay.com/FutureJJ/donate">
    <img src="https://liberapay.com/assets/widgets/donate.svg" alt="LiberPay_Donation_Button" width="100" > 
  </a>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <a href="https://github.com/JairajJangle/OpenCV-Catalogue/blob/master/.github/Jairaj_Jangle_Google_Pay_UPI_QR_Code.jpg">
    <img src="assets/upi.png" alt="Paypal_Donation_Button" width="100" >
  </a>
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <a href="https://www.paypal.com/paypalme/jairajjangle001/usd">
    <img src="assets/paypal_donate.png" alt="Paypal_Donation_Button" width="100" >
  </a>
</p>





&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

<!-- ACKNOWLEDGEMENTS -->

## Acknowledgements
* [Img Shields](https://shields.io)
* [QDarkStylesheet](https://github.com/ColinDuquesnoy/QDarkStyleSheet) - [The MIT License](https://github.com/ColinDuquesnoy/QDarkStyleSheet/blob/master/LICENSE.rst)
* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Pages](https://pages.github.com)
* [Best-README-Template](https://github.com/othneildrew/Best-README-Template)
* [Typora Markdown Editor](https://typora.io/)
* [briandk - CONTRIBUTING.md](https://gist.github.com/briandk/3d2e8b3ec8daf5a27a62)



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
[build-status-shield]: https://github.com/JairajJangle/OpenCV-Catalogue/actions/workflows/github-actions-demo.yml/badge.svg
[build-url]: https://github.com/JairajJangle/OpenCV-Catalogue/actions
[license-url]: https://github.com/JairajJangle/Open-CV-Catalogue/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/jairaj-jangle-35aab3137/
[product-screenshot]: media/screenshot_canny.jpg
