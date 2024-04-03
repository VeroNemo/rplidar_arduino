# 3D model of the room with Slamtec RPLIDAR and Arduino Mega

This project is practical part of my master thesis at University of Constantine the Philosopher in Nitra, Slovakia. 

## Description of project

Project consist of implementing this features:
* creating communication with RPLidar and Arduino
* scanning the room 2x with 20 seconds pause between
* preprocessing lidar data -> from distance and angle to cartesian coordinates (with graph)
* reducing noisy points -> applying 4 algorithms: Moving Average, Savitzky-Golay filter, Gaussian filter and Median filtering (with graph)
* applying RANSAC algorithm for line fitting (with graph)
* applying RANSAC algorithm for plane fitting and generate room dimensions (with graph)
* generating table with dimensions of the room as input to Unity script
* creating Unity script for developing 3D model of the room

## Hardware & Software

* Slamtec RPLIDAR A2M12
* Arduino Mega 2560
* 5V power supply

## Connection of RPLIDAR and Arduino

RPLIDAR **RX** => Arduino **TX**   
RPLIDAR **TX** => Arduino **RX**   
RPLIDAR **PWM** => Arduino **PWM 3**

Make sure you upload *diplomovka.ino* file to your Arduino board at first and don't forget to put *RPLidarDriver* into Arduino libraries.

## Scanning
Make sure you put there a correct serial port and baud rate of your sensor. 

```python
connectionToRPLIDAR(serial_port: str, baud_rate: int)
#Linux   : "/dev/ttyUSB0"
#MacOS   : "/dev/cu.SLAB_USBtoUART"
#Windows : "COM5"

startScan()
```
*startScan()* will return 2 dataframe with scanning data.

## Preprocessing
Return value of method will be dataframe. It also show graph of point cloud. 

```python
df = preprocessing(data: str)
```

## Reducing noisy points 
You can choose from 4 different filtering algorithms. Return values in each one are newly X and Y points. Every algorithm will also show graph. Entry datas are dataframe and parameter to algorithm.

```python
movingAverage(data: [], rolling_number: int)
SavitzkyGolayFilter(data: [], window_length: int)
GaussianFilter(data: [], sigma: float)
medianFilter(data: [], kernel_size: int)
```

## RANSAC algorithm 
RANSAC algorithm for finding lines will return number of lines find and show them on graph.

```python
RANSAC_for_lines(min_sample: int, max_distance: int, min_inliers: int, data: [])
```
RANSAC algorithm for finding planes will return width and height of plane and show plane on graph.

```python
RANSAC_for_planes(x: [], y: [], z: [])
```

## Generating text file with dimensions
Data will be save where you want it. For Unity, write path into Assets folder, for example: *./Unity/3D_Model/Assets/lidarData.txt*

```python
generateDimensionsForUnity(save_path: str, width: float, height: float, length: float)
```

## Unity script
Make sure you copy *CreateRoom.cs* file into Unity scripts folder. 
