#include <Engine/Rendering/Manager/RenderManagerView.h>
#include <Engine/Rendering/Manager/RenderManager.h>

SlackEngine::Render::RenderManagerView::
RenderManagerView(RenderManager* input_render_manager_ref)
	: render_manager_ref_(input_render_manager_ref)
{
}

SlackEngine::Render::GameWindow* SlackEngine::Render::RenderManagerView::get_game_window() const
{
	return render_manager_ref_->get_game_window();
}
