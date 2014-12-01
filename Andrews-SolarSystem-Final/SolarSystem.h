#pragma once
#include "Source3.h"

class SolarSystem : public Source3 {
public:
	SolarSystem();
	~SolarSystem();
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;
	virtual void End() override;
	virtual void LogMessage() override;
};