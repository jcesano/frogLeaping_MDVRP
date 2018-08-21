#include "stdafx.h"
#include "FrogLeapController.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include <iostream>
#include <time.h>


FrogLeapController::FrogLeapController()
{
	this->failAttempts = 0;

	this->successAttempts = 0;

	this->timeSeedUsed = (unsigned)time(NULL);
}

FrogLeapController::~FrogLeapController()
{
}

int FrogLeapController::getFailAttempts()
{
	return this->failAttempts;
}

void FrogLeapController::incFailAttempts()
{
	this->failAttempts++;
}

void FrogLeapController::setRandomSeed()
{
	srand(this->timeSeedUsed);
}

void FrogLeapController::printCtrl()
{
	printf("Showing data of controller \n");
	printf("	Number of success attempts: %d", this->successAttempts);
	printf("	Number of fail attempts: %d", this->failAttempts);
}

void FrogLeapController::setFailAttempts(int vfailAttempts)
{
	this->failAttempts = vfailAttempts;
}

int FrogLeapController::getSuccessAttempts()
{
	return this->successAttempts;
}

void FrogLeapController::incSuccessAttempts()
{
	this->successAttempts++;
}

void FrogLeapController::setSuccessAttempts(int vsucessAttempts)
{
	this->successAttempts = vsucessAttempts;
}