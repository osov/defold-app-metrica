#if defined(DM_PLATFORM_IOS)

#include "extension_private.h"
#include "extension_callback_private.h"

using namespace dmAppMetrica;

#import <YandexMobileMetrica/YandexMobileMetrica.h>

namespace dmAppMetrica {
	void SendSimpleMessage(MessageId type, NSString *key, NSString *value) {
		char buffer[2048];
		uint32_t len = dmSnPrintf(buffer, sizeof(buffer), "{\"%s\": \"%s\"}", key.UTF8String, value.UTF8String);
		AddToQueueCallback(type, buffer);
	}

	YMMAdType stringToAdType(NSString *adType) {
		if ([adType isEqualToString:@"BANNER"]) {
			return YMMAdTypeBanner;
		} else if ([adType isEqualToString:@"REWARDED"]) {
			return YMMAdTypeRewarded;
		} else if ([adType isEqualToString:@"INTERSTITIAL"]) {
			return YMMAdTypeInterstitial;
		}
		return YMMAdTypeUnknown;
	}
}

#define ExtensionInterface Extension_appmetrica_Interface

@interface ExtensionInterface : NSObject
@end

@implementation ExtensionInterface

-(id)init:(NSString*)apiKey {
	YMMYandexMetricaConfiguration *configuration = [[YMMYandexMetricaConfiguration alloc] initWithApiKey:apiKey];
	//configuration.logs = YES;
	[YMMYandexMetrica activateWithConfiguration:configuration];
	SendSimpleMessage(MSG_TYPE_NONE, @"init", apiKey);
	return self;
}

-(void)ReportEvent:(NSString*)event eventParameters:(NSString*)eventParameters {
	if (eventParameters.length == 0) {
		[YMMYandexMetrica reportEvent:event onFailure:nil];
	} else {
		NSData *data = [eventParameters dataUsingEncoding:NSUTF8StringEncoding];
		NSError *err = nil;
		NSDictionary *params = [NSJSONSerialization JSONObjectWithData:data options:0 error:&err];
		if (!err) {
			[YMMYandexMetrica reportEvent:event parameters:params onFailure:nil];
		}
	}
}

-(void)SendRevenue:(NSString*)money networkName:(NSString*)networkName adUnitId:(NSString*)adUnitId precision:(NSString*)precision adType:(NSString*)adType {
	YMMMutableAdRevenueInfo *adRevenue = [[YMMMutableAdRevenueInfo alloc] initWithAdRevenue:[NSDecimalNumber decimalNumberWithString:money] currency:@"USD"];
	adRevenue.adNetwork = networkName;
	adRevenue.adUnitID = adUnitId;
	adRevenue.precision = precision;
	adRevenue.adType = stringToAdType(adType);
	[YMMYandexMetrica reportAdRevenue:adRevenue onFailure:nil];
}

@end

/* #region C++ interface */

static ExtensionInterface *extension_instance;

namespace dmAppMetrica {
	void Initialize_Ext() {
		extension_instance = [ExtensionInterface alloc];
	}

	void ActivateApp() {
	}

	void Initialize(const char *api_key) {
		[extension_instance init:@(api_key)];
	}

	void ReportEvent(const char *event, const char *eventParameters) {
		[extension_instance ReportEvent:@(event) eventParameters:@(eventParameters)];
	}

	void SendRevenue(const char *money, const char *network_name, const char *ad_unit_id, const char *precision, const char *ad_type) {
		[extension_instance SendRevenue:@(money) networkName:@(network_name) adUnitId:@(ad_unit_id) precision:@(precision) adType:@(ad_type)];
	}
}

/* #endregion */

#endif
