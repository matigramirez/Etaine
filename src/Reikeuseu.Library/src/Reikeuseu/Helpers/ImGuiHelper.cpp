#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include <Reikeuseu/Helpers/ImGuiHelper.h>
#include <Reikeuseu/Analyzer.h>
#include <iostream>
#include <iomanip>
#include <sstream>

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

		static int n = 1;
		ImGui::BeginChild("Scrolling");

		//for (int i = 0; i < Analyzer::InOutPackets.size(); i++) {
		//	std::stringstream sStream;

		//	for (size_t j = 0; j < Analyzer::InOutPackets[i]->Length - 2; j++)
		//	{
		//		sStream << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)Analyzer::InOutPackets[i]->Data[j] << " ";
		//	}

		//	sStream << std::endl;

		//	std::string s = sStream.str();

		//	ImGui::Text("%s>> 0x%04X %s", Analyzer::InOutPackets[i]->Type, Analyzer::InOutPackets[i]->Opcode, s.c_str());
		//}

		auto size = Analyzer::Packets.size();

		//for (int i = 0; i < size; i++) {
		//	ImGui::Text(Analyzer::Packets[i].c_str());
		//}

		for (int i = size - 1; i >= 0; i--) {
			ImGui::Text(Analyzer::Packets[i].c_str());
		}

		//for (int i = 0; i < n; i++)
		//	ImGui::Text("%04d: Some text", i);
		ImGui::EndChild();

		if (ImGui::Button("Increment")) {
			n++;
		}

		static int counter = 0;

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

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