/**
 ********************************************************************************
 * @file    DataStore_Configuration.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Configuration for CORALS DataStore Module
 * @version 1.0
 * @date    2024-03-22
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __DATASTORE_CONFIGURATION_HPP__
#define __DATASTORE_CONFIGURATION_HPP__

#include <EEPROM.h>

#define DATASTORE EEPROM

// Memory Map
#define DATASTORE_SIZE 4096
#define DATASTORE_START 0
#define DATASTORE_END DATASTORE_SIZE - 1
#define DATASTORE_SECTION_BUFFER 4

#endif // __DATASTORE_CONFIGURATION_HPP__