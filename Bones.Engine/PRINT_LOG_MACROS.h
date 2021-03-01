#pragma once

// PRINT_LOG_MACROS_H pring log macros contains macros that will simply 
// use stdio library to print and log various messages 
// such as error information, general information, various function calls

#ifndef PRINT_LOG_MACROS_H

#define PRINT_LOG_MACROS_H

#include "APP_MACROS.H"

#if DEBUG
#include <stdio.h>
// general logs 
#define LOG_ERROR(FORMAT, ...) fprintf(stderr, "%s() in %s, line %i: " FORMAT "\n", __func__, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FORMAT(FORMAT, ...) fprintf(stdout, "%s() in %s, line %i: " FORMAT "\n", __func__, __FILE__, __LINE__, __VA_ARGS__)
#define LOG(MSG) LOG_FORMAT("%s\n", MSG)

// constructor, destructor, copy calls
#define LOG_CONSTRUCTOR() LOG("Constructor called.\n")
#define LOG_MOVE_OWNERSHIP_CONSTRUCTOR() LOG("Move ownership construtor called.\n");
#define LOG_COPY_CONSTRUCTOR() LOG("Copy constructor called.\n")
#define LOG_COPY_OPERATOR() LOG("Copy operator called.\n")
#define LOG_DESTRUCTOR() LOG("Destructor called.\n")

// interface method calls 
#define LOG_INITIALIZE() LOG("Initialize called.\n")
#define LOG_LOAD() LOG("Initialize called.\n")
#define LOG_DESTROY() LOG("Initialize called.\n")
#else
#define LOG_ERROR(FORMAT, ...) ((void)0)
#define LOG_FORMAT(FORMAT, ...) ((void)0)
#define LOG(MSG) ((void)0)
#define LOG_CONSTRUCTOR() ((void)0)
#define LOG_COPY_CONSTRUCTOR() 
#define LOG_COPY_OPERATOR() 
#define LOG_MOVE_OWNERSHIP_CONSTRUCTOR() 
#define LOG_DESTRUCTOR() ((void)0)
#define LOG_INITIALIZE() 
#define LOG_LOAD() 
#define LOG_DESTROY() 
#endif

// For warnings, this should be always printed out.
#define LOG_WARN_FORMAT(FORMAT, ...) fprintf(stdout, "%s. Warning: " FORMAT "\n", __func__, __VA_ARGS__)
#define LOG_WARN(MSG) LOG_FORMAT("%s\n", MSG)

#endif // !PRINT_LOG_MACROS_H
