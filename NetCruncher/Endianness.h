/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#if defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
#define NC_BIG_ENDIAN
#else
#define NC_LITTLE_ENDIAN
#endif