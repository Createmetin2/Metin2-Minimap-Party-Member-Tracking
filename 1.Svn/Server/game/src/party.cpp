///Add
#if defined(__BL_PARTY_POSITION__)
EVENTINFO(party_position_event_info)
{
	LPPARTY pParty;
	party_position_event_info(LPPARTY mParty) 
		: pParty(mParty)
	{}
};

EVENTFUNC(party_position_event)
{
	const party_position_event_info* info = dynamic_cast<party_position_event_info*>(event->info);

	if (info == NULL || info->pParty == NULL)
	{
		sys_err("party_position_event> <Factor> Null pointer");
		return 0;
	}

	info->pParty->SendPositionInfo();
	return PASSES_PER_SEC(3);
}
#endif

//Find
	m_eventUpdate = NULL;
	
///Add
#if defined(__BL_PARTY_POSITION__)
	m_PositionInfoEvent = NULL;
#endif

//Find
	event_cancel(&m_eventUpdate);
	
///Add
#if defined(__BL_PARTY_POSITION__)
	event_cancel(&m_PositionInfoEvent);
#endif

//Find
	pkChr->SetParty(this);
	
///Add
#if defined(__BL_PARTY_POSITION__)
	if (m_bPCParty && m_PositionInfoEvent == NULL)
		m_PositionInfoEvent = event_create(party_position_event, new party_position_event_info(this), PASSES_PER_SEC(1));
#endif

///Add to end
#if defined(__BL_PARTY_POSITION__)
#include "buffer_manager.h"
void CParty::SendPositionInfo() const
{
	for (TMemberMap::const_iterator it = m_memberMap.begin(); it != m_memberMap.end(); ++it) {
		const LPCHARACTER ch = it->second.pCharacter;
		if (ch == NULL || ch->GetDesc() == NULL)
			continue;

		TEMP_BUFFER buf;
		for (TMemberMap::const_iterator it2 = m_memberMap.begin(); it2 != m_memberMap.end(); ++it2) {
			if (it == it2)
				continue;

			const LPCHARACTER ch2 = it2->second.pCharacter;
			if (ch2 == NULL || ch2->GetDesc() == NULL)
				continue;

			if (ch->GetMapIndex() != ch2->GetMapIndex())
				continue;

			TPartyPosition T;
			T.dwPID = ch2->GetPlayerID();
			T.lX = ch2->GetX();
			T.lY = ch2->GetY();
			T.fRot = ch2->GetRotation();
			buf.write(&T, sizeof(T));
		}

		if (buf.size()) {
			TPacketGCPartyPosition packet;
			packet.bHeader = HEADER_GC_PARTY_POSITION_INFO;
			packet.wSize = sizeof(packet) + buf.size();
			ch->GetDesc()->BufferedPacket(&packet, sizeof(packet));
			ch->GetDesc()->Packet(buf.read_peek(), buf.size());
		}
	}
}
#endif