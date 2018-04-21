/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "PackageHeader.h"
#include "PackBase.h"
#include <vector>

class Package
{
	PackageHeader Header;

	std::vector<Pack> Packs;

public:
	Package() {}
	~Package() {}
};