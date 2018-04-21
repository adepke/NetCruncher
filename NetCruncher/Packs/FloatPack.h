/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "../PackBase.h"

class FloatPack8 : public Pack
{
public:
	static const size_t Size = 1;
	typedef float UnderlyingType;

	FloatPack8() : Pack(PackType::PT_Float8) {}
	virtual ~FloatPack8() {}

	unsigned char Data[Size];
};

class FloatPack16 : public Pack
{
public:
	static const size_t Size = 2;
	typedef float UnderlyingType;

	FloatPack16() : Pack(PackType::PT_Float16) {}
	virtual ~FloatPack16() {}

	unsigned char Data[Size];
};

class FloatPack32 : public Pack
{
public:
	static const size_t Size = 4;
	typedef float UnderlyingType;

	FloatPack32() : Pack(PackType::PT_Float32) {}
	virtual ~FloatPack32() {}

	unsigned char Data[Size];
};

class FloatPack64 : public Pack
{
public:
	static const size_t Size = 8;
	typedef float UnderlyingType;

	FloatPack64() : Pack(PackType::PT_Float64) {}
	virtual ~FloatPack64() {}

	unsigned char Data[Size];
};