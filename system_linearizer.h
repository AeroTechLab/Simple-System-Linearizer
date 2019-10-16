#ifndef SYSTEM_LINEARIZER_H
#define SYSTEM_LINEARIZER_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _LinearSystemData LinearSystemData;
typedef LinearSystemData* LinearSystem;

LinearSystem SystemLinearizer_CreateSystem( size_t inputsNumber, size_t outputsNumber, size_t samplesNumber );
size_t SystemLinearizer_AddSample( LinearSystem lSystem, double* inputsList, double* outputsList );
bool SystemLinearizer_Identify( LinearSystem lSystem, double* parametersList );
void SystemLinearizer_DeleteSystem( LinearSystem lSystem );


#endif // SYSTEM_LINEARIZER_H
