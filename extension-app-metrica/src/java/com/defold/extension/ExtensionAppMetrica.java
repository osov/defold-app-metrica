package com.defold.extension;

import androidx.annotation.NonNull;
import android.util.Log;
import android.app.Activity;
import android.view.Display;
import android.view.Gravity;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewGroup.MarginLayoutParams;
import android.content.Context;
import android.content.SharedPreferences;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;

import com.yandex.metrica.YandexMetrica;
import com.yandex.metrica.YandexMetricaConfig;

import java.math.BigDecimal;
import java.util.Currency;
import java.util.HashMap;
import java.util.Map;
import com.yandex.metrica.AdRevenue;
import com.yandex.metrica.AdType;

public class ExtensionAppMetrica {

  private static final String TAG = "ExtensionAppMetrica";
  public static native void AddToQueue(int msg, String json);
  private static final int MSG_TYPE_NONE = 1;

  private static final int EVENT_NOT_SUPPORTED = 100;
  private static final int EVENT_JSON_ERROR = 101;
  private Activity activity;


  public ExtensionAppMetrica(Activity mainActivity) {
    activity = mainActivity;
  }

  public void initialize(final String key) {
    activity.runOnUiThread(new Runnable() {
      @Override
      public void run() {
        Log.d(TAG, "initialize");
        YandexMetricaConfig config = YandexMetricaConfig.newConfigBuilder(key).build();
				// Initializing the AppMetrica SDK.
				YandexMetrica.activate(activity.getApplicationContext(), config);
				// Automatic tracking of user activity.
				YandexMetrica.enableActivityAutoTracking(activity.getApplication());
        sendSimpleMessage(MSG_TYPE_NONE, "init", key);
      }
    });
  }

  public void ReportEvent(final String event, final String eventParameters) {
  	activity.runOnUiThread(new Runnable() {
      @Override
      public void run() {
        Log.d(TAG, "ReportEvent:"+event);
        Log.d(TAG, "eventParameters:"+eventParameters);
        if (eventParameters.equals(""))
        	YandexMetrica.reportEvent(event);
        else
        	YandexMetrica.reportEvent(event, eventParameters);
      }
    });
  }

  public void SendRevenue(final String money, final String network_name, final String ad_unit_id, final String precision, final String ad_type){
        AdType _ad_type;
        _ad_type = AdType.NATIVE;
        if (ad_type.equals("BANNER"))
            _ad_type = AdType.BANNER;
        else if (ad_type.equals("REWARDED"))
            _ad_type = AdType.REWARDED;
        else if (ad_type.equals("INTERSTITIAL"))
            _ad_type = AdType.INTERSTITIAL;
        //передать значение из поля revenue_USD из объекта impressionData и валюту USD
        AdRevenue adRevenue = AdRevenue.newBuilder(new BigDecimal(money), Currency.getInstance("USD"))
        //передать значение из поля network.name из объекта impressionData
        .withAdNetwork(network_name)
        //задать значение в зависимости от того, какое значение пришло в поле adType
        .withAdType(_ad_type)
        //передать значение из поля ad_unit_id из объекта impressionData
        .withAdUnitId(ad_unit_id)
        //передать значение из поля precision из объекта impressionData
         .withPrecision(precision)
         .build();
        YandexMetrica.reportAdRevenue(adRevenue);
        Log.d(TAG, "sendRevenue:"+money+"/"+network_name+"/"+ad_unit_id+"/"+precision+"/"+ad_type+"-"+_ad_type);
    }

  private String getJsonConversionErrorMessage(String messageText) {
    String message = null;
    try {
      JSONObject obj = new JSONObject();
      obj.put("error", messageText);
      obj.put("event", EVENT_JSON_ERROR);
      message = obj.toString();
    } catch (JSONException e) {
      message = "{ \"error\": \"Error while converting simple message to JSON.\", \"event\": " + EVENT_JSON_ERROR
          + " }";
    }
    return message;
  }


  private void sendSimpleMessage(int msg, String key, String value) {
    String message = null;
    try {
      JSONObject obj = new JSONObject();
      obj.put(key, value);
      message = obj.toString();
    } catch (JSONException e) {
      message = getJsonConversionErrorMessage(e.getLocalizedMessage());
    }
    AddToQueue(msg, message);
  }


}
