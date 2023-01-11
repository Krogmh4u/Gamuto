#include "gui.h"

#include <thread>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow
)
{
	W_SPACE space; 
	strcpy(space.Name, "SMPTE-C RGB");
	strcpy(space.RefWhite, "D65");
	for (auto i = 0; i < 9; ++i)
		space.RGB2XYZ_Matrix[i] = TrMatrixes::smpte_cRgb[i];
	space.Gamma = 2.2f;
	space.LabGamutEfficiency = 31.9f;
	space.CodingEfficiency = 100.0f;
	space.Illuminant[0] = 0.95047f;
	space.Illuminant[1] = 1.00000f;
	space.Illuminant[2] = 1.08883f;

	std::fstream fout("smtpec.ws", std::ios::out | std::ios::binary);

	if (fout.is_open())
	{
		fout.seekg(fout._Seekbeg);
		fout.write((char*)&space, sizeof(W_SPACE));

		fout.close();
	}

	gui::CreateHWindow("GAMUTO", "GAMUTOCLASS");
	gui::CreateDevice();
	gui::CreateImGui();

	converter::Init();

	while (gui::exit)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}