#if defined(DM_PLATFORM_ANDROID) 

#pragma once

namespace dmAppMetrica {

void Initialize_Ext();

void Initialize(const char* unitId);

void ActivateApp();

void ReportEvent(const char* s1, const char* s2);
void SendRevenue(const char* money, const char* network_name, const char* ad_unit_id, const char* precision, const char* ad_type);

}

#endif
