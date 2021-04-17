//Find
		void		SendPartyUnlinkOneToAll(LPCHARACTER ch);
		
///Add
#if defined(__BL_PARTY_POSITION__)
		void		SendPositionInfo() const;
#endif

//Find
		LPEVENT		m_eventUpdate;
		
///Add
#if defined(__BL_PARTY_POSITION__)
		LPEVENT		m_PositionInfoEvent;
#endif