#include "system_linearizer.h"

#include "fcntl.h"
#include "stdio.h"

int main()
{
  FILE* samplesFile = fopen( "samples.txt", "r" );
  
  LinearSystem lSystem = SystemLinearizer_CreateSystem( 3, 1, LINEARIZATION_MAX_SAMPLES );
  
  double time = 0.0;
  double setpoint = 0.0;
  double inputsList[ 3 ] = { 0.0 };
  double outputsList[ 1 ] = { 0.0 };
  double inertia, damping, stiffness;
  double impedancesList[ 3 ] = { 0.0 };
  while( fscanf( samplesFile, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &time, &setpoint, 
                                                                     &(inputsList[ 0 ]), &(inputsList[ 1 ]), &(inputsList[ 2 ]), 
                                                                     &(outputsList[ 0 ]), &inertia, &damping, &stiffness ) >= 9 )
  {
    if( SystemLinearizer_AddSample( lSystem, inputsList, outputsList ) >= LINEARIZATION_MAX_SAMPLES )
      SystemLinearizer_Identify( lSystem, impedancesList );
    printf( "impedance: %f %f %f\n", impedancesList[ 0 ], impedancesList[ 1 ], impedancesList[ 2 ] );
  }
  
  fclose( samplesFile );
  
  return 0;
}
