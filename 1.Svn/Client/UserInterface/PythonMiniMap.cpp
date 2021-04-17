///Add
#if defined(__BL_PARTY_POSITION__)
#include "PythonPlayer.h"
#endif

//Find in bool CPythonMiniMap::LoadAtlas()
	m_AtlasPlayerMark.Destroy();
	
///Add
#if defined(__BL_PARTY_POSITION__)
	mAtlasPartyPlayerMark.clear();
#endif

//Find
	if ((ELTimer_GetMSec() / 500) % 2)
		m_AtlasPlayerMark.Render();
		
///Change
#if defined(__BL_PARTY_POSITION__)
	if ((ELTimer_GetMSec() / 500) % 2)
	{
		for (auto it(mAtlasPartyPlayerMark.begin()); it != mAtlasPartyPlayerMark.end();)
		{
			CPythonPlayer::TPartyMemberInfo* pPartyMemberInfo;
			if (CPythonPlayer::Instance().GetPartyMemberPtr(it->first, &pPartyMemberInfo))
			{
				const auto& PartyInfo = it->second;

				long xPos = PartyInfo->lX;
				long yPos = PartyInfo->lY;
				float fRotation = (540.0f - PartyInfo->fRot);

				CInstanceBase* pkInst = CPythonCharacterManager::Instance().GetInstancePtrByName(pPartyMemberInfo->strName.c_str());
				if (pkInst) {
					TPixelPosition kInstPos;
					pkInst->NEW_GetPixelPosition(&kInstPos);
					xPos = kInstPos.x + m_dwAtlasBaseX;
					yPos = kInstPos.y + m_dwAtlasBaseY;
					fRotation = (540.0f - pkInst->GetRotation());
				}

				while (fRotation > 360.0f)
					fRotation -= 360.0f;
				while (fRotation < 0.0f)
					fRotation += 360.0f;
				PartyInfo->grMarkImage.SetRotation(fRotation);

				__GlobalPositionToAtlasPosition(xPos - m_dwAtlasBaseX, yPos - m_dwAtlasBaseY, 
					&PartyInfo->fScreenX, &PartyInfo->fScreenY);

				PartyInfo->grMarkImage.SetPosition(PartyInfo->fScreenX - static_cast<float>(PartyInfo->grMarkImage.GetWidth()) / 2.0f,
					PartyInfo->fScreenY - static_cast<float>(PartyInfo->grMarkImage.GetHeight()) / 2.0f);

				PartyInfo->grMarkImage.Render();
				++it;
			}
			else
				it = mAtlasPartyPlayerMark.erase(it);
		}
		m_AtlasPlayerMark.Render();
	}
#else
	if ((ELTimer_GetMSec() / 500) % 2)
		m_AtlasPlayerMark.Render();
#endif

//Find
	m_AtlasMarkInfoVectorIterator = m_AtlasWarpInfoVector.begin();
	while (m_AtlasMarkInfoVectorIterator != m_AtlasWarpInfoVector.end())
	{
		...
	}
	
///Add
#if defined(__BL_PARTY_POSITION__)
	for (const auto& PartyInfo : mAtlasPartyPlayerMark)
	{
		const float fffx = static_cast<float>(PartyInfo.second->lX) - static_cast<float>(m_dwAtlasBaseX);
		const float fffy = static_cast<float>(PartyInfo.second->lY) - static_cast<float>(m_dwAtlasBaseY);

		if (fffx - fCheckWidth / 2 < fRealX && fffx + fCheckWidth > fRealX &&
			fffy - fCheckWidth / 2 < fRealY && fffy + fCheckHeight > fRealY)
		{
			rReturnString = PartyInfo.second->sName;
			*pReturnPosX = fffx;
			*pReturnPosY = fffy;
			*pdwTextColor = CInstanceBase::GetIndexedNameColor(CInstanceBase::NAMECOLOR_PARTY);
			return true;
		}
	}
#endif

//Find in void CPythonMiniMap::Destroy()
	m_AtlasPlayerMark.Destroy();
	
///Add
#if defined(__BL_PARTY_POSITION__)
	mAtlasPartyPlayerMark.clear();
#endif

///Add to end
#if defined(__BL_PARTY_POSITION__)
void CPythonMiniMap::RemovePartyPositionInfo(DWORD dwPID)
{
	mAtlasPartyPlayerMark.erase(dwPID);
}

void CPythonMiniMap::AddPartyPositionInfo(const TPartyPosition& Info)
{
	SPartyPlayerPosition* PartyInfo = nullptr;
	auto it = mAtlasPartyPlayerMark.find(Info.dwPID);

	if (it == mAtlasPartyPlayerMark.end()) {
		CPythonPlayer::TPartyMemberInfo* pPartyMemberInfo;
		if (!CPythonPlayer::Instance().GetPartyMemberPtr(Info.dwPID, &pPartyMemberInfo))
			return;
		
		static const char* playerMarkFileName = "d:/ymir work/ui/minimap/playermark.sub";
		CGraphicSubImage* CImage = dynamic_cast<CGraphicSubImage*>(CResourceManager::Instance().GetResourcePointer(playerMarkFileName));
		if (CImage == nullptr) {
			Tracef(" CPythonMiniMap::AddPartyPositionInfo File Load %s ERROR\n", playerMarkFileName);
			return;
		}

		PartyInfo = new SPartyPlayerPosition();
		PartyInfo->sName = pPartyMemberInfo->strName; // Get Name From PythonPlayer Party Data
		PartyInfo->grMarkImage.SetImagePointer(CImage);
		mAtlasPartyPlayerMark.emplace(Info.dwPID, std::shared_ptr<SPartyPlayerPosition>(PartyInfo));
	}
	else
		PartyInfo = it->second.get(); // already exist

	PartyInfo->lX = Info.lX;
	PartyInfo->lY = Info.lY;
	PartyInfo->fRot = Info.fRot;
}
#endif