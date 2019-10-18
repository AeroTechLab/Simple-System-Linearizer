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
