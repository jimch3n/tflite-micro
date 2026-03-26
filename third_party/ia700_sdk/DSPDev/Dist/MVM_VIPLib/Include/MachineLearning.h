/************************************************************************//**
 * @file    MVM_VIPLib/Include/MachineLearning.h
 *
 * @brief   Machine learning interface file
 *
 * @details
 * <pre>
 *  Machine Learning Library contains optimized Matrix Vector
 *  Multiplication functions for different types of input\n
 *      Matrix Vector Multiplication : Currently supports below functions
 *          MVM8bx4b   : Matrix vector multiplication for 8 bits x 4 bits data
 *          MVM16bx4b  : Matrix vector multiplication for 16 bits x 4 bits data
 *          MVM8bx8b   : Matrix vector multiplication for 8 bits x 8 bits data
 *          MVM16bx8b  : Matrix vector multiplication for 16 bits x 8 bits data
 *          MVM16bx8bFast : Fast version of MVM16bx8b with minor restrictions
 *          MVM16bx16b : Matrix vector multiplication for 16 bits x 16 bits data
 *          MVMAfloat  : Matrix vector multiplication for Afloat data 
 *          MVMCovert  : Matrix vector converter for 16 bits and 8 bit inputs
 *          MVMLayer     Mutliple Layer Full Connected Neural Network for MVM
 *          Sigmoid    : Scalar and vector versions of sigmoid (logistic function:
 *                       1 / (1 + exp(-x))
 *          ReLU       : Scalar and vector versions of ReLU (Rectified Linear Unit)
 *          SoftMax    : Scalar and vector versions of SoftMax 
 *          Tanh       : Scalar and vector versions of Tanh (Hyperbolic tangent)
 * </pre>
 *
 * $DateTime: 2019/04/17 20:42:30 $
 * $Revision: #7 $
 *
 * @copyright Copyright © 2018 Knowles Electronics, LLC. All rights reserved.
 * THIS FILE IS SUBJECT TO THE TERMS OF YOUR SDK LICENSE WITH KNOWLES.
 * SEE ALSO License.txt
 *
 ****************************************************************************/
#ifndef __FILE_MACHINE_LEARNING_H__
#define __FILE_MACHINE_LEARNING_H__

/**************************************************************************//**
 * @defgroup hml_ml HemiLite Machine Learning library 
 * @{
 *****************************************************************************/


/****************************************************************************
 * Includes
 ****************************************************************************/
#include "MVM8bx4b.h"
#include "MVM16bx4b.h"
#include "MVM8bx8b.h"
#include "MVM16bx8b.h"
#include "MVM16bx8bFast.h"
#include "MVM16bx16b.h"
#include "MVMBiasAdd.h"
#include "MVMAfloat.h"
#include "MVMLayer.h"
#include "MVMConvert.h"
#include "Sigmoid.h"
#include "ReLU.h"
#include "SoftMax.h"
#include "Tanh.h"
#include "LSTM.h"
#include "Utils.h"
#include "Conv2D.h"
#include "Pool2D.h"
#include "VIP.h"



/**************************************************************************//**
 * @}
 *****************************************************************************/

#endif  /* __FILE_MACHINE_LEARNING_H__ */



/* End of File */

