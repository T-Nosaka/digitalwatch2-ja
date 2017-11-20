#include <pebble.h>
#include "syukujitsu.h"
#include "mooncalc.h"
#include "analogclock.h"
#include "getwether.h"
#include "messagelist.h"
#include "utf8tool.h"
#include "scrolltxt.h"
#include "fmvhash.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_back_white;
static GFont s_res_font_open_52;
static GFont s_res_font_open_24;
static GFont s_res_font_moongraph_30;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_18;
static BitmapLayer *s_backlayer;
static TextLayer *s_timetext;
static TextLayer *s_datetext;
static TextLayer *s_sectext;
static TextLayer *s_moontext;
static Layer *s_analogclock;
static TextLayer *s_temptext;
static TextLayer *s_wdaytext;
static TextLayer *s_kindtext;
static TextLayer *s_messagetext;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorClear);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_image_back_white = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACK);
  s_res_font_open_52 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OPEN_52));
  s_res_font_open_24 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OPEN_24));
  s_res_font_moongraph_30 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_MOONGRAPH_30));
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  // s_backlayer
  s_backlayer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_backlayer, s_res_image_back_white);
  bitmap_layer_set_background_color(s_backlayer, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_backlayer);
  
  // s_timetext
  s_timetext = text_layer_create(GRect(3, 101, 110, 64));
  text_layer_set_background_color(s_timetext, GColorClear);
  text_layer_set_text_color(s_timetext, GColorFromRGB ( 255, 0, 85));
  text_layer_set_text(s_timetext, " ");
  text_layer_set_text_alignment(s_timetext, GTextAlignmentCenter);
  text_layer_set_font(s_timetext, s_res_font_open_52);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_timetext);

  // s_datetext
  s_datetext = text_layer_create(GRect(5, 74, 105, 27));
  text_layer_set_background_color(s_datetext, GColorClear);
  text_layer_set_text_color(s_datetext, GColorFromRGB ( 255, 255, 0));
  text_layer_set_text(s_datetext, " ");
  text_layer_set_text_alignment(s_datetext, GTextAlignmentCenter);
  text_layer_set_font(s_datetext, s_res_font_open_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_datetext);
  
  // s_sectext
  s_sectext = text_layer_create(GRect(116, 127, 23, 26));
  text_layer_set_background_color(s_sectext, GColorClear);
  text_layer_set_text_color(s_sectext, GColorFromRGB ( 255, 255, 85));
  text_layer_set_text(s_sectext, " ");
  text_layer_set_text_alignment(s_sectext, GTextAlignmentCenter);
  text_layer_set_font(s_sectext, s_res_font_open_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_sectext);
  
  // s_moontext
  s_moontext = text_layer_create(GRect(99, 7, 40, 41));
  text_layer_set_background_color(s_moontext, GColorClear);
  text_layer_set_text_color(s_moontext, GColorFromRGB ( 255, 255, 0));
//  text_layer_set_text_color(s_moontext, GColorWhite);
  text_layer_set_text(s_moontext, "0");
  text_layer_set_text_alignment(s_moontext, GTextAlignmentCenter);
  text_layer_set_font(s_moontext, s_res_font_moongraph_30);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_moontext);
  
  // s_analogclock
  s_analogclock = layer_create(GRect(5, 5, 41, 40));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_analogclock);
  
  // s_temptext
  s_temptext = text_layer_create(GRect(49, 5, 46, 19));
  text_layer_set_background_color(s_temptext, GColorClear);
  text_layer_set_text_color(s_temptext, GColorFromRGB ( 255, 255, 85));
  text_layer_set_text(s_temptext, " ");
  text_layer_set_text_alignment(s_temptext, GTextAlignmentCenter);
  text_layer_set_font(s_temptext, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_temptext);
  
  // s_wdaytext
  s_wdaytext = text_layer_create(GRect(113, 77, 27, 25));
  text_layer_set_background_color(s_wdaytext, GColorClear);
  text_layer_set_text_color(s_wdaytext, GColorFromRGB ( 255, 255, 255));
  text_layer_set_text(s_wdaytext, " ");
  text_layer_set_text_alignment(s_wdaytext, GTextAlignmentCenter);
  text_layer_set_font(s_wdaytext, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_wdaytext);
  
  // s_kindtext
  s_kindtext = text_layer_create(GRect(50, 25, 45, 20));
  text_layer_set_background_color(s_kindtext, GColorClear);
  text_layer_set_text_color(s_kindtext, GColorFromRGB ( 255, 255, 85));
  text_layer_set_text(s_kindtext, " ");
  text_layer_set_text_alignment(s_kindtext, GTextAlignmentCenter);
  text_layer_set_font(s_kindtext, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_kindtext);
  
  // s_messagetext
  s_messagetext = text_layer_create(GRect(6, 48, 132, 22));
  text_layer_set_background_color(s_messagetext, GColorClear);
   text_layer_set_text_color(s_messagetext, GColorFromRGB ( 255, 170, 0));
  text_layer_set_text(s_messagetext, " ");
  text_layer_set_font(s_messagetext, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_messagetext);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_backlayer);
  text_layer_destroy(s_timetext);
  text_layer_destroy(s_datetext);
  text_layer_destroy(s_sectext);
  text_layer_destroy(s_moontext);
  layer_destroy(s_analogclock);
  text_layer_destroy(s_temptext);
  text_layer_destroy(s_wdaytext);
  text_layer_destroy(s_kindtext);
  text_layer_destroy(s_messagetext);
  gbitmap_destroy(s_res_image_back_white);
  fonts_unload_custom_font(s_res_font_open_52);
  fonts_unload_custom_font(s_res_font_open_24);
  fonts_unload_custom_font(s_res_font_moongraph_30);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_gui(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_gui(void) {
  window_stack_remove(s_window, true);
}

/*
 * 祝日出力用
 */
static char s_week[30];

/*
 * 同タイプのメッセージ削除
 */
void deletePrevMessageType( uint32_t type )
{
  for( int iIdx=0; iIdx<messagelist_size();iIdx++ )
  {
    message_data_t* ps = messagelist_getstruct( iIdx );
    if( ps->type == type )
    {
      messagelist_remove( iIdx );
      break;
    }
  }
  
  ScrollText_cancel();
}

/*
 * 同タイプの同じメッセージ削除
 */
void deletePrevSameMessageType( uint32_t type, uint32_t hashkey )
{
  for( int iIdx=0; iIdx<messagelist_size();iIdx++ )
  {
    message_data_t* ps = messagelist_getstruct( iIdx );
    if( ps->type == type && ps->hashkey == hashkey )
    {
      messagelist_remove( iIdx );
      break;
    }
  }
  
  ScrollText_cancel();
}

/*
 * 祝日結果出力
 */
void ResultOut2( char* mes, struct tm targetdate, HolidayType holiday )
{
  snprintf(s_week,sizeof(s_week),"%s",mes );

  //前の情報を削除する。
  deletePrevMessageType(1);
  
  //祝日表示
  messagelist_push( s_week, MAX_MESSAGE_LENGTH, 1 );
}

/*
 * 最後に更新した日
 */
int m_last_yy=0;
int m_last_mm=0;
int m_last_dd=0;

/*
 * メッセージインデックス
 */
static int message_idx=-1;

/*
 * スクロール完了コールバック
 */
void OnFinishScroll()
{
  //次のメッセージ
  message_idx++;
  
  //メッセージ表示
  int mes_size = messagelist_size();
  if( message_idx >= mes_size )
  {
    if( mes_size == 0 )
    {
      message_idx = -1;
      return;
    }
    
    //先頭に戻す
    message_idx = 0;
  }

  //ッセージを取得
  char* pmes = messagelist_get(message_idx);
  int meslength = utf8_strlen( pmes );
     
  //メッセージセット
  ScrollText_contents( pmes, meslength );
}

/*
 * 更新カウント
 */
static int m_update_count=0;

/*
 * 時刻
 */
void update_time() {
  
  m_update_count++;
  
  //現在時刻取得
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
/*
  //スクリーンショット用
  tick_time->tm_year = 2016-1900;
  tick_time->tm_mon = 3-1;
  tick_time->tm_mday = 21;
  tick_time->tm_wday = 1;
*/ 
  
  //表示文字列作成
  static char s_time[11],s_time1[7],s_time2[4];
  strftime(s_time, sizeof(s_time), "%Y_%m_%d", tick_time );
  if( clock_is_24h_style() == true ) {
    text_layer_set_text_color(s_timetext, GColorFromRGB ( 255, 255, 85));
    strftime(s_time1, sizeof(s_time1), "%H:%M", tick_time );
  }
  else {
    if( tick_time->tm_hour >= 12 ) {
      text_layer_set_text_color(s_timetext, GColorFromRGB ( 255, 255, 85));
    } else {
      text_layer_set_text_color(s_timetext, GColorFromRGB ( 0, 170, 255));
    }
    strftime(s_time1, sizeof(s_time1), "%I:%M", tick_time );
  }
  strftime(s_time2, sizeof(s_time2), "%S", tick_time );
 
   //文字列設定
  text_layer_set_text(s_datetext, s_time);
  text_layer_set_text(s_timetext, s_time1);
  text_layer_set_text(s_sectext, s_time2);

  //曜日出力
  int yy = tick_time->tm_year+1900;
	int mm = tick_time->tm_mon+1;
	int dd = tick_time->tm_mday;
	int ww = tick_time->tm_wday; 
  
  if( m_last_yy != yy || m_last_mm != mm || m_last_dd != dd )
  {
    //日替わり発生
    //曜日
    char* wday = "";
    GColor wdaycolor = GColorFromRGB ( 255, 255, 255);
    switch( ww )
    {
      case 0:
      wday = "日";
      wdaycolor = GColorFromRGB ( 255, 0, 0);
      break;
      case 1:
      wday = "月";
      break;
      case 2:
      wday = "火";
      break;
      case 3:
      wday = "水";
      break;
      case 4:
      wday = "木";
      break;
      case 5:
      wday = "金";
      break;
      case 6:
      wday = "土";
      wdaycolor = GColorFromRGB ( 0, 170, 255);
      break;
      default:
      wday = "";
      break;
    }

    //曜日
    static char s_wday[4];
    snprintf(s_wday,sizeof(s_wday),"%s",wday );
    text_layer_set_text_color(s_wdaytext, wdaycolor);
    
    // 祝日対応
    s_week[0] = (char)0x00;
    HolidayType holiday = Syukujitu( yy, mm, dd, ww, ResultOut2 );

    //祝日の場合、赤にする。
    if( holiday != WEEKDAY ) {
      text_layer_set_text_color(s_wdaytext, GColorFromRGB ( 255, 0, 85));
    }
    text_layer_set_text(s_wdaytext, s_wday);
    
    // 月齢
    int iMoonAge = mooncalc( yy, mm, dd );
    setmoontext( iMoonAge, s_moontext );

    //メッセージクリア
    messagelist_clear();
    
    //要求
    request_js( 1, 1 );
    
    //日替わり日を記録
    m_last_yy = yy;
    m_last_mm = mm;
    m_last_dd = dd;
  }
  else
  if( tick_time->tm_min == 0 && tick_time->tm_sec == 0 )
  {
    // 祝日対応
    s_week[0] = (char)0x00;
    Syukujitu( yy, mm, dd, ww, ResultOut2 );

    //要求
    request_js( 1, 1 );
  }

  if( message_idx == -1 )
  {
    //非表示中
    //メッセージ確認
    int mes_size = messagelist_size();
    
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Message Start %d", mes_size);
    
    if( mes_size > 0 )
    {
      //最初のメッセージを取得
      message_idx = 0;
      char* pmes = messagelist_get(message_idx);
      int meslength = utf8_strlen( pmes );
      
      //メッセージセット
      ScrollText_contents( pmes, meslength );
    }
  }
  else
  {
    //表示中
    //スクロール進行
    ScrollText_beat();
  }
}

/*
 * 秒周期ハンドル
 */
void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
   update_time();
  
  //アナログ時計描画
  layer_mark_dirty(s_analogclock);
}

/*
 * 受信発生
 */
static void OnReceive(Tuple *tuple) {
  int key = (int)tuple->key;
  const char* val = tuple->value->cstring;
  
  switch (key) {
    case NEWS_RES_TITLE_KEY0:
      if( val[0] != 0x00 )
      {
        uint32_t hashkey = fnv_1_hash_32((uint8_t*)val, utf8_strlenb(val));
        deletePrevSameMessageType( 3, hashkey );
        
        APP_LOG(APP_LOG_LEVEL_DEBUG, "NEWS_RES_TITLE_KEY : %s", val);
        messagelist_push( (char*)val, MAX_MESSAGE_LENGTH, 3 );
      }
      break;
    case WEATHER_CITY_KEY:
      if( val[0] != 0x00 )
      {
        deletePrevMessageType(2);
        messagelist_push( (char*)val, MAX_MESSAGE_LENGTH, 2 );
      }
      break;
    case WEATHER_TEMPERATURE_KEY:
      {
        static char temptext[10];
        memcpy(temptext,val,sizeof(temptext));
        text_layer_set_text(s_temptext,temptext);
      }
      break;
    case WEATHER_ICON_KEY:
      {
        int iVal = atoi(val);
        int iKind = iVal/100;
        switch( iKind )
        {
          case 2:
          text_layer_set_text(s_kindtext,"雷");
          break;
          case 3:
          text_layer_set_text(s_kindtext,"霧");
          break;
          case 5:
          text_layer_set_text(s_kindtext,"雨");
          break;
          case 6:
          text_layer_set_text(s_kindtext,"雪");
          break;          
          case 7:
          text_layer_set_text(s_kindtext,"異");
          break;          
          case 8:
          {
            if( iVal == 800 )
              text_layer_set_text(s_kindtext,"晴");
            else
              text_layer_set_text(s_kindtext,"曇");
          }
          break;
          case 9:
          text_layer_set_text(s_kindtext,"極");
          break; 
          default:
          text_layer_set_text(s_kindtext,"不");
          break;
        }
      }
      break;
  }
}


/*
 * メイン
 */
int main(void) {
  
  //アナログ時計初期設定
  setup_analogclock();
  
  //画面設定
  show_gui();

  //天気取得初期設定
  setup_wether(OnReceive);
  
  //アナログ時計描画コールバック登録
  layer_set_update_proc(s_analogclock, analogclock_layer_update_callback);
  
  //秒周期イベントコールバック登録
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);

  //スクロール初期処理
  ScrollText_set( s_messagetext, OnFinishScroll );
  
  app_event_loop();
  
  destroy_analogclock();
}