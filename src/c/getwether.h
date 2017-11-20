#pragma once

#define MAX_TRANS_LENGTH 200

/*
 * 受信発生コールバック
 */
typedef void (* js_receive_callback)(Tuple *tuple);

/*
 * メッセージ定義
 */
enum WeatherKey {
  WEATHER_ICON_KEY = 1,
  WEATHER_TEMPERATURE_KEY = 2,
  WEATHER_CITY_KEY = 3,
  WEATHER_REQUEST_KEY = 1001,
  NEWS_REQUEST_KEY = 1002,
  NEWS_RES_TITLE_KEY0 = 11
};

/*
 * JSコールバック設定
 */
void setup_wether(js_receive_callback receivecallback );

/*
 * JSへ取得要求
 */
void request_js( int wether, int news );

