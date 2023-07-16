
#include "BaseQueue.h"

SlackEngine::Render::BaseQueue::~BaseQueue()
{
	//Empty here
}

vk::Queue* SlackEngine::Render::BaseQueue::get_queue()
{
	return &queue_;
}

SlackEngine::Render::BaseQueue::operator vk::Queue() const
{
	return queue_;
}
