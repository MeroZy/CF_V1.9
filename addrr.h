#define FireWeaponAddress  0x91E20

#define ADDR_DIPENGINE_1		0x004DBD46
#define ADDR_DIPENGINE_2		0x004D4AA4
//ADDR_DIPENGINE_1:
//8b 80 48 01 00 00 57 51 55 52 6a 00 6a 04 53 ff d0 85 c0 7c ??

//ADDR_DIPENGINE_2:
//8b 88 48 01 00 00 55 6a 00 53 6a 00 6a 00 6a 04 57 ff d1 85 c0 7c ??
//10D66586  |. 330495 38814A11               |XOR EAX,DWORD PTR DS:[EDX*4+114A8138]

#define check1                          0x5C9BBC	// aob: 75 ?? 32 ?? 5B 8B ?? ?? ?? ?? ??
#define check2                          0x5C9BB4	// aob: 73 ?? 85 ?? ?? ?? 85 ?? ?? ?? 32
#define check3                          0x5C9BB8	// aob: 7E ?? 85 ?? ?? ?? 32 ??
#define check4                          0x5CADCB	// aob: 75 ?? 32 ?? E9 ?? ?? ?? ?? 55
#define check5                          0x5C9BBE	// aob: 7E ?? 57 53 E8 ?? ?? ?? ??
#define check6                          0x5C9BD8	// aob: 7E ?? 57 8D ?? ?? ?? 53 51 E8 olly
#define hackDetect_1			0x5CD801			// aob: E8 ?? ?? ?? ?? 83 ?? ?? 8B ?? 85 ?? 8B ?? 89 ?? ?? ?? olly
#define hackDetect_2			0x5CA12B			// aob: E8 ?? ?? ?? ?? 8D ?? ?? 83 ?? ?? 89 ?? ?? 8B ?? 2B ??
#define hackDetect_3			0x5CA163			// aob: E8 ?? ?? ?? ?? ?? ?? A1 ?? ?? ?? ?? 83 C0 ?? 83 olly
#define hackDetect_4			0x5CAB72			// aob: E8 ?? ?? ?? ?? 8B ?? ?? ?? 83 ?? ?? 89 ?? 33 ?? 85 ??
#define hackDetect_5			0x5CA681			// aob: E8 ?? ?? ?? ?? 83 ?? ?? 39 ?? ?? ?? ?? ?? 55 olly
#define hackDetect_6			0x5CB2E0			// aob: E8 ?? ?? ?? ?? 83 ?? ?? 39 ?? ?? ?? ?? ?? 55 olly
#define awsawsModelN000de 0x1C3A19C


#define aLTClientShell 0x14B04B0
#define dwCPlayerStart 0x208
#define dwCPlayerSize 0xD80
#define MEOffset 0x214
#define aLTModel 0x14AB79C






#define M4A1 11
#define M4A1PRISM 1721
#define AK47 12
#define AK47SavageBeast 731
#define AK47KnifeBornBeast 1616
#define AN94KnifeSupernova 1997
#define DesertEagle 20
#define	DesertEagleElDorado 1848
#define	KNIFE 5
#define	KukriBeast 1003
#define M4A1SGSpirit 2058 
#define	Glock18CGSpirit 2061
#define	M4A1CDevilWing 2448
#define AK47BlueCrystal 623
#define	DEBlueCrystal 626
#define	AWMUltimateSilver 632
#define AK47KnifeIronBeast 1269
#define BarrettIronShark 1394
#define M82A1GoldPhoenix 2176
#define M700 14
#define M16 25
#define ShovelObsidianBeast 1620
#define AWM 15