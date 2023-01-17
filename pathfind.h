#pragma once
//#include "filestuff.h"
#include "enemy.h"

//straight line find
void* stupidFind(int argn, ...);
//spin around target and gradually get closer
void* spinFind(int argn, ...);
//do sine wave and follow target
void* sinewaveFind(int argn, ...);
//follow target and home in like revenant missile in doom 2
//follow target and change angle if target moves(within angle threshhold)
void* seeksightFind(int argn, ...);
//like sinewaveFind but this follows the target instead
void* sinewaveFollow(int argn, ...);
// Pathfind in gridmap
// 
// 
//pathfind in planet map
void* daijkstraFind(int argn, ...);


//split into smaller cases, divide and conquer
void* treeFind(int argn, ...);


void* hnorthwestFind(int argn, ...);

void* hnortheastFind(int argn, ...);

void* hsouthwestFind(int argn, ...);

void* hsoutheastFind(int argn, ...);



void* vnorthwestFind(int argn, ...);

void* vnortheastFind(int argn, ...);

void* vsouthwestFind(int argn, ...);

void* vsoutheastFind(int argn, ...);

void* greedyFind(int argn, ...);









