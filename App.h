#pragma once
#include "Game.h"

#ifndef App_h
#define App_h



namespace app {
	class App
	{
	protected:
		Game game;
	public:
		void	Initialise(void);
		void	Load(void);
		void	Run(void);
		void	RunIteration(void);

		Game& GetGame(void);
		const Game& GetGame(void) const;
		virtual void	Clear(void);
		void Main(void);
	};
}

#endif // !App_h