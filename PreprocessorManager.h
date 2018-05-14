#pragma once
#include <iostream>
#include <memory>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <Windows.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <typeinfo>
#include <exception>
#define PAUSE system("pause")
#define RAND(min, max) ((rand()%(int)(((max) + 1)-(min)))+ (min) //Generate a random nember between the min/max parameters 
using namespace std;