/*
  ==============================================================================

    AsyncCallback.h
    Created: 10 Nov 2022 1:34:46pm
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/**
	This class is constructed with a pointer to a callback function.
	This class currently only handles the asynchronous callback of the editor renderer's configure function,
	but has been genericized enough that it would work with most callbacks
*/
class AsyncCallback  : private juce::AsyncUpdater
{
public:
	explicit AsyncCallback (std::function<void()> callbackIn)
		: callback (std::move (callbackIn)) {}

	~AsyncCallback() override { cancelPendingUpdate(); }

	template <typename RequiresLock>
	auto withLock (RequiresLock&& fn)
	{
		const juce::SpinLock::ScopedTryLockType scope (processingFlag);
		return fn (scope.isLocked());
	}

	void startCallback() { triggerAsyncUpdate(); }

private:
	void handleAsyncUpdate() override
	{
		const juce::SpinLock::ScopedLockType scope (processingFlag);
		callback();
	}

	std::function<void()> callback;
	juce::SpinLock processingFlag;
};
