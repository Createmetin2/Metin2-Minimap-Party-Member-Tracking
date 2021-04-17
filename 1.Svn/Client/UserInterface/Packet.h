//Find
	HEADER_GC_RESPOND_CHANNELSTATUS				= 210,
	
///Add
#if defined(__BL_PARTY_POSITION__)
	HEADER_GC_PARTY_POSITION_INFO 				= 235,
#endif

//Find
typedef struct packet_dead
{
	...
} TPacketGCDead;

///Add
#if defined(__BL_PARTY_POSITION__)
struct TPartyPosition
{
	DWORD	dwPID;
	long	lX;
	long	lY;
	float	fRot;
};

typedef struct SPacketGCPartyPosition
{
	BYTE bHeader;
	WORD wSize;
} TPacketGCPartyPosition;
#endif