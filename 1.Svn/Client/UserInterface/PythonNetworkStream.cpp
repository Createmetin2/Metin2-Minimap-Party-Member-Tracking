//Find
			Set(HEADER_GC_MAIN_CHARACTER,			CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCMainCharacter), STATIC_SIZE_PACKET));
			
///Add
#if defined(__BL_PARTY_POSITION__)
			Set(HEADER_GC_PARTY_POSITION_INFO,	CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCPartyPosition), DYNAMIC_SIZE_PACKET));
#endif