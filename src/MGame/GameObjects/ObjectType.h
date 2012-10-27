#pragma once

class ObjectType
{
public:
	enum Type
	{
		//Player (type 0)
		Death = 0,

		//Enemies (1 - 70)
		Enemy = 1,
		Skeletons = 2,
		PumpkinHead = 3,
		Zombies = 4,
		Bats = 5,
		Vampires = 6,
		Ghouls = 7,
		HeadlessHorseKnight = 8,
		Knight = 9,
		Witches = 10,
		Demon = 11,
		HauntedArmor = 12,
		FrankensteinMonsters = 13,

		//Power Ups (71-99)


		//Environment Lower Layer (100 - 199)
		Floor = 100,

		//Environment Upper Layer (200 - 299)
		HigherLayerFloor = 200,
		Tree = 201,

		//Attacks (300+)
		PlayerMelee = 301,

		PassableWithoutEffect = 999
	};
};