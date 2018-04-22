/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "../PackBase.h"

class FloatPack8 : public Pack
{
public:
	enum { Size = 1 };
	typedef float UnderlyingType;

	FloatPack8() : Pack(PackType::PT_Float8) {}
	virtual ~FloatPack8() {}

	unsigned char Data[Size];
};

class FloatPack16 : public Pack
{
public:
	enum { Size = 2 };
	typedef float UnderlyingType;

	FloatPack16() : Pack(PackType::PT_Float16) {}
	virtual ~FloatPack16() {}

	unsigned char Data[Size];
};

class FloatPack24 : public Pack
{
public:
	enum { Size = 3 };
	typedef float UnderlyingType;

	FloatPack24() : Pack(PackType::PT_Float24) {}
	virtual ~FloatPack24() {}

	unsigned char Data[Size];
};

class FloatPack32 : public Pack
{
public:
	enum { Size = 4 };
	typedef float UnderlyingType;

	FloatPack32() : Pack(PackType::PT_Float32) {}
	virtual ~FloatPack32() {}

	unsigned char Data[Size];
};

class FloatPack40 : public Pack
{
public:
	enum { Size = 5 };
	typedef double UnderlyingType;

	FloatPack40() : Pack(PackType::PT_Float40) {}
	virtual ~FloatPack40() {}

	unsigned char Data[Size];
};

class FloatPack48 : public Pack
{
public:
	enum { Size = 6 };
	typedef double UnderlyingType;

	FloatPack48() : Pack(PackType::PT_Float48) {}
	virtual ~FloatPack48() {}

	unsigned char Data[Size];
};

class FloatPack56 : public Pack
{
public:
	enum { Size = 7 };
	typedef double UnderlyingType;

	FloatPack56() : Pack(PackType::PT_Float56) {}
	virtual ~FloatPack56() {}

	unsigned char Data[Size];
};

class FloatPack64 : public Pack
{
public:
	enum { Size = 8 };
	typedef double UnderlyingType;

	FloatPack64() : Pack(PackType::PT_Float64) {}
	virtual ~FloatPack64() {}

	unsigned char Data[Size];
};

enum class FloatCompressionLevel
{
	CL_0,  // No Compression
	CL_1,  // Drop 1 Byte of Precision (Float/Double)
	CL_2,  // Drop 2 Bytes of Precision (Float/Double)
	CL_3,  // Drop 3 Bytes of Precision (Float/Double)
	CL_4,  // Drop 4 Bytes of Precision (Double)
	CL_5,  // Drop 5 Bytes of Precision (Double)
	CL_6,  // Drop 6 Bytes of Precision (Double)
};

Pack* CrunchFloat(float Input, FloatCompressionLevel CompressionLevel)
{
	auto* InputIter = (char*)&Input;

	switch (CompressionLevel)
	{
	case FloatCompressionLevel::CL_0:
	{
		auto* Output = new FloatPack32;

		memcpy(Output->Data, &Input, FloatPack32::Size);

		return Output;
	}
	case FloatCompressionLevel::CL_1:
	{
		auto* Output = new FloatPack24;

		Output->Data[0] = InputIter[3];
		Output->Data[1] = InputIter[2];
		Output->Data[2] = InputIter[1];

		return Output;
	}
	case FloatCompressionLevel::CL_2:
	{
		auto* Output = new FloatPack16;

		Output->Data[0] = InputIter[3];
		Output->Data[1] = InputIter[2];

		return Output;
	}
	case FloatCompressionLevel::CL_3:
	{
		auto* Output = new FloatPack8;

		Output->Data[0] = InputIter[3];

		return Output;
	}
	}

	return nullptr;
}

Pack* CrunchFloat(double Input, FloatCompressionLevel CompressionLevel)
{
	// Double has a Different Exponent Length, So Compress After Conversion to 32 Bit Float.
	if (CompressionLevel >= FloatCompressionLevel::CL_4)
	{
		return CrunchFloat(static_cast<float>(Input), static_cast<FloatCompressionLevel>((int)CompressionLevel - 4));
	}

	auto* InputIter = (char*)&Input;

	switch (CompressionLevel)
	{
	case FloatCompressionLevel::CL_0:
	{
		auto* Output = new FloatPack64;

		memcpy(Output->Data, &Input, FloatPack64::Size);

		return Output;
	}
	case FloatCompressionLevel::CL_1:
	{
		auto* Output = new FloatPack56;

		Output->Data[0] = InputIter[7];
		Output->Data[1] = InputIter[6];
		Output->Data[2] = InputIter[5];
		Output->Data[3] = InputIter[4];
		Output->Data[4] = InputIter[3];
		Output->Data[5] = InputIter[2];
		Output->Data[6] = InputIter[1];

		return Output;
	}
	case FloatCompressionLevel::CL_2:
	{
		auto* Output = new FloatPack48;

		Output->Data[0] = InputIter[7];
		Output->Data[1] = InputIter[6];
		Output->Data[2] = InputIter[5];
		Output->Data[3] = InputIter[4];
		Output->Data[4] = InputIter[3];
		Output->Data[5] = InputIter[2];

		return Output;
	}
	case FloatCompressionLevel::CL_3:
	{
		auto* Output = new FloatPack40;

		Output->Data[0] = InputIter[7];
		Output->Data[1] = InputIter[6];
		Output->Data[2] = InputIter[5];
		Output->Data[3] = InputIter[4];
		Output->Data[4] = InputIter[3];

		return Output;
	}
	}

	return nullptr;
}

template <typename FloatPackType>
typename FloatPackType::UnderlyingType RestoreFloat(const FloatPackType& Input)
{
	typename FloatPackType::UnderlyingType Output;
	const size_t UnderlyingTypeSize = sizeof(Output);
	auto* OutputIter = (char*)&Output;

	memset(&Output, 0, sizeof(Output));

	if (FloatPackType::Size == UnderlyingTypeSize)
	{
		memcpy(&Output, &Input.Data, FloatPackType::Size);
	}

	else
	{
		for (size_t Iter = 0; Iter < FloatPackType::Size; ++Iter)
		{
			OutputIter[UnderlyingTypeSize - Iter - 1] = Input.Data[Iter];
		}
	}

	return Output;
}