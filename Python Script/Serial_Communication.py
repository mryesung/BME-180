import serial
from datetime import datetime
import platform
import time
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from threading import Thread
import struct

class RealTimePlot:
    def __init__(self, PortName, FileName, fig):
        self.fileName = FileName
        self.baudRate = 9600

        self.isConnected = False
        self.isReceiving = False
        #connect to serial
        try:
            self.ser = serial.Serial(PortName, self.baudRate)
            self.isConnected = True
        except:
            print("Failed to connect with the serial port")

        #list to store data
        self.dataPlot = []
        self.dataSave = []

        #figure
        self.ax = fig.add_subplot(111)
        self.getPlotFormat()

        #reading data
        self.readData = bytearray(4)

        #thread
        self.thread = None

    def append(self, serialData):
        #save the Rsensor value in both plotdata list and savedata list
        self.dataPlot.append(serialData)
        self.dataSave.append([serialData, datetime.now().strftime("%H:%M:%S.%f")])

        #fix the list size to certain value
        self.dataPlot = self.dataPlot[-100:]

    def readThread(self):
        #main thread handles plotting and other works
        #while the second thread will be responsible for reading serial data
        #buffer time
        time.sleep(1.0)

        self.ser.reset_input_buffer()

        #read data
        while self.isConnected:
            self.ser.readinto(self.readData)
            self.isReceiving = True

    def readStart(self):
        if self.thread == None:
            self.thread = Thread(target = self.readThread)
            self.thread.start()

            while self.isReceiving != True:
                time.sleep(0.1)

    def readLine(self):
        serialData, = struct.unpack('f', self.readData) #'f' for float data type byte

        self.append(serialData)

    def animate(self, i):
        self.readLine()

        #clear last data frame
        self.ax.clear()

        #plot new data frame
        self.ax.plot(self.dataPlot)

    def getPlotFormat(self):
        self.ax.set_ylim([0,100]) #change to 2,13 for strain sensor
        self.ax.set_ylabel('Rsensor')

    def save(self):
        #save data to csv
        dataFile = pd.DataFrame(self.dataSave, columns = ['Rsensor', 'Time'])
        dataFile.to_csv(self.fileName, index = False)

    def close(self):
        self.isConnected = False

        self.thread.join()

        #disconnect serial
        self.ser.flush()
        self.ser.close()

        self.save()

def main():
    #set serial connection
    OS = platform.system()

    if OS == 'Windows':
        PortBase = "COM"
    elif OS == 'Darwin':
        PortBase = '/ev/tty.usbmodem'
    else:
        print("Not supported OS")

    print("Type in your Port Number")
    print("ex) if COM3, type in 3")
    PortName = PortBase + input()

    #get File Name
    print("Type in the desired name of the .csv data file")
    print("ex) 0001")
    print("If there is a csv file with same name, the original file will be replaced!")
    FileName = input() + ".csv"

    #close the plot when the user wants to
    print("You may close the plot window to end the program and save the data")
    print("You will need to change the cell format of Time to 'hh:mm:ss.000'")

    #create figure
    fig = plt.figure()

    #create object
    Arduino = RealTimePlot(PortName, FileName, fig)
    Arduino.readStart()

    #real time plotting with loop
    ani = animation.FuncAnimation(fig, Arduino.animate, frames = 100, interval = 10, repeat = True)

    plt.show()

    #close the serial connection
    Arduino.close()

if __name__ == '__main__':
    main()
