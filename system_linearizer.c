#include "system_linearizer.h"

#include "matrix/matrix.h"

#include <stdlib.h>

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
  size_t maxSamplesNumber = Mat_GetHeight( lSystem->inputSamples );
  size_t inputsNumber = Mat_GetWidth( lSystem->inputSamples );
  size_t outputsNumber = Mat_GetWidth( lSystem->outputSamples );
  
  size_t sampleIndex = ( lSystem->samplesCount++ ) % maxSamplesNumber;
  
  for( size_t inputIndex = 0; inputIndex < inputsNumber; inputIndex++ )
    Mat_SetElement( lSystem->inputSamples, sampleIndex, inputIndex, inputsList[ inputIndex ] );
  
  for( size_t outputIndex = 0; outputIndex < outputsNumber; outputIndex++ )
    Mat_SetElement( lSystem->outputSamples, sampleIndex, outputIndex, outputsList[ outputIndex ] );
  
  return lSystem->samplesCount;
}

bool SystemLinearizer_Identify( LinearSystem lSystem, double* parametersList )
{
  size_t maxSamplesNumber = Mat_GetHeight( lSystem->inputSamples );
  
  if( lSystem->samplesCount < maxSamplesNumber ) return false;
  
  lSystem->aux = Mat_Dot( lSystem->inputSamples, MATRIX_TRANSPOSE, lSystem->inputSamples, MATRIX_KEEP, lSystem->aux );
  lSystem->aux = Mat_Inverse( lSystem->aux, lSystem->aux );
  lSystem->aux = Mat_Dot( Mat_Inverse( lSystem->aux, lSystem->aux ), MATRIX_KEEP, lSystem->aux, MATRIX_KEEP, lSystem->aux );
  lSystem->parameters = Mat_Dot( lSystem->aux, MATRIX_KEEP, lSystem->outputSamples, MATRIX_KEEP, lSystem->parameters );
  
  Mat_GetData( lSystem->parameters, parametersList );
  
  return true;
}

void SystemLinearizer_DeleteSystem( LinearSystem lSystem )
{
  Mat_Discard( lSystem->inputSamples );
  Mat_Discard( lSystem->outputSamples );
  Mat_Discard( lSystem->aux );
  Mat_Discard( lSystem->parameters );
  
  free( lSystem );
}
