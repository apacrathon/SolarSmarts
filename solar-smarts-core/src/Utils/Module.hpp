#pragma once

class Module
{
public:
	std::string ModuleName() { return "Unknown Module"; };

private:

};

static std::vector < std::shared_ptr < Module > > loadedModules;
template <typename T> __forceinline std::shared_ptr < T > LoadModule()
{
	auto mod = std::make_shared < T >();
	loadedModules.push_back(mod);

	//PRINT("Loading module %s...\n", mod->ModuleName().data());
	return mod;
}

// author: Raj Patel