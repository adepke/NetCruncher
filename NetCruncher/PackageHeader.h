/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

struct PackageHeader
{
	unsigned int PackCount : 11;
	unsigned int Flags : 5;
};

unsigned short PackageHeaderToBytes(PackageHeader Input)
{
	unsigned short Output = Input.PackCount;
	Output <<= 5;
	Output |= Input.Flags;

	return Output;
}

PackageHeader BytesToPackageHeader(unsigned short Input)
{
	PackageHeader Output;

	static const unsigned int PackCountMask = 0xFFE0;
	static const unsigned int FlagsMask = 0x001F;

	unsigned int PackCountInt = (Input & PackCountMask) >> 5;
	unsigned int FlagsInt = Input & FlagsMask;

	Output.PackCount = PackCountInt;
	Output.Flags = FlagsInt;

	return Output;
}