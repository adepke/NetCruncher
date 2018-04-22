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