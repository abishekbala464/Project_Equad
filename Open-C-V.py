import cv2 as cv
import numpy as np

#///////////////////////TO find the edges of the image///////////////////////////////

#////////coordinates of the image/////////
def coord(img):
    gray=cv.cvtColor(img,cv.COLOR_BGR2GRAY) #hsv
    blur=cv.GaussianBlur(gray,(7,7), cv.BORDER_DEFAULT) #reflect
    canny=cv.Canny(blur,50,100)
    indices = np.where(canny != [0])
    coordinates = zip(indices[0], indices[1])
    lst=list(coordinates)
    return lst
#//////////To sort the coordinates and only take the left most coordinate to avoid noise////////
def cont(lst):
    y=[]
    for i in range(len(lst)):
        y1=lst[i][1]
        if y1 not in y:
            y+=[y1]
    l=[]
    for i in y:
        x=[]
        for j in range(len(lst)):

            if i==lst[j][1]:
                x+=[lst[j][0]]
        x.sort()
        l+=[[x[0],i]]
    return l
def Sort(ListOfList):
    length = len(ListOfList)
    for i in range(0, length):
        for j in range(0, length-i-1):
            if (ListOfList[j][1] > ListOfList[j + 1][1]):
                temp = ListOfList[j]
                ListOfList[j] = ListOfList[j + 1]
                ListOfList[j + 1] = temp
    return ListOfList

def sort_by_x_coordinate(lst):
    return sorted(lst, key=lambda x: x[0])

#///to convert the pixels into mm (multiply it to the 0.26458333 x 10 (for getting the accurate integer values to be given to the controller))/////

def pixels_to_mm(lst):
    distance = []
    for item in lst:
        distance.append((int (item[0] * 2.6458333), int(item[1] *2.6458333)))
    return distance

def main():
    img = cv.imread(r'I:\OpenCv\carvin_project\bottle.jpg')
    lst=coord(img)#coordinates
    #print(lst)
    l=cont(lst)#leftmost coords
    lsort=sort_by_x_coordinate(l)
    distance = pixels_to_mm(lsort)
    print(len(distance))
    a=str(distance)
    b=a.replace('[','{')
    c=b.replace(']','}')
    d=c.replace(')','}')
    e=d.replace('(','{')
    f=e.replace(' ','')
    print(f)
