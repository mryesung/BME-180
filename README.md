# Team BioSignus

## Team Members
### Gilberto Morales
Team Lead, Program Coordinator

### Firdose Rahman
Publication/Regulatory Specialist

### Yeseong Kim
Lead Programmer, Hardware Specialist

### Ilho Moon
Creative Director, Project Coordinator

## Project Mentors
### Dr. Daniel W. Shrey
Physician Mentor, Children's Hospital of Orange County

### Dr. Michael Chu
Engineering Mentor, CEO Makani Science

## Project Description
### Project Name: Respiratory Monitoring Patch for Newborns under Intensive Care
This project
(need to edit)

## Repository Description
This repository includes the codes used in Respiratory Monitoring Patch for Newborns under Intensive Care project.
The main goal of this code is to connect the device with Arduino in a wireless environment to save the measured sensor resistance
in a .csv file and plot the data.

### Tutorial
This project uses Arduino UNO Rev3 Microcontroller board as the processor. The Arduino circuit is based on a simple voltage divider, measuring the resistance of the sensor. The Arduino script need to be modified based on the fixed resistance value in the circuit to display correct resistance value.
The python script uses two threads for higher performance, one for plotting and other works, and another for reading data from the serial connection.

## Release
The .exe file in the release section is constructed with a python script using pyinstaller. The requirement to use this .exe file is to know the port number of the connected Arduino. Also, the user needs to type in the desired name of the .csv file to save the data.
