//Find
	m_PartyMemberMap.insert(make_pair(dwPID, TPartyMemberInfo(dwPID, c_szName)));
	
///Add
#if defined(__BL_PARTY_POSITION__)
	if (strlen(c_szName) == 0) // offline
		CPythonMiniMap::Instance().RemovePartyPositionInfo(dwPID);
#endif