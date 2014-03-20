# Raspi Robot Color Tracker
# Saint Paul College ACM
# Revision 1.1
# 3/10/2014: Conversion to cv2 and streamlined blob tracking
# 3/20/2014: Cleaned up and commented

import cv2
import numpy
import serial

# Set up and open serial connection with arduino
ser_tx = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
ser_tx.open()

def MaskMaker(img):

    # BGR to HSV image
    imgHSV = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # Mask for HSV image set to desired color
    # Lower/upper Hue Saturation and Value variables
    lower = numpy.array([46,60,87])
    upper = numpy.array([80,173,255])

    # Applying variables to show only objects that fall in this color range 
    imgMask = cv2.inRange(imgHSV, lower, upper)

    return imgMask
    
# captured image size, change to whatever you want
# Less resolution to make life easier on raspberry pi
"""Note: if you change the image size, make sure you change
   the scale that keeps the integers being set to the arduino within
   the bounds of 0 to 255"""
width = 320
height = 240

# Start capturing video
camera = cv2.VideoCapture(0)

# Over-write default captured image size
camera.set(3, width)
camera.set(4, height)
              
while 1:
    
    # Read in a frame from camera
    success, frame = camera.read()

    # Apply a blur filter to smooth out the image and remove noise
    blurFrame = cv2.medianBlur(frame,5)
    
    # Call the masking function
    imgMasked = MaskMaker(blurFrame)
        
    #Get the contours in masked image
    contours, hierarchy = cv2.findContours(imgMasked,cv2.RETR_LIST,cv2.CHAIN_APPROX_SIMPLE)
 
    #Contour with largest area will be used
    biggest = 0
    for blob in contours:
        area = cv2.contourArea(blob)
        if area > biggest:
            biggest = area
            lg_blob = blob

        
    # If the blob is of sufficient size: calculate center of blob
    # and send it to the Arduino
    if(biggest > 200):
        
        #Find the coordinates of blob's center in relation to frame
        M = cv2.moments(lg_blob)
        posX = int(M['m10']/M['m00'])
            
        # Scale for 0 to 255 since field of vision is 0 to 320
        """Be sure to change this if you change the resolution of the image"""
        posX = int(posX * 0.797) 

        # Send the position of object to arduino (0 - 254) 
        ser_tx.write(chr(posX))
        
        # Uncomment this for terminal debugging 
        print 'x: ' + str(posX)

    else:
        # Arduino program will recognize 255 as a stop command
        # If no object to track or it is too far away, stop will be sent
        ser_tx.write(chr(255))

        # Uncomment this for terminal debugging
        print 'stop'
