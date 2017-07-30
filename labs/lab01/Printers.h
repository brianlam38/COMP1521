// Interface to ADT for a pool of printers
// COMP1521 17s2 Week01 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#ifndef PRINTERS_H
#define PRINTERS_H

typedef struct PrintersRep *Printers;

// create a pool containing N printers
Printers makePrinters(int);

// release memory allocated to Printers
void freePrinters(Printers);

// remove all completed jobs from pool
void clearPrinterJobs(Printers, int);

// add a new job to the Printer pool
void addPrintersJob(Printers, int, int);

// display printer pool queues
void showPrinters(Printers);

#endif
