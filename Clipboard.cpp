#include "Clipboard.h"

std::vector<uint32_t> Clipboard::m_types { CF_TEXT, CF_UNICODETEXT };

void Clipboard::GetData(uint16_t format, void* dataDestination) {
	if(GetPriorityClipboardFormat(&m_types[0], (int32_t)m_types.size()) > 0 && OpenClipboard(nullptr)) {

		void* dataHandle = GetClipboardData(format);
		if(dataHandle != nullptr) {

			void* data = GlobalLock(dataHandle);
			if(data != nullptr) {
				switch(format) {
					case CF_TEXT:
						*((std::string*)dataDestination) = (char*)data;
						break;

					case CF_UNICODETEXT:
						*((std::wstring*)dataDestination) = (wchar_t*)data;
						break;
				}

				GlobalUnlock(dataHandle);
			}
		}

		CloseClipboard();
	}
}