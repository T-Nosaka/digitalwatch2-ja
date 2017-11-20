#include <pebble.h>
#include "analogclock.h"

//針ポリゴン座標
const GPathInfo HOUR_PATH_INFO = {
  .num_points = 4,
  .points = (GPoint []) {{-3, 10}, {-3, 0}, {3, 0},{3,10}} };
const GPathInfo MINUTE_PATH_INFO = {
  .num_points = 4,
  .points = (GPoint []) {{-3, 18}, {-3, 0}, {3, 0},{3,18}} };

//針のパス
static GPath *s_hour_path_ptr = NULL;
static GPath *s_minute_path_ptr = NULL;

/*
 * アナログ時計セットアップ
 */
void setup_analogclock()
{
  s_hour_path_ptr = gpath_create(&HOUR_PATH_INFO);
  s_minute_path_ptr = gpath_create(&MINUTE_PATH_INFO);
}

/*
 * アナログ時計破棄
 */
void destroy_analogclock()
{
  gpath_destroy(s_hour_path_ptr);
  gpath_destroy(s_minute_path_ptr);
}

/*
 * アナログ時計針描画
 */
void DrawClock(Layer *layer, GContext* ctx, GPoint center, GPath* path, float angle, GColor color )
{
  //中心移動
  gpath_move_to(path, center);
  //回転
  gpath_rotate_to(path, ((float)TRIG_MAX_ANGLE / 360.0f) * angle);

  //描画
  graphics_context_set_fill_color(ctx, color);
  gpath_draw_filled(ctx, path);
}

/*
 * アナログ時計レイヤー更新
 */
void analogclock_layer_update_callback(Layer *layer, GContext* ctx) {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  
  //中心座標取得
  GRect bounds = layer_get_bounds(layer);
  GPoint center = grect_center_point(&bounds);

  //中心点描画
  graphics_context_set_fill_color(ctx, GColorFromRGB ( 170, 85, 0));
  graphics_fill_circle(ctx, center, 3);

  float angle = 0.0f;
  
  float hour = t->tm_hour%12;
  float minute = t->tm_min;
  float second = t->tm_sec;
 
  //分
  angle = minute*6.0f +second*0.1f - 180.0f;
  DrawClock( layer, ctx, center, s_minute_path_ptr, angle, GColorFromRGB ( 255, 170, 170));
  
  //時
  angle = hour*30.0f+minute*0.5f - 180.0f;
  DrawClock( layer, ctx, center, s_hour_path_ptr, angle, GColorFromRGB ( 255, 0, 0));

}
