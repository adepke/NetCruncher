/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

struct PackageHeader
{
	unsigned int PackCount : 11;
	unsigned int Flags : 5;
};