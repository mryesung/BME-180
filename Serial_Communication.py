#!/usr/bin/env python
# coding: utf-8

# In[14]:


#import required modules
import serial
from datetime import datetime
import platform
import time
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

get_ipython().run_line_magic('matplotlib', 'tk')


# In[15]:


#set serial connection

OS = platform.system()

if OS == 'Windows':
    PortBase = "COM"
elif OS == 'Darwin':
    PortBase = '/ev/tty.usbmodem'
else:
    print("Not supported OS")


print("Type in your COM port Number")
print("ex) if COM3, type in 3")
PortName = PortBase + input()
BaudRate = 9600

Arduino = serial.Serial(PortName, BaudRate)


# In[16]:


#to create exe file

#convert to .py
#pip install nbconvert
#jupyter nbconvert --to script name.ipynb

#convert to .exe
#pip install pyinstaller
#pyinstaller name.py


# In[17]:


#create csv file
print("Type in the desired name of the .csv data file")
print("ex) 0001")
print("if there is a csv file with same, the original file will be replaced!")
FileName = input() + ".csv"


# In[18]:


#read data from arduino serial monitor and save in list of data
data = np.array([])

print("How much minutes will you record the data?")
seconds = float(input()) * 60

#delayTime is in seconds
#follwing is sampling frequency of 10
delayTime = 0.1


# In[6]:


plt.ion()

fig, ax = plt.subplots(figsize = (10, 8))
line, = ax.plot(data)

plt.ylabel('Rsensor')


# In[7]:


while seconds > 0:
    #Arduino will print the Rsensor value in the Serial Monitor
    #only when python script requires to do so by printing 'w'
    Arduino.write(b'w')
    
    SerialData = float(Arduino.readline().decode('utf-8'))
    data = np.append(data, [SerialData, datetime.now().strftime("%H : %M : %S . %f")])
    
    line.set_ydata(data[:,1])
    fig.canvas.draw()
    fig.canvas.flush_events()
    
    time.sleep(delayTime)
    seconds -= delayTime


# In[ ]:


#import numpy if we need additional mathematical calculations


# In[ ]:


#write data to the csv file
columnNames = ['Rsensor', 'Time']

dataFile = pd.DataFrame(data, columns = columnNames)
dataFile.to_csv(FileName, index = False)


# In[13]:


#disconnect the Arduino
Arduino.close()

print("You will need to change the cell format to 'hh:mm:ss.000'")


# In[ ]:




