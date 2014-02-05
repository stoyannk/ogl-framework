#pragma once

namespace oglwork
{

class APP_EXPORTED_SYMBOL RenderingRoutine
{
public:
	virtual ~RenderingRoutine();

	virtual void PreDraw(double dt) = 0;
	virtual void Draw(double dt) = 0;
	virtual void PostDraw(double dt) = 0;
};

}
