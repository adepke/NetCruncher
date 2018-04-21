/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "../PackBase.h"

#include <climits>

class IntPack8 : public Pack
{
public:
	static const size_t Size = 1;
	typedef char UnderlyingType;

	IntPack8() : Pack(PackType::PT_Int8) {}
	virtual ~IntPack8() {}

	unsigned char Data[1];
};

class IntPack16 : public Pack
{
public:
	static const size_t Size = 2;
	typedef short UnderlyingType;

	IntPack16() : Pack(PackType::PT_Int16) {}
	virtual ~IntPack16() {}

	unsigned char Data[2];
};

class IntPack32 : public Pack
{
public:
	static const size_t Size = 4;
	typedef int UnderlyingType;

	IntPack32() : Pack(PackType::PT_Int32) {}
	virtual ~IntPack32() {}

	unsigned char Data[4];
};

class IntPack64 : public Pack
{
public:
	static const size_t Size = 8;
	typedef long UnderlyingType;

	IntPack64() : Pack(PackType::PT_Int64) {}
	virtual ~IntPack64() {}

	unsigned char Data[8];
};

Pack* Crunch(char Input)
{
	auto* Output = new IntPack8;

	memcpy(Output->Data, &Input, IntPack8::Size);

	return Output;
}

Pack* Crunch(short Input)
{
	if (Input <= CHAR_MAX && Input >= CHAR_MIN)
	{
		auto* Output = new IntPack8;

		memcpy(Output->Data, &Input, IntPack8::Size);

		return Output;
	}

	else
	{
		auto* Output = new IntPack16;

		memcpy(Output->Data, &Input, IntPack16::Size);

		return Output;
	}
}

Pack* Crunch(int Input)
{
	if (Input <= CHAR_MAX && Input >= CHAR_MIN)
	{
		auto* Output = new IntPack8;

		memcpy(Output->Data, &Input, IntPack8::Size);

		return Output;
	}

	else if (Input <= SHRT_MAX && Input >= SHRT_MIN)
	{
		auto* Output = new IntPack16;

		memcpy(Output->Data, &Input, IntPack16::Size);

		return Output;
	}

	else
	{
		auto* Output = new IntPack32;

		memcpy(Output->Data, &Input, IntPack32::Size);

		return Output;
	}
}


Pack* Crunch(long Input)
{
	if (Input <= CHAR_MAX && Input >= CHAR_MIN)
	{
		auto* Output = new IntPack8;

		memcpy(Output->Data, &Input, IntPack8::Size);

		return Output;
	}

	else if (Input <= SHRT_MAX && Input >= SHRT_MIN)
	{
		auto* Output = new IntPack16;

		memcpy(Output->Data, &Input, IntPack16::Size);

		return Output;
	}

	else if (Input <= INT_MAX && Input >= INT_MIN)
	{
		auto* Output = new IntPack32;

		memcpy(Output->Data, &Input, IntPack32::Size);

		return Output;
	}

	else
	{
		auto* Output = new IntPack64;

		memcpy(Output->Data, &Input, IntPack64::Size);

		return Output;
	}
}

template <typename IntPackType>
typename IntPackType::UnderlyingType Restore(const IntPackType& Input)
{
	typename IntPackType::UnderlyingType Output;

	memcpy(&Output, &Input.Data, IntPackType::Size);

	return Output;
}