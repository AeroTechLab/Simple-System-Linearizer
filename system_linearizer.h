/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//  Copyright (c) 2019-2020 Leonardo Consoni <leonardojc@protonmail.com>       //
//                                                                             //
//  This file is part of Simple-System-Linearizer.                             //
//                                                                             //
//  Simple-System-Linearizer is free software: you can redistribute it         //
//  and/or modify it under the terms of the GNU Lesser General Public License  //
//  as published by the Free Software Foundation, either version 3 of the      //
//  License, or (at your option) any later version.                            //
//                                                                             //
//  Simple-System-Linearizer is distributed in the hope that it will           //
//  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty     //
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            //
//  GNU Lesser General Public License for more details.                        //
//                                                                             //
//  You should have received a copy of the GNU Lesser General Public License   //
//  along with Simple-System-Linearizer.                                       //
//  If not, see <http://www.gnu.org/licenses/>.                                //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////


/// @file system_linearizer.h
/// @brief System Linearizer implementation
///
/// Estimate parameters for linear regression of a system using least squares method to solve X*B = Y

#ifndef SYSTEM_LINEARIZER_H
#define SYSTEM_LINEARIZER_H

#include <stddef.h>
#include <stdbool.h>

#define LINEARIZATION_MAX_VARIABLES 10		      ///< Maximum number of inputs, outputs or linearization coefficients
#define LINEARIZATION_MAX_SAMPLES 200		      ///< Maximum number of samples for linear regression

typedef struct _LinearSystemData LinearSystemData;    ///< Single linear system sampling data structure
typedef LinearSystemData* LinearSystem;               ///< Opaque reference to linear system data structure

/// @brief Creates and initializes sampling data matrices for linearization
/// @param[in] inputsNumber number of columns for the X input samples matrix
/// @param[in] outputsNumber number of columns for the Y output samples matrix
/// @param[in] maxSamplesNumber max number of rows for X and Y matrices
/// @return reference to created linear system
LinearSystem SystemLinearizer_CreateSystem( size_t inputsNumber, size_t outputsNumber, size_t maxSamplesNumber );

/// @brief Add new single input-output sample pair to the sampling matrices 
/// @param[in] lSystem reference to linear system
/// @param inputsList array of inputs for the added sample (X matrix row)
/// @param outputsList array of outputs for the added sample (Y matrix row)
/// @return total number of added samples (first ones are overwritten once the maximum is reached)
size_t SystemLinearizer_AddSample( LinearSystem lSystem, double* inputsList, double* outputsList );

/// @brief Estimate linearization parameters from the previously provided data samples
/// @param[in] lSystem reference to linear system
/// @param[out] parametersList array to store estimated linearization parameters (size of nº inputs x nº outputs)
/// @return true on successful calculation, false otherwise
bool SystemLinearizer_Identify( LinearSystem lSystem, double* parametersList );

/// @brief Clear/zero out the internally stored data samples
/// @param[in] lSystem reference to linear system
void SystemLinearizer_Reset( LinearSystem lSystem );

/// @brief Deallocates memory for internal linearizer data
/// @param[in] lSystem reference to linear system
void SystemLinearizer_DeleteSystem( LinearSystem lSystem );


#endif // SYSTEM_LINEARIZER_H
