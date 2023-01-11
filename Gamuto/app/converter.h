#pragma once

#include "matrixes.hpp"

const int gamutSize = 9;
static const char* gamutKeys[gamutSize]{
   "sRgb",
   "Adobe Rgb",
   "AppleRGB",
   "Best RGB",
   "Beta RGB",
   "ColorMatch RGB",
   "Ekta Space PS5",
   "PAL/SECAM RGB",
   "SMPTE-C RGB"
};

static int gamutKeyIndex = 0;

struct Color {
	int R, G, B;
};

struct XYZColor {
	float X, Y, Z;
};

namespace converter
{
	static Color iColor = { 0, 0, 0 };
	static XYZColor oColor = { .0f, .0f, .0f };
	static float gamutMatrix[9];

	static float OutputColorScheme[3] = { .0f, .0f, .0f };
	
	inline void ComputeEntry()
	{
		OutputColorScheme[0] = static_cast<float>(iColor.R) / 255;
		OutputColorScheme[1] = static_cast<float>(iColor.G) / 255;
		OutputColorScheme[2] = static_cast<float>(iColor.B) / 255;

		if (gamutKeys[gamutKeyIndex] == "sRgb")
			for (auto i = 0; i < 9; ++i)
				gamutMatrix[i] = TrMatrixes::sRgb[i];
		else if(gamutKeys[gamutKeyIndex] == "Adobe Rgb")
			for (auto i = 0; i < 9; ++i)
				gamutMatrix[i] = TrMatrixes::adobeRgb[i];
		else if (gamutKeys[gamutKeyIndex] == "Apple Rgb")
			for (auto i = 0; i < 9; ++i)
				gamutMatrix[i] = TrMatrixes::appleRgb[i];
		else if (gamutKeys[gamutKeyIndex] == "Best Rgb")
			for (auto i = 0; i < 9; ++i)
				gamutMatrix[i] = TrMatrixes::bestRgb[i];
		else if (gamutKeys[gamutKeyIndex] == "Beta Rgb")
			for (auto i = 0; i < 9; ++i)
				gamutMatrix[i] = TrMatrixes::betaRgb[i];
		else if (gamutKeys[gamutKeyIndex] == "ColorMatch RGB")
			for (auto i = 0; i < 9; ++i)
				gamutMatrix[i] = TrMatrixes::colorMatchRgb[i];
		else if (gamutKeys[gamutKeyIndex] == "Ekta Space PS5")
			for (auto i = 0; i < 9; ++i)
				gamutMatrix[i] = TrMatrixes::ektaSpaceRgb[i];
		else if (gamutKeys[gamutKeyIndex] == "PAL/SECAM RGB")
			for (auto i = 0; i < 9; ++i)
				gamutMatrix[i] = TrMatrixes::palSecamRgb[i];
		else if (gamutKeys[gamutKeyIndex] == "SMPTE-C RGB")
			for (auto i = 0; i < 9; ++i)
				gamutMatrix[i] = TrMatrixes::smpte_cRgb[i];
	}

	inline void ComputeOutput()
	{
		oColor.X = (gamutMatrix[0] * static_cast<float>(iColor.R) / 255) +
				   (gamutMatrix[1] * static_cast<float>(iColor.G) / 255) +
				   (gamutMatrix[2] * static_cast<float>(iColor.B) / 255);

		oColor.Y = (gamutMatrix[3] * static_cast<float>(iColor.R) / 255) +
				   (gamutMatrix[4] * static_cast<float>(iColor.G) / 255) +
				   (gamutMatrix[5] * static_cast<float>(iColor.B) / 255);

		oColor.Z = (gamutMatrix[6] * static_cast<float>(iColor.R) / 255) +
				   (gamutMatrix[7] * static_cast<float>(iColor.G) / 255) +
				   (gamutMatrix[8] * static_cast<float>(iColor.B) / 255);
	}
}
