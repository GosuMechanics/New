#pragma once
#include <time.h>
#include "Engine.h"
#include <string>
#include "CObject.h"

class COrbWalker
{

public:

	void RightClick()
	{
		auto cursorpos = Engine::GetMouseWorldPosition();
		if (cursorpos.DistTo(me->GetPos()) <= HoldRadius)
			return;

		if (VK_SPACE)
		{
			POINT CurPos;
			GetCursorPos(&CurPos);
			int X = CurPos.x;
			int Y = CurPos.y;
			mouse_event(MOUSEEVENTF_RIGHTDOWN, X, Y, 0, 0);
			Sleep(10);
			mouse_event(MOUSEEVENTF_RIGHTUP, X, Y, 0, 0);
		}
		else
		{
			Engine::MoveTo(&Engine::GetMouseWorldPosition());
		}
	}


	void ResetMoveTimer()
	{
		movetimer = Engine::GameTickCount();
	}
	void ResetAttackTimer()
	{
		attacktimer = Engine::GameTickCount();
	}

	double CalcMoveDelay()
	{
		return (Engine::GameTickCount() - movetimer) / (double)CLOCKS_PER_SEC;
	}
	double CalcAttackDelay()
	{
		return (Engine::GameTickCount() - attacktimer) / (double)CLOCKS_PER_SEC*pWindMultipler;
	}

	bool MoveReady()
	{
		if (CalcMoveDelay() >= me->CalcWindup())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool AttackReady()
	{
		if (CalcAttackDelay() >= me->CalcAttackTime()*pWindMultipler)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	void Orbwalk(CObject* object)
	{
		std::string name = me->GetChampionName();
		if (object == nullptr)
		{
			RightClick();
			return;
		}

		if (AttackReady() && !strcmp(name.c_str(), "Kalista") == 0)
		{
			Engine::AttackTarget(object);
			ResetAttackTimer();
			ResetMoveTimer();
			attackmove = true;
		}
		else
		{
			if (strcmp(name.c_str(), "Kalista") == 0)
			{
				Engine::AttackTarget(object);
			}
		}
		if (MoveReady() && !strcmp(name.c_str(), "Kalista") == 0)
		{
			RightClick();
			ResetMoveTimer();
			attackmove = false;
		}
		else
		{
			if (strcmp(name.c_str(), "Kalista") == 0)
			{
				RightClick();
			}
		}
	}

	ULONGLONG movetimer, attacktimer;

	float pWindMultipler = 9999.9f;
	bool attackmove = true;

	float HoldRadius = 100;
};
