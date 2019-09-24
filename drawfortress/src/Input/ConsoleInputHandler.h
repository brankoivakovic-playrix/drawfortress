#pragma once

#include "ConsoleInput.h"

class IConsoleInputHandler
{
public:
	IConsoleInputHandler() = default;
	IConsoleInputHandler(IConsoleInputHandler&&) = delete;
	IConsoleInputHandler(const IConsoleInputHandler&) = delete;

	IConsoleInputHandler& operator = (const IConsoleInputHandler&) = delete;
	IConsoleInputHandler& operator = (IConsoleInputHandler&&) = delete;
	
	virtual void Invoke(const ConsoleInput* e) const = 0;
	
	virtual ~IConsoleInputHandler() = default;

	virtual ConsoleInput::Type Type() const = 0;

};


template <class T>
class ConsoleInputHandler final : public IConsoleInputHandler
{
public:
	ConsoleInputHandler(const ConsoleInput::Type type, T* handlerClass, const std::function<void(const ConsoleInput*)> handler ):
	_type(type),
	_handlerClass(handlerClass),
	_handler(handler)
	{
	}

	void Invoke (const ConsoleInput* e) const override
	{
		_handler(e);
	}

	ConsoleInput::Type Type() const override
	{
		return _type;
	}
	
private:
	const ConsoleInput::Type _type;
	
	const T* _handlerClass;
	
	const std::function<void(const ConsoleInput*)> _handler;
};