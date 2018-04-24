/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#if defined(__BIG_ENDIAN__) || defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
#define NC_BIG_ENDIAN
#else
#define NC_LITTLE_ENDIAN
#endif

#pragma warning(push)
#pragma warning(disable:4244)

inline unsigned char SwapOrder(unsigned char Input)
{
#ifdef NC_LITTLE_ENDIAN
	return ((Input * 0x0202020202ULL & 0x010884422010ULL) % 1023);
#else
	return Input;
#endif
}

#pragma warning(pop)