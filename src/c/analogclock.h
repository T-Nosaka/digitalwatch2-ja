#pragma once


/*
 * アナログ時計セットアップ
 */
void setup_analogclock();

/*
 * アナログ時計破棄
 */
void destroy_analogclock();

/*
 * アナログ時計レイヤー更新
 */
void analogclock_layer_update_callback(Layer *layer, GContext* ctx);

