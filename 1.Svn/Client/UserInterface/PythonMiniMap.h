///Add
#if defined(__BL_PARTY_POSITION__)
#include "Packet.h"
#include <unordered_map>
#endif

//Find
		void DeleteTarget(int iID);
		
///Add
#if defined(__BL_PARTY_POSITION__)
		void RemovePartyPositionInfo(DWORD dwPID);
		void AddPartyPositionInfo(const TPartyPosition& Info);
#endif

//Find
		typedef struct
		{
			...
		} TMarkPosition;
		
///Add
#if defined(__BL_PARTY_POSITION__)
		struct SPartyPlayerPosition
		{
			~SPartyPlayerPosition()
			{
				grMarkImage.Destroy();
			}
			std::string sName;
			long	lX, lY;
			float	fScreenX, fScreenY;
			float	fRot;
			CGraphicExpandedImageInstance grMarkImage;
		};
#endif

//Find
		CGraphicExpandedImageInstance	m_AtlasPlayerMark;
		
///Add
#if defined(__BL_PARTY_POSITION__)
		std::unordered_map<DWORD, std::shared_ptr<SPartyPlayerPosition>> mAtlasPartyPlayerMark;
#endif