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
