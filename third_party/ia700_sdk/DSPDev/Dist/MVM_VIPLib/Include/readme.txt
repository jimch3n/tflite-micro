
This folder contains the MachineLearning library interface header files.

Files
-----
MachineLearning.h: wrapper file including all other ones in this folder
MachineLearningDefs.h: type and other definitions specific to the MachineLearning library
MVM8bx4b.h  : 4-bit Matrix x 8-bit Vector Multiply interface
MVM16bx4b.h : 4-bit Matrix x 16-bit Vector Multiply interface
MVM8bx8b.h  : 8-bit Matrix x 8-bit Vector Multiply interface
MVM16bx8b.h : 8-bit Matrix x 16-bit Vector Multiply interface
MVM16bx16b.h : 16-bit Matrix x 16-bit Vector Multiply interface
MVMAfloat.h  : Afloat Matrix x Afloat Vector Multiply interface
MVMConvert.h : MVM input conversion (from Afloat type to 16/8 bit fixed-point) interface
MVMLayer.h   : Multi-layers (full-connected Neural Network for MVM) interface
ReLU.h    : ReLU (retified linear unit) interface
Sigmoid.h : sigmoid interface
SoftMax.h : softmax interface
Tanh.h    : hyperbolic tangent interface
VIP.h : Vector Inner Product (VIP) interface.