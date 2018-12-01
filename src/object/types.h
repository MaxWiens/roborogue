#ifndef types_h
#define types_h
typedef enum Types
{
	TypeGameObject			= 0x0000,

	TypeEntity				= 0x0001,
		TypeComponent		= 0x0002|TypeEntity,
			TypeCPU			= 0x0004|TypeComponent,
			TypePowerSupply	= 0x0008|TypeComponent,
			TypeChassis		= 0x0010|TypeComponent,
		TypeItem			= 0x0020|TypeEntity,
	TypeCharacter			= 0x0040,
	TypeTile				= 0x0080,
		TypeFloor			= 0x0100|TypeTile,
		TypeWall			= 0x0200|TypeTile,


}Types;
#endif//types_h