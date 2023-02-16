import serial
from datetime import datetime
import platform
import time
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation

class RealTimePlot:
    def animate(self, i, plotdata, ser, savedata):
        #require arduino to analogRead
        ser.write(b'w')

        #get the Rsensor value in float
        SerialData = float(ser.readline().decode('utf-8'))

        #save the Rsensor value in both plotdata list and savedata list
        savedata.append([SerialData, datetime.now().strftime("%H:%M:%S.%f")])
        plotdata.append(SerialData)

        #Fix the list size to certain value
        plotdata = plotdata[-50:]

        #clear last data frame
        ax.clear()

        #plot new data frame
        self.getPlotFormat()
        ax.plot(plotdata)

    def getPlotFormat(self):
        ax.set_ylim([0,100]) #change to 2,13 for strain sensor
        ax.set_ylabel('Rsensor')

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
BaudRate = 9600

Arduino = serial.Serial(PortName, BaudRate)

#get File Name

print("Type in the desired name of the .csv data file")
print("ex) 0001")
print("If there is a csv file with same name, the original file will be replaced!")
FileName = input() + ".csv"

#close the plot when the user wants to
print("You may close the plot window to end the program and save the data")
print("You will need to change the cell format of Time to 'hh:mm:ss.000'")

#data to save in .csv file
dataSave = []

#real time plotting
dataPlot = []

fig = plt.figure()
ax = fig.add_subplot(111)

plot_object = RealTimePlot()

ani = animation.FuncAnimation(fig, plot_object.animate, frames = 100, fargs=(dataPlot, Arduino, dataSave), interval = 50, repeat = True)

plt.show()

#save data to .csv file
columnNames = ['Rsensor', 'Time']

dataFile = pd.DataFrame(dataSave, columns = columnNames)
dataFile.to_csv(FileName, index = False)

#close the serial connection
Arduino.close()
