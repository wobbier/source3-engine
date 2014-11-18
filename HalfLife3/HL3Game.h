#pragma once
#include "Source3.h"

class HL3Game : public Source3 {
public:
	HL3Game();
	~HL3Game();
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;
	virtual void End() override;
	virtual void LogMessage() override;
};