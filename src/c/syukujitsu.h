#pragma once

/*
 * 結果型
 */
typedef enum { HOLIDAY , WEEKDAY, SYUKUJITSU, C_HOLIDAY } HolidayType;

/*
 * 結果出力コールバック
 */
typedef void (*CallbackResultOut)(char*,struct tm, HolidayType holiday);

/*
 * 祝日取得
 */
HolidayType Syukujitu( int yy, int mm, int dd, int ww, CallbackResultOut callback );
