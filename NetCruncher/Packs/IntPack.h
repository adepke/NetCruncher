/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "../PackBase.h"

class IntPack8 : public Pack
{
public:
	IntPack8() : Pack(PackType::PT_Int8) {}
	virtual ~IntPack8() {}

	unsigned char Data[1];
};

class IntPack16 : public Pack
{
public:
	IntPack16() : Pack(PackType::PT_Int16) {}
	virtual ~IntPack16() {}

	unsigned char Data[2];
};

class IntPack32 : public Pack
{
public:
	IntPack32() : Pack(PackType::PT_Int32) {}
	virtual ~IntPack32() {}

	unsigned char Data[4];
};

class IntPack64 : public Pack
{
public:
	IntPack64() : Pack(PackType::PT_Int64) {}
	virtual ~IntPack64() {}

	unsigned char Data[8];
};