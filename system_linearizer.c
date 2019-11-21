/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//  Copyright (c) 2019 Leonardo Consoni <leonardojc@protonmail.com>            //
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


#include "system_linearizer.h"

#include "matrix/matrix.h"

#include <stdlib.h>
#include <stdio.h>

struct _LinearSystemData
{
  Matrix inputSamples;
  Matrix outputSamples;
  Matrix aux;
  Matrix parameters;
  size_t samplesCount;
};

LinearSystem SystemLinearizer_CreateSystem( size_t inputsNumber, size_t outputsNumber, size_t samplesNumber )
{
  if( inputsNumber > LINEARIZATION_MAX_VARIABLES || outputsNumber > LINEARIZATION_MAX_VARIABLES ) return NULL;
  if( samplesNumber > LINEARIZATION_MAX_SAMPLES ) return NULL;
  
  LinearSystem lSystem = (LinearSystem) malloc( sizeof(LinearSystemData) );
  
  lSystem->inputSamples = Mat_Create( NULL, samplesNumber, inputsNumber );
  lSystem->outputSamples = Mat_Create( NULL, samplesNumber, outputsNumber );
  lSystem->aux = Mat_Create( NULL, inputsNumber, samplesNumber );
  lSystem->parameters = Mat_Create( NULL, inputsNumber, outputsNumber );
  lSystem->samplesCount = 0;
  
  return lSystem;
}

size_t SystemLinearizer_AddSample( LinearSystem lSystem, double* inputsList, double* outputsList )
{
  size_t samplesNumber = Mat_GetHeight( lSystem->inputSamples );
  size_t inputsNumber = Mat_GetWidth( lSystem->inputSamples );
  size_t outputsNumber = Mat_GetWidth( lSystem->outputSamples );
  
  size_t sampleIndex = ( lSystem->samplesCount++ ) % samplesNumber;
  
  for( size_t inputIndex = 0; inputIndex < inputsNumber; inputIndex++ )
    Mat_SetElement( lSystem->inputSamples, sampleIndex, inputIndex, inputsList[ inputIndex ] );
  
  for( size_t outputIndex = 0; outputIndex < outputsNumber; outputIndex++ )
    Mat_SetElement( lSystem->outputSamples, sampleIndex, outputIndex, outputsList[ outputIndex ] );
  
  return lSystem->samplesCount;
}

bool SystemLinearizer_Identify( LinearSystem lSystem, double* parametersList )
{
  Mat_Dot( lSystem->inputSamples, MATRIX_TRANSPOSE, lSystem->inputSamples, MATRIX_KEEP, lSystem->aux );
  if( Mat_Inverse( lSystem->aux, lSystem->aux ) == NULL ) return false;
  Mat_Dot( lSystem->aux, MATRIX_KEEP, lSystem->inputSamples, MATRIX_TRANSPOSE, lSystem->aux );
  Mat_Dot( lSystem->aux, MATRIX_KEEP, lSystem->outputSamples, MATRIX_KEEP, lSystem->parameters );
  Mat_GetData( lSystem->parameters, parametersList );
  return true;
}

void SystemLinearizer_Reset( LinearSystem lSystem )
{
  Mat_Clear( lSystem->inputSamples );
  Mat_Clear( lSystem->outputSamples );
  Mat_Clear( lSystem->aux );
  Mat_Clear( lSystem->parameters );
  lSystem->samplesCount = 0;
}

void SystemLinearizer_DeleteSystem( LinearSystem lSystem )
{
  Mat_Discard( lSystem->inputSamples );
  Mat_Discard( lSystem->outputSamples );
  Mat_Discard( lSystem->aux );
  Mat_Discard( lSystem->parameters );
  
  free( lSystem );
}
