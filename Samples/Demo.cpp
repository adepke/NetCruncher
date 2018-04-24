#include "../NetCruncher/NetCruncher.h"

#include <iostream>
#include <string>

int main()
{
	// -- Example Data. --

	int Integer1 = 422455;
	int Integer2 = 24;
	int Integer3 = 43209525;

	long long Long1 = 309245034324;
	long long Long2 = 4;

	float Float1 = 0.002415f;
	float Float2 = 424.533023f;
	
	double Double1 = 0.00000452;
	double Double2 = 304932.3905823;

	// -- Pack Them Up. --

	auto* Integer1Pack = CrunchInt(Integer1);
	auto* Integer2Pack = CrunchInt(Integer2);
	auto* Integer3Pack = CrunchInt(Integer3);

	auto* Long1Pack = CrunchInt(Long1);
	auto* Long2Pack = CrunchInt(Long2);

	// Compression Level Determines How Compressed the Pack Should Be. Only Available on Float Packs Currently.
	auto* Float1Pack = CrunchFloat(Float1, FloatCompressionLevel::CL_1);  // 25% Compression.
	auto* Float2Pack = CrunchFloat(Float2, FloatCompressionLevel::CL_2);  // 50% Compression.

	auto* Double1Pack = CrunchFloat(Double1, FloatCompressionLevel::CL_3);  // 38% Compression.
	auto* Double2Pack = CrunchFloat(Double2, FloatCompressionLevel::CL_5);  // 63% Compression.

	// -- Build a Stream to Send Over the Network. --

	Package* StartingPackage = new Package();
	StartingPackage->Packs.push_back(Integer1Pack);
	StartingPackage->Packs.push_back(Integer2Pack);
	StartingPackage->Packs.push_back(Integer3Pack);
	StartingPackage->Packs.push_back(Long1Pack);
	StartingPackage->Packs.push_back(Long2Pack);
	StartingPackage->Packs.push_back(Float1Pack);
	StartingPackage->Packs.push_back(Float2Pack);
	StartingPackage->Packs.push_back(Double1Pack);
	StartingPackage->Packs.push_back(Double2Pack);

	StartingPackage->AddFlag(0);  // Add Any User-Defined Flags.

	// Construct the Byte Stream. (Network Byte Order).
	auto* Stream = PackageToStream(*StartingPackage);

	// -- Pass The Stream Over a Wire --

	// --

	// -- Reconstruct The Package From The Stream on a Remote Machine. --

	Package* EndingPackage = StreamToPackage(Stream);

	// -- Decompress The Packs. --

	int Integer1Final = Restore<int>(EndingPackage->Packs[0]);
	int Integer2Final = Restore<int>(EndingPackage->Packs[1]);
	int Integer3Final = Restore<int>(EndingPackage->Packs[2]);

	int Long1Final = Restore<long>(EndingPackage->Packs[3]);
	int Long2Final = Restore<long>(EndingPackage->Packs[4]);

	float Float1Final = Restore<float>(EndingPackage->Packs[5]);
	float Float2Final = Restore<float>(EndingPackage->Packs[6]);

	double Double1Final = Restore<double>(EndingPackage->Packs[7]);
	double Double2Final = Restore<double>(EndingPackage->Packs[8]);

	// -- Compare The Results. --

	std::cout << "Integer1 Start: " << std::to_string(Integer1) << "\n";
	std::cout << "Integer1 End:   " << std::to_string(Integer1Final) << "\n\n";
	std::cout << "Integer2 Start: " << std::to_string(Integer2) << "\n";
	std::cout << "Integer2 End:   " << std::to_string(Integer2Final) << "\n\n";
	std::cout << "Integer3 Start: " << std::to_string(Integer3) << "\n";
	std::cout << "Integer3 End:   " << std::to_string(Integer3Final) << "\n\n\n";

	std::cout << "Long1 Start:    " << std::to_string(Long1) << "\n";
	std::cout << "Long1 End:      " << std::to_string(Long1Final) << "\n\n";
	std::cout << "Long2 Start:    " << std::to_string(Long2) << "\n";
	std::cout << "Long2 End:      " << std::to_string(Long2Final) << "\n\n\n";

	std::cout << "Float1 Start:   " << std::to_string(Float1) << "\n";
	std::cout << "Float1 End:     " << std::to_string(Float1Final) << "\n\n";
	std::cout << "Float2 Start:   " << std::to_string(Float2) << "\n";
	std::cout << "Float2 End:     " << std::to_string(Float2Final) << "\n\n\n";

	std::cout << "Double1 Start:   " << std::to_string(Double1) << "\n";
	std::cout << "Double1 End:     " << std::to_string(Double1Final) << "\n\n";
	std::cout << "Double2 Start:   " << std::to_string(Double2) << "\n";
	std::cout << "Double2 End:     " << std::to_string(Double2Final) << "\n\n\n";

	// -- Cleanup. --

	delete StartingPackage;
	delete EndingPackage;

	system("pause");

	return 0;
}