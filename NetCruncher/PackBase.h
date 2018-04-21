/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "PackTypes.h"

// Package Base Type
class Pack
{
public:
	PackType Type;

	Pack(PackType InType) : Type(InType) {}
	virtual ~Pack() {}
};