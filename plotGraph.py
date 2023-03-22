##
# @file plotGraph.py
# @brief This file is used to plot the graph of the DCELs generated by the program.
# @author Suvigya Sharma (2020A7PS0140H)
# @author Anshul Kanodia (2020A7PS0174H)
# @bug No known bugs.
##

import matplotlib.pyplot as plt
# Remember the starting point should be repeated at the end of every DCEL just to accomodate to this script file.

with open("plotData.txt", 'r') as f:
    input = f.readlines()
    i = 0
    numberofGraph = 1
    while(i<len(input)):
        t1 = input[i].split(' ')
        t2 = input[i+1].split(' ')
        x = []
        y = []
        for j in t1:
            x.append(float(j))
        for j in t2:
            y.append(float(j))
        plt.plot(x, y, label = "plot " + str(numberofGraph))
        numberofGraph += 1
        i += 2

plt.xlabel('x axis')
plt.ylabel('y axis')
# plt.legend()
plt.title('Graph')
plt.show()
