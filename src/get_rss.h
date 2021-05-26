//
// Created by Paul Ross on 26/05/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_GET_RSS_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_GET_RSS_H

#include <stdlib.h>

size_t getPeakRSS(void);
size_t getCurrentRSS(void);
size_t getCurrentRSS_alternate(void);

extern const double MEGABYTES;

double getPeakRSSMb();
double getCurrentRSSMb();
double getCurrentRSS_alternateMb();

#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_GET_RSS_H
