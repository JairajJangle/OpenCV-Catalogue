Get started with contributing to the OpenCV Catalogue

## For Developers 🧑‍💻

### Prerequisites for building the source and contributing to the project

* [Install OpenCV](https://docs.opencv.org/trunk/df/d65/tutorial_table_of_content_introduction.html): Go for 3.x+ version
* [Install QT libs + QT Creator](https://www.qt.io/download-open-source)
* C++ 17+
* For development, supported platforms: Linux, MacOS, Windows


- Please respect the project file structure while making pull requests and maintain a consistent coding style

- If you find that the project structure should be amended to make it more organized please do make a pull request  or create an issue and explain the need in detail

- Update the README.md with details of changes if necessary

  

## Contributing 🙌

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



### How do I add a new OpenCV Operation? 🤔

1. Create <operationname.h> file in OpenCVFunction
2. Inherit the class from `BaseConfigWidget`
3. Assign operationName and moreInfoLink in contructor
4. Override `getProcessedImage(...)` with exception handling
5. Override `initWidget()` and populate `BaseConfigWidget::vBox` with parameter adjustment widgets
6. Super call to `BaseConfigWidget::initWidget()` in the end of overriden `initWidget()`
7. In overriden `getProcessedImage(...)` get parameter values from widgets and apply to the OpenCV operation. 
8. Return the processed image from `getProcessedImage(...)`
9. Now, in mainwindow.h, import <operationname.h> and add Operation Code for the newly added operation in `OPCodes` enum.
10. In mainwindow.cpp, add case for the new `OPCodes` value in `addOperation(...)`, append the object of the new operation to `baseConfigWidgetChain`.
11. Done, that's it.  The new operation should be available in he UI. 🎉



## Report bugs using Github's [issues](https://github.com/JairajJangle/OpenCV-Catalogue/issues) 🐞

We use GitHub issues to track public bugs. Report a bug by [opening a new issue](https://github.com/JairajJangle/OpenCV-Catalogue/issues/new/choose); it's that easy!



## Write bug reports with detail, background, and sample code

**Great Bug Reports** tend to have:

- A quick summary and/or background
- Steps to reproduce
  - Be specific!
  - Give sample code if you can.
- What you expected would happen
- What actually happens
- Notes (possibly including why you think this might be happening, or stuff you tried that didn't work)

People *love* thorough bug reports. I'm not even kidding.



## License 📜

By contributing, you agree that your contributions will be licensed under its GNU GPLv3 License.