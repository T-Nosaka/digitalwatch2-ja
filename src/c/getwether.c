#include <pebble.h>
#include "getwether.h"

/*
 * JSメーセージ同期オブジェクト
 */
static AppSync sync;

/*
 * メッセージバッファ
 */
static uint8_t sync_buffer[MAX_TRANS_LENGTH];


/*
 * 同期エラーコールバック
 */
static void sync_error_callback(DictionaryResult dict_error, AppMessageResult app_message_error, void *context)
{
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync Error: %d", app_message_error);
}
 
/*
 * 同期メーセージ変化発生コールバック
 */
static void sync_tuple_changed_callback(const uint32_t key, const Tuple* new_tuple, const Tuple* old_tuple, void* context)
{
}

/*
 * 受信発生コールバック
 */
static js_receive_callback m_receive_callback = NULL;

/*
 * 受信発生
 */
static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  
  Tuple *tuple = dict_read_first(iterator);
  if (!tuple) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Received null");
    return;
  }

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Received: %d", (int)tuple->key );

  if( m_receive_callback != NULL ) {
    m_receive_callback(tuple);
  }
}

/*
 * JSへ取得要求
 */
void request_js( int wether, int news )
{
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  if (iter == NULL) {
    return;
  }
  if( wether > 0 )
    dict_write_uint8(iter, WEATHER_REQUEST_KEY, 1); //key, value
  if( news > 0 )
    dict_write_uint8(iter, NEWS_REQUEST_KEY, 1);
  dict_write_end(iter);
  app_message_outbox_send();
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "request_js : wether=%d news=%d", wether,news);
}

/*
 * JSコールバック設定
 */
void setup_wether(js_receive_callback receivecallback)
{
  //コールバック設定
  m_receive_callback = receivecallback;
  
  //通信路開通   
  const int inbound_size = MAX_TRANS_LENGTH;
  const int outbound_size = MAX_TRANS_LENGTH;
  app_message_open(inbound_size, outbound_size);

  //通信メッセージ
  Tuplet initial_values[] = {
    TupletCString(WEATHER_ICON_KEY, "0"),
    TupletCString(WEATHER_TEMPERATURE_KEY, "0\u00B0C"),
    TupletCString(WEATHER_CITY_KEY, ""),
    TupletCString(NEWS_RES_TITLE_KEY0, "")
  };
  
  app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values, ARRAY_LENGTH(initial_values),
      sync_tuple_changed_callback, sync_error_callback, NULL);
  
  app_message_register_inbox_received(inbox_received_callback);
}