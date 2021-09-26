#pragma once

namespace UI {
	ImGuiIO& Initialize(GLFWwindow*);
	void Render();
	void Terminate();
	void NewFrame();
}
