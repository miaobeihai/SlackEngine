

//Init static instance reference

#include "VulkanSurface.h"

#include <GLFW/glfw3.h>

#include "DebugLog.h"
#include "GameWindow.h"
#include "Instance/VukanInstance.h"
SlackEngine::Render::VulkanSurface* SlackEngine::Render::VulkanSurface::instance_ = nullptr;

//Class

void SlackEngine::Render::VulkanSurface::init(GameWindow* window_ref)
{
	create_surface(window_ref);
}

SlackEngine::Render::VulkanSurface::~VulkanSurface()
{
	VukanInstance::get_instance()->get_vulkan_instance()->destroySurfaceKHR(surface_);
}

SlackEngine::Render::VulkanSurface* SlackEngine::Render::VulkanSurface::get_instance()
{
	if (instance_ == nullptr)
	{
		instance_ = new VulkanSurface();
	}
	return instance_;
}

void SlackEngine::Render::VulkanSurface::create_surface(GameWindow* window_ref)
{
	surface_ = vk::SurfaceKHR();
	if (glfwCreateWindowSurface(*VukanInstance::get_instance(), window_ref->window_, nullptr,
	                            reinterpret_cast<VkSurfaceKHR*>(&surface_)) != VK_SUCCESS)
	{
		Debug::DebugLog::fatal_error(vk::Result(-13), "VulkanSurface: Failed to create window surface!");
	}
}

vk::SurfaceKHR* SlackEngine::Render::VulkanSurface::get_surface()
{
	return &surface_;
}
