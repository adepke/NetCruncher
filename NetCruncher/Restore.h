/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "Packs/IntPack.h"
#include "Packs/FloatPack.h"

#pragma warning(push)
#pragma warning(disable:4244)

template <typename ReturnType, typename InPack>
ReturnType Restore(InPack* Input)
{
	switch (Input->Type)
	{
	case PackType::PT_Int8:
	{
		return RestoreInt(*static_cast<IntPack8*>(Input));
	}
	case PackType::PT_Int16:
	{
		return RestoreInt(*static_cast<IntPack16*>(Input));
	}
	case PackType::PT_Int32:
	{
		return RestoreInt(*static_cast<IntPack32*>(Input));
	}
	case PackType::PT_Int64:
	{
		return RestoreInt(*static_cast<IntPack64*>(Input));
	}
	case PackType::PT_Float8:
	{
		return RestoreFloat(*static_cast<FloatPack8*>(Input));
	}
	case PackType::PT_Float16:
	{
		return RestoreFloat(*static_cast<FloatPack16*>(Input));
	}
	case PackType::PT_Float24:
	{
		return RestoreFloat(*static_cast<FloatPack24*>(Input));
	}
	case PackType::PT_Float32:
	{
		return RestoreFloat(*static_cast<FloatPack32*>(Input));
	}
	case PackType::PT_Float40:
	{
		return RestoreFloat(*static_cast<FloatPack40*>(Input));
	}
	case PackType::PT_Float48:
	{
		return RestoreFloat(*static_cast<FloatPack48*>(Input));
	}
	case PackType::PT_Float56:
	{
		return RestoreFloat(*static_cast<FloatPack56*>(Input));
	}
	case PackType::PT_Float64:
	{
		return RestoreFloat(*static_cast<FloatPack64*>(Input));
	}
	}

	return { 0 };
}

#pragma warning(pop)