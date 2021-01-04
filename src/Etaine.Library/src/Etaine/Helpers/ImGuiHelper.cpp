#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include <Etaine/Helpers/ImGuiHelper.h>
#include <Etaine/Analyzer.h>
#include <Etaine/Faker.h>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

#define WINDOW_NAME "Dear ImGui DirectX9 Example"

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

const char* windowName = "Shaiya";
EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}

const char* string_to_hex(const char* str, char* hex, size_t maxlen)
{
	static const char* const lut = "0123456789ABCDEF";

	if (str == NULL) return NULL;
	if (hex == NULL) return NULL;
	if (maxlen == 0) return NULL;

	size_t len = strlen(str);

	char* p = hex;

	for (size_t i = 0; (i < len) && (i < (maxlen - 1)); ++i)
	{
		const unsigned char c = str[i];
		*p++ = lut[c >> 4];
		*p++ = lut[c & 15];
	}

	*p++ = 0;

	return hex;
}

bool init = false;
bool show = false;
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		InitImGui(pDevice);
		init = true;
	}


	if (GetAsyncKeyState(VK_F5) & 1) {
		show = !show;
	}

	//if (GetAsyncKeyState(VK_END)) {
	//	kiero::shutdown();
	//	return 0;
	//}

	if (show) {


		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Etaine Packet Sniffer");

		ImGui::BeginChild("Scrolling");


		//static vector<bool> t = vector<bool>();

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
		ImGui::BeginChild("Packets", ImVec2(ImGui::GetWindowContentRegionWidth(), 260), false, window_flags);

		for (int i = 0; i < Analyzer::InOutPackets.size(); i++) {
			stringstream sStream;

			sStream << Analyzer::InOutPackets[i]->Type << ">> 0x" << hex << setw(4) << setfill('0') << uppercase << Analyzer::InOutPackets[i]->Opcode << " ";

			if (Analyzer::DisplayType == 0) // HEX
			{
				for (size_t j = 0; j < Analyzer::InOutPackets[i]->Length - 2; j++)
				{
					sStream << hex << setw(2) << setfill('0') << uppercase << (int)Analyzer::InOutPackets[i]->Data[j] << " ";
				}

			}
			else if (Analyzer::DisplayType == 1)  // Decimal
			{
				for (size_t j = 0; j < Analyzer::InOutPackets[i]->Length - 2; j++)
				{
					sStream << dec << setw(3) << setfill('0') << (int)Analyzer::InOutPackets[i]->Data[j] << " ";
				}
			}
			else  // ASCII
			{
				for (size_t j = 0; j < Analyzer::InOutPackets[i]->Length - 2; j++)
				{
					if ((int)Analyzer::InOutPackets[i]->Data[j] != 0) {
						sStream << Analyzer::InOutPackets[i]->Data[j] << " ";
					}
					else {
						sStream << "|| ";
					}
				}
			}

			sStream << endl;

			string parsedPacket = sStream.str();

			//ImGui::Text(s.c_str());

			if (ImGui::Selectable(parsedPacket.c_str(), Analyzer::PacketSelection[i]))
			{
				if (!ImGui::GetIO().KeyCtrl)    // Clear selection when CTRL is not held
				{
					bool temp = (bool)Analyzer::PacketSelection[i];

					Analyzer::PacketSelection = vector<bool>(Analyzer::PacketSelection.size(), false);

					Analyzer::PacketSelection[i] = !(bool)temp;

					cout << "cleared selected packets" << endl;
				}
				else {
					Analyzer::PacketSelection[i] = !((bool)Analyzer::PacketSelection[i]);
				}
			}
		}

		ImGui::EndChild();


		if (ImGui::Button("Copy All"))
		{
			ImGui::LogToClipboard();

			for (size_t i = 0; i < Analyzer::Packets.size(); i++)
			{
				ImGui::LogText(Analyzer::Packets[i].c_str());
			}

			ImGui::LogFinish();
		}

		ImGui::SameLine();

		if (ImGui::Button("Copy Selection"))
		{
			ImGui::LogToClipboard();

			for (size_t i = 0; i < Analyzer::Packets.size(); i++)
			{
				if (Analyzer::PacketSelection[i])
					ImGui::LogText(Analyzer::Packets[i].c_str());
			}

			ImGui::LogFinish();
		}

		ImGui::SameLine();

		ImGui::RadioButton("Hex", &Analyzer::DisplayType, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Decimal", &Analyzer::DisplayType, 1);
		ImGui::SameLine();
		ImGui::RadioButton("ASCII", &Analyzer::DisplayType, 2);

		static char fakePacketBuffer[2048] = "";
		static char parsedFakePacketBuffer[2048] = "";
		ImGui::InputText("", fakePacketBuffer, IM_ARRAYSIZE(fakePacketBuffer));
		ImGui::SameLine();

		if (ImGui::Button("Fake Send (pending)")) {
			stringstream ss;
			ss << fakePacketBuffer;

			string temp = ss.str();
			unsigned char* val = new unsigned char[temp.length() + 1];
			strcpy((char*)val, temp.c_str());

			for (size_t i = 0; i < temp.length(); i++)
			{
				cout << val[i];
			}

			cout << endl;

			Faker::fakeSendPacket(Analyzer::InOutPackets[0]->Buffer, Analyzer::InOutPackets[0]->Length);
		}

		ImGui::SameLine();
		ImGui::Button("Fake Receive (pending)");
		//ImGui::InputText("", parsedFakePacketBuffer, IM_ARRAYSIZE(parsedFakePacketBuffer));


		//// START: String version

		//auto size = Analyzer::Packets.size();

		//for (int i = 0; i < size; i++) {
		//	ImGui::Text(Analyzer::Packets[i].c_str());
		//}

		//for (int i = size - 1; i >= 0; i--) {
		//	ImGui::Text(Analyzer::Packets[i].c_str());
		//}

		//// END: String version

		ImGui::EndChild();

		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;

	window = FindWindowA(NULL, windowName);

	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

void AttachImGui() {
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)&oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		}
	} while (!attached);
}

void ImGuiHelper::Initialize() {
	AttachImGui();
}