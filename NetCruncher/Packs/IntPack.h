/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "../PackBase.h"

#include <climits>

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

Pack Crunch(char Input)
{
	IntPack8 Output;

	memcpy(&Output.Data, &Input, 1);

	return Output;
}

Pack Crunch(unsigned char Input)
{
	IntPack8 Output;

	memcpy(&Output.Data, &Input, 1);

	return Output;
}

Pack Crunch(short Input)
{
	if (Input <= CHAR_MAX && Input >= CHAR_MIN)
	{
		IntPack8 Output;

		memcpy(&Output.Data, &Input, 1);

		return Output;
	}

	else
	{
		IntPack16 Output;

		memcpy(&Output.Data, &Input, 2);

		return Output;
	}
}

Pack Crunch(unsigned short Input)
{
	if (Input <= UCHAR_MAX)
	{
		IntPack8 Output;

		memcpy(&Output.Data, &Input, 1);

		return Output;
	}

	else
	{
		IntPack16 Output;

		memcpy(&Output.Data, &Input, 2);

		return Output;
	}
}

Pack Crunch(int Input)
{
	if (Input <= CHAR_MAX && Input >= CHAR_MIN)
	{
		IntPack8 Output;

		memcpy(&Output.Data, &Input, 1);

		return Output;
	}

	else if (Input <= SHRT_MAX && Input >= SHRT_MIN)
	{
		IntPack16 Output;

		memcpy(&Output.Data, &Input, 2);

		return Output;
	}

	else
	{
		IntPack32 Output;

		memcpy(&Output.Data, &Input, 4);

		return Output;
	}
}

Pack Crunch(unsigned int Input)
{
	if (Input <= UCHAR_MAX)
	{
		IntPack8 Output;

		memcpy(&Output.Data, &Input, 1);

		return Output;
	}

	else if (Input <= USHRT_MAX)
	{
		IntPack16 Output;

		memcpy(&Output.Data, &Input, 2);

		return Output;
	}

	else
	{
		IntPack32 Output;

		memcpy(&Output.Data, &Input, 4);

		return Output;
	}
}

Pack Crunch(long Input)
{
	if (Input <= CHAR_MAX && Input >= CHAR_MIN)
	{
		IntPack8 Output;

		memcpy(&Output.Data, &Input, 1);

		return Output;
	}

	else if (Input <= SHRT_MAX && Input >= SHRT_MIN)
	{
		IntPack16 Output;

		memcpy(&Output.Data, &Input, 2);

		return Output;
	}

	else if (Input <= INT_MAX && Input >= INT_MIN)
	{
		IntPack32 Output;

		memcpy(&Output.Data, &Input, 4);

		return Output;
	}

	else
	{
		IntPack64 Output;

		memcpy(&Output.Data, &Input, 8);

		return Output;
	}
}

Pack Crunch(unsigned long Input)
{
	if (Input <= UCHAR_MAX)
	{
		IntPack8 Output;

		memcpy(&Output.Data, &Input, 1);

		return Output;
	}

	else if (Input <= USHRT_MAX)
	{
		IntPack16 Output;

		memcpy(&Output.Data, &Input, 2);

		return Output;
	}

	else if (Input <= UINT_MAX)
	{
		IntPack32 Output;

		memcpy(&Output.Data, &Input, 4);

		return Output;
	}

	else
	{
		IntPack64 Output;

		memcpy(&Output.Data, &Input, 8);

		return Output;
	}
}