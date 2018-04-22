/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "PackageHeader.h"
#include "PackBase.h"
#include "Endianness.h"
#include <vector>

// Packs
#include "Packs/IntPack.h"
#include "Packs/FloatPack.h"

class Package
{
protected:
	PackageHeader Header;

public:
	Package() {}
	~Package()
	{
		for (size_t Iter = 0; Iter < Packs.size(); ++Iter)
		{
			if (Packs[Iter])
			{
				delete Packs[Iter];
			}
		}
	}

	PackageHeader GetHeaderCopy()
	{
		Header.PackCount = Packs.size();

		return Header;
	}

	void AddFlag(unsigned char Flag)
	{
		Header.Flags |= Flag;
	}

	void SetFlags(unsigned char Flags)
	{
		Header.Flags = Flags;
	}

	std::vector<Pack*> Packs;

	friend Package StreamToPackage(std::vector<unsigned char>* Input);
};

// Byte Stream is Big Endian
std::vector<unsigned char>* PackageToStream(Package& Input)
{
	unsigned short RawHeader = PackageHeaderToBytes(Input.GetHeaderCopy());
	auto* RawHeaderIter = (char*)&RawHeader;

	auto* Stream = new std::vector<unsigned char>();

	// Store the Header Length and Flags.
	Stream->push_back(RawHeaderIter[0]);
	Stream->push_back(RawHeaderIter[1]);

	// Store the Header Pack Types.
	for (auto _Pack : Input.Packs)
	{
		Stream->push_back(static_cast<unsigned char>(_Pack->Type));
	}

	// Store the Data Payloads.
	for (auto _Pack : Input.Packs)
	{
		int Size = 0;
		unsigned char* Data = nullptr;

		switch (_Pack->Type)
		{
		case PackType::PT_Int8:
		{
			auto* const SpecificPack = static_cast<IntPack8*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Int16:
		{
			auto* const SpecificPack = static_cast<IntPack16*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Int32:
		{
			auto* const SpecificPack = static_cast<IntPack32*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Int64:
		{
			auto* const SpecificPack = static_cast<IntPack64*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Float8:
		{
			auto* const SpecificPack = static_cast<FloatPack8*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Float16:
		{
			auto* const SpecificPack = static_cast<FloatPack16*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Float24:
		{
			auto* const SpecificPack = static_cast<FloatPack24*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Float32:
		{
			auto* const SpecificPack = static_cast<FloatPack32*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Float40:
		{
			auto* const SpecificPack = static_cast<FloatPack40*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Float48:
		{
			auto* const SpecificPack = static_cast<FloatPack48*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Float56:
		{
			auto* const SpecificPack = static_cast<FloatPack56*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		case PackType::PT_Float64:
		{
			auto* const SpecificPack = static_cast<FloatPack64*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;

			break;
		}
		}

		for (int ByteIter = 0; ByteIter < Size; ++ByteIter)
		{
			Stream->push_back(Data[ByteIter]);
		}
	}

	return Stream;
}

Package StreamToPackage(std::vector<unsigned char>* Input)
{
	Package Output;

	unsigned char RawHeaderA = Input->at(0);
	unsigned char RawHeaderB = Input->at(1);

	unsigned short RawHeader = RawHeaderB;
	RawHeader <<= 8;
	RawHeader |= RawHeaderA;

	Output.Header = BytesToPackageHeader(RawHeader);

	int PackOffset = 2 + Output.Header.PackCount;

	// Read the Packs.
	for (unsigned int Iter = 0; Iter < Output.Header.PackCount; ++Iter)
	{
		// Get the Type.
		const PackType Type = static_cast<PackType>(Input->at(Iter + 2));

		switch (Type)
		{
		case PackType::PT_Int8:
		{
			auto* _Pack = new IntPack8();

			_Pack->Data[0] = Input->at(0 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Int16:
		{
			auto* _Pack = new IntPack16();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Int32:
		{
			auto* _Pack = new IntPack32();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);
			_Pack->Data[2] = Input->at(2 + PackOffset);
			_Pack->Data[3] = Input->at(3 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Int64:
		{
			auto* _Pack = new IntPack64();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);
			_Pack->Data[2] = Input->at(2 + PackOffset);
			_Pack->Data[3] = Input->at(3 + PackOffset);
			_Pack->Data[4] = Input->at(4 + PackOffset);
			_Pack->Data[5] = Input->at(5 + PackOffset);
			_Pack->Data[6] = Input->at(6 + PackOffset);
			_Pack->Data[7] = Input->at(7 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Float8:
		{
			auto* _Pack = new FloatPack8();

			_Pack->Data[0] = Input->at(0 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Float16:
		{
			auto* _Pack = new FloatPack16();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Float24:
		{
			auto* _Pack = new FloatPack24();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);
			_Pack->Data[2] = Input->at(2 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Float32:
		{
			auto* _Pack = new FloatPack32();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);
			_Pack->Data[2] = Input->at(2 + PackOffset);
			_Pack->Data[3] = Input->at(3 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Float40:
		{
			auto* _Pack = new FloatPack40();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);
			_Pack->Data[2] = Input->at(2 + PackOffset);
			_Pack->Data[3] = Input->at(3 + PackOffset);
			_Pack->Data[4] = Input->at(4 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Float48:
		{
			auto* _Pack = new FloatPack48();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);
			_Pack->Data[2] = Input->at(2 + PackOffset);
			_Pack->Data[3] = Input->at(3 + PackOffset);
			_Pack->Data[4] = Input->at(4 + PackOffset);
			_Pack->Data[5] = Input->at(5 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Float56:
		{
			auto* _Pack = new FloatPack56();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);
			_Pack->Data[2] = Input->at(2 + PackOffset);
			_Pack->Data[3] = Input->at(3 + PackOffset);
			_Pack->Data[4] = Input->at(4 + PackOffset);
			_Pack->Data[5] = Input->at(5 + PackOffset);
			_Pack->Data[6] = Input->at(6 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		case PackType::PT_Float64:
		{
			auto* _Pack = new FloatPack64();

			_Pack->Data[0] = Input->at(0 + PackOffset);
			_Pack->Data[1] = Input->at(1 + PackOffset);
			_Pack->Data[2] = Input->at(2 + PackOffset);
			_Pack->Data[3] = Input->at(3 + PackOffset);
			_Pack->Data[4] = Input->at(4 + PackOffset);
			_Pack->Data[5] = Input->at(5 + PackOffset);
			_Pack->Data[6] = Input->at(6 + PackOffset);
			_Pack->Data[7] = Input->at(7 + PackOffset);

			Output.Packs.push_back(_Pack);

			PackOffset += _Pack->Size;

			break;
		}
		}
	}

	return Output;
}