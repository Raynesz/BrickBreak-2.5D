#pragma once

namespace UI {
	ImGuiIO& Initialize(GLFWwindow*);
	void DrawControls(bool*, ImGuiIO&);
	void DrawAbout(bool*, bool*, bool*, ImGuiIO&, GLFWwindow*);
	void DrawMetrics(bool*, double);
	void Render();
	void Terminate();
	void NewFrame();
}
