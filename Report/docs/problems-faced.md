---
sidebar_position: 3
---
# Problems Faced

## 1. Segmentation faults: 
During the course of the algorithm implementation, there were many instances where we tried to access out-of-bound indices, which led to the program running into a segmentation fault. To counter this, we printed success messages after every step to identify the location of the segmentation fault.
***
## 2. Linker issues:
The problem with the linker was that it was unable to find the functions of the `DCEL` class. To resolve the issue, we had to configure the compilation command to include function definitions from `definitions.cpp` file.
***
## 3. Generating test cases:
This was the major problem as generating test cases with polygons of more than 15 vertices is tough to be done manually. To resolve the issue, we referred to previous works available on Github and also used datasets available online. This even consisted of datasets that represented countries' borders approximately on a Cartesian plane. Look into the  <samp>References</samp> section for more details.
***
## 4. Rotating a vector: 
The main confusion we had what should be done if the decomposed polygon given by the algorithm consisted of two vertices only. To rectify the issue, we decided to change the starting vertex of our traversal, and in order to achieve that, rotated the given input vector in a cyclic manner.
***
## 5. Merging polygons: 
While merging two polygons into one, the edges of the two polygons were unable to be listed in a proper sequence. As a result, the new polygon after merging included additional edges and deleted some of the original edges. We kept on rotating the vector data structure containing the edges until the common edge of the two polygons mentioned was at the 0th index of the vector. The issue of sequencing in polygons while merging was rectified thus.