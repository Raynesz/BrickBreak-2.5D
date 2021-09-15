#ifndef UI_H
#define UI_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Viewer.h"

ImGuiIO& InitializeUI(Viewer&);
void DrawUIAbout(bool*, bool*, ImGuiIO&, GLFWwindow*);
void DrawUIMetrics(bool* show, double dt);
void RenderUI();
void TerminateUI();
void NewUIFrame();

#endif
