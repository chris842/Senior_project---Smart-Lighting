# Smart Lighting v1.0.0
This is the Smart Lighting project for my senior project.

DESCRIPTION
---------------------------------------------------------
This project includes the details for the smart lighting project, such as how it will function,
the specific componenets of the project, as well as some additional features such as the housing
design and PCB designs.

The programming languaged used for the project was C++, which was written using VSCode and PlatformIO
(More details on the code can be found on the main.cpp file). The microcontroller used for this project
was the ESP32 devkit v1, allowing for wireless connections to be made.

ADDITIONAL NOTES
----------------------------------------------------------
For the PCB design, there were some components that I had to customize myself, as KiCAD did not have the 
specific componenets that I had in mind. These additional symbols and components should be included in the
ZIP file.
Also note that the app used to communicate with the ESP32 is Blynk. Currently, the app that I had created
cannot be published as a standalone, as the BLE features for Blynk is still in its prototyping phase. In order to
recreate this project, using the Blynk app is necessary to have the manual control feature operational.
