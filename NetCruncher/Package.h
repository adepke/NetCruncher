/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "PackageHeader.h"
#include "PackBase.h"
#include <vector>

// Packs
#include "Packs/IntPack.h"
#include "Packs/FloatPack.h"

class Package
{
public:
	Package() {}
	~Package()
	{
		for (int Iter = 0; Iter < Packs.size(); ++Iter)
		{
			delete Packs[Iter];
		}
	}

	PackageHeader Header;

	std::vector<Pack*> Packs;
};

std::vector<unsigned char>* PackageToStream(const Package& Input)
{
	unsigned short RawHeader = PackageHeaderToBytes(Input.Header);
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
		}
		case PackType::PT_Int16:
		{
			auto* const SpecificPack = static_cast<IntPack16*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Int32:
		{
			auto* const SpecificPack = static_cast<IntPack32*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Int64:
		{
			auto* const SpecificPack = static_cast<IntPack64*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Float8:
		{
			auto* const SpecificPack = static_cast<FloatPack8*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Float16:
		{
			auto* const SpecificPack = static_cast<FloatPack16*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Float24:
		{
			auto* const SpecificPack = static_cast<FloatPack24*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Float32:
		{
			auto* const SpecificPack = static_cast<FloatPack32*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Float40:
		{
			auto* const SpecificPack = static_cast<FloatPack40*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Float48:
		{
			auto* const SpecificPack = static_cast<FloatPack48*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Float56:
		{
			auto* const SpecificPack = static_cast<FloatPack56*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
		}
		case PackType::PT_Float64:
		{
			auto* const SpecificPack = static_cast<FloatPack64*>(_Pack);
			Size = SpecificPack->Size;
			Data = SpecificPack->Data;
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

	unsigned short RawHeader = RawHeaderA;
	RawHeader <<= 8;
	RawHeader |= RawHeaderB;

	Output.Header = BytesToPackageHeader(RawHeader);



	return Output;
}