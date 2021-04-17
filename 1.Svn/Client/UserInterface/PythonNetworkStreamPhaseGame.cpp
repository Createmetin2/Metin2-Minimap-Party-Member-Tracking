//Find
			case HEADER_GC_QUEST_INFO:
				ret = RecvQuestInfoPacket();
				break;
				
///Add
#if defined(__BL_PARTY_POSITION__)
			case HEADER_GC_PARTY_POSITION_INFO:
				ret = RecvPartyPositionInfo();
				break;
#endif

//Find
void CPythonNetworkStream::ToggleGameDebugInfo()
{
	...
}

///Add
#if defined(__BL_PARTY_POSITION__)
bool CPythonNetworkStream::RecvPartyPositionInfo()
{
	TPacketGCPartyPosition Packet;
	if (!Recv(sizeof(Packet), &Packet)) {
		Tracen("RecvPartyPositionInfo Error");
		return false;
	}

	for (auto iPacketSize = Packet.wSize - sizeof(Packet); iPacketSize > 0; iPacketSize -= sizeof(TPartyPosition)) {
		TPartyPosition PositionInfo;
		if (Recv(sizeof(PositionInfo), &PositionInfo))
			CPythonMiniMap::Instance().AddPartyPositionInfo(PositionInfo);
	}
	
	return true;
}
#endif