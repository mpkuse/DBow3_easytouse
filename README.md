# Easy to use DBOW

This is adopted from [https://github.com/rmsalinas/DBow3](https://github.com/rmsalinas/DBow3).
I do not lay any claims to its development. It is just a version of it which is easy
to use (atleast for me). Only the `CMakeLists.txt` file by me. This only depends on
OpenCV 3.

The publication to cite in case you use this work is:
```
@ARTICLE{GalvezTRO12, author={G'alvez-L'opez, Dorian and Tard'os, J. D.}, journal={IEEE Transactions on Robotics}, title={Bags of Binary Words for Fast Place Recognition in Image Sequences}, year={2012}, month={October}, volume={28}, number={5}, pages={1188--1197}, doi={10.1109/TRO.2012.2197158}, ISSN={1552-3098} } }
```

## File Structure
The core files all exist in folder `dbow3_core`. If you use this, you likely just need to `#include "DBoW3.h"`.

In the repo's root directory you will find a) 3 usage-examples, b) a pretrained vocabulary (orbvoc.dbow3), c) a few sample images.
- create_voc_step0.cpp : Given a descriptor's name viz. brisk, SURF etc, and a folder containing ton of images. This can extract features and feature-descriptors for each of the images and save all of it to disk for later processing.
- create_voc_step1.cpp : Using the descriptors computed from step0, does clustering on the features to get make a vocabulary.
- demo_general.cpp : Loads pretrained vocabulary and a few images and queries them from the DB.
- dbow3_test.cpp : A more realistic usage case. This is what a SLAM's loop closure module would look like. 

## How to build
```
mkdir build
cmake ..
make
```

## Get sample pretrained vocabulary
```
./get_orbvoc.sh
```


## TODO
It is rather crude to link all the .o with the executables (see the CMakeLists.txt).
I will accept a PR (pull-request) if you change this bit to
make a static-linked library (.a) for the core files.

## See Also 
Optimized version of DBOW with AVX/SSE instructions
https://github.com/rmsalinas/fbow


## Author
Manohar Kuse <mpkuse@connect.ust.hk><br/>
[rmsalinas](https://github.com/rmsalinas)<br/>
