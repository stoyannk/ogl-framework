#pragma once

namespace oglwork
{
class RenderSystem;

class APP_EXPORTED_SYMBOL RenderingRoutine
{
public:
	void SetSystem(RenderSystem* system);
	virtual ~RenderingRoutine();

	virtual void PreDraw(double dt);
	virtual void Draw(double dt) = 0;
	virtual void PostDraw(double dt);

	RenderSystem* GetSystem() const { return m_System; }

private:
	RenderSystem* m_System;
};

}
