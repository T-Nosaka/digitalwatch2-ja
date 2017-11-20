#include <pebble.h>
#include <time.h>

#include "syukujitsu.h"


#define SundayDef 0
#define MondayDef 1
#define TuesdayDef 2
#define WednesdayDef 3
#define ThursdayDef 4
#define FridayDef 5
#define SaturdayDef 6

/*
 * 春分計算
 */
static int Syunbun(int yy) 
{
	int dd;
	if (yy <= 1947) 
	{
		dd = 99;
	} 
	else if (yy <= 1979) 
	{
		dd = (int)(20.8357 + (0.242194 * (yy - 1980)) - (int)((yy - 1983) / 4));
	} 
	else if (yy <= 2099) 
	{
		dd = (int)(20.8431 + (0.242194 * (yy - 1980)) - (int)((yy - 1980) / 4));
	} 
	else if (yy <= 2150) 
	{
		dd = (int)(21.851 + (0.242194 * (yy - 1980)) - (int)((yy - 1980) / 4));
	} 
	else 
	{
		dd = 99;
	}
	return dd;
}

/*
 * 秋分計算
 */
static int Syubun(int yy) 
{
	int dd;
	if (yy <= 1947) 
	{
		dd = 99;
	} 
	else if (yy <= 1979) 
	{
		dd = (int)(23.2588 + (0.242194 * (yy - 1980)) - (int)((yy - 1983) / 4));
	} 
	else if (yy <= 2099) 
	{
		dd = (int)(23.2488 + (0.242194 * (yy - 1980)) - (int)((yy - 1980) / 4));
	} 
	else if (yy <= 2150) 
	{
		dd = (int)(24.2488 + (0.242194 * (yy - 1980)) - (int)((yy - 1980) / 4));
	} 
	else 
	{
		dd = 99;
	}
	return dd;
}

/*
 * 日付計算
 */
struct tm * calcdate(int y, int m, int d, int days)
{
    struct tm tm1;
    tm1.tm_sec = 0;
    tm1.tm_min = 0;
    tm1.tm_hour = 0;
    tm1.tm_mday = d;
    tm1.tm_mon = m-1;
    tm1.tm_year = y-1900;
    tm1.tm_wday = 0;
    tm1.tm_yday = 0;
    tm1.tm_isdst = 0;
  
//  = { 0, 0, 0, d, m-1, y-1900 }; 
    time_t time = mktime(&tm1) + 86400 * days;
    return localtime(&time);
}

/*
 * 結果出力
 */
void ResultOut( CallbackResultOut callback, char* mes, struct tm targetdate, HolidayType holiday )
{
	if( callback != NULL )
		callback( mes, targetdate, holiday );
}

/*
 * 祝日取得
 */
HolidayType Syukujitu( int yy, int mm, int dd, int ww, CallbackResultOut callback )
{
	struct tm targetdate = *calcdate(yy,mm,dd,0);

	HolidayType result = WEEKDAY;

	if( ww == SundayDef )
	{
		result = HOLIDAY;
	}
	else
	{
		result = WEEKDAY;
	}

	// 祝日法施行以前
	if (yy<1948 && mm<7 && dd<20 )
		return result;

	switch (mm) 
	{
			// １月 //
		case 1:
			if (dd==1)
			{
				result = SYUKUJITSU;
				ResultOut(callback,"元旦",targetdate,result);
			} 
			else 
			{
				if (yy>=2000)
				{
					if (((int)((dd-1)/7)==1)&&(ww==MondayDef))
					{
						result = SYUKUJITSU;
						ResultOut(callback,"成人の日",targetdate,result);
					}
				} 
				else 
				{
					if (dd==15)
					{
						result = SYUKUJITSU;
						ResultOut(callback,"成人の日",targetdate,result);
					}
				}
			}
			break;
			// ２月 //
		case 2:
			if (dd==11)
			{
				if (yy>=1967)
				{
					result = SYUKUJITSU;
					ResultOut(callback,"建国記念の日",targetdate,result);
				}
			} 
			else if ((yy==1989)&&(dd==24))
			{
				result = SYUKUJITSU;
				ResultOut(callback,"昭和天皇の大喪の礼",targetdate,result);
			}
			break;
			// ３月 //
		case 3:
			if (dd==Syunbun(yy))
			{
				result = SYUKUJITSU;
				ResultOut(callback,"春分の日",targetdate,result);
			}
			break;
			// ４月 //
		case 4:
			if (dd==29)
			{
				if (yy>=2007)
				{
					result = SYUKUJITSU;
					ResultOut(callback,"昭和の日",targetdate,result);
				} 
				else if (yy>=1989)
				{
					result = SYUKUJITSU;
					ResultOut(callback,"みどりの日",targetdate,result);
				} 
				else 
				{
					result = SYUKUJITSU;
					ResultOut(callback,"天皇誕生日",targetdate,result);
				}
			} 
			else if ((yy==1959)&&(dd==10))
			{
				result = SYUKUJITSU;
				ResultOut(callback,"皇太子明仁親王の結婚の儀",targetdate,result);
			}
			break;
			// ５月 //
		case 5:
			if (dd==3)
			{
				result = SYUKUJITSU;
				ResultOut(callback,"憲法記念日",targetdate,result);
			} 
			else if (dd==4)
			{
				if (yy>=2007) 
				{
					result = SYUKUJITSU;
					ResultOut(callback,"みどりの日",targetdate,result);
				} 
				else if (yy>=1986) 
				{
					/* 5/4が日曜日は『只の日曜』､月曜日は『憲法記念日の振替休日』(～2006年)*/
					if (ww > MondayDef)
					{
						result = HOLIDAY;
						ResultOut(callback,"国民の休日",targetdate,result);
					}
				}
			} 
			else if (dd==5) 
			{
				result = SYUKUJITSU;
				ResultOut(callback,"こどもの日",targetdate,result);
			} 
			break;
			// ６月 //
		case 6:
			if ((yy==1993)&&(dd==9))
			{
				result = SYUKUJITSU;
				ResultOut(callback,"皇太子徳仁親王の結婚の儀",targetdate,result);
			}
			break;
			// ７月 //
		case 7:
			if (yy>=2003)
			{
				if (((int)((dd - 1) / 7) == 2) && (ww == MondayDef))
				{
					result = SYUKUJITSU;
					ResultOut(callback,"海の日",targetdate,result);
				}
			} 
			else if (yy>=1996)
			{
				if (dd==20) 
				{
					result = SYUKUJITSU;
					ResultOut(callback,"海の日",targetdate,result);
				}
			}
			break;
			// ８月 //
		case 8:
		    //
		    if (yy >= 2016)
		    {
			if (dd == 11)
			{
			    result = SYUKUJITSU;
			    ResultOut(callback,"山の日",targetdate,result);
			}
		    }

			break;
			// ９月 //
		case 9:
			if (dd==Syubun(yy))
			{
				result = SYUKUJITSU;
				ResultOut(callback,"秋分の日",targetdate,result);
			} 
			else 
			{
				if (yy>=2003) 
				{
					if (((int)((dd - 1) / 7) == 2) && (ww == MondayDef))
					{
						result = SYUKUJITSU;
						ResultOut(callback,"敬老の日",targetdate,result);
					} 
					else if (ww == TuesdayDef)
					{
						if (dd==Syubun(yy)-1)
						{
							result = HOLIDAY;
							ResultOut(callback,"国民の休日",targetdate,result);
						}
					}
				} 
				else if (yy>=1966)
				{
					if (dd==15) 
					{
						result = SYUKUJITSU;
						ResultOut(callback,"敬老の日",targetdate,result);
					}
				}
			}
			break;
			// １０月 //
		case 10:
			if (yy>=2000)
			{
				if (((int)((dd - 1) / 7) == 1) && (ww == MondayDef))
				{
					result = SYUKUJITSU;
					ResultOut(callback,"体育の日",targetdate,result);
				}
			} 
			else if (yy>=1966)
			{
				if (dd==10)
				{
					result = SYUKUJITSU;
					ResultOut(callback,"体育の日",targetdate,result);
				}
			}
			break;
			// １１月 //
		case 11:
			if (dd==3)
			{
				result = SYUKUJITSU;
				ResultOut(callback,"文化の日",targetdate,result);
			} 
			else if (dd==23) 
			{
				result = SYUKUJITSU;
				ResultOut(callback,"勤労感謝の日",targetdate,result);
			} 
			else if ((yy==1990)&&(dd==12))
			{
				result = SYUKUJITSU;
				ResultOut(callback,"即位礼正殿の儀",targetdate,result);
			}
			break;
			// １２月 //
		case 12:
			if (dd==23)
			{
				if (yy>=1989)
				{
					result = SYUKUJITSU;
					ResultOut(callback,"天皇誕生日",targetdate,result);
				}
			}
			break;
		default:
			break;
	}

	//振替休日処理
	//2007年からは日曜日が祝日で,その日曜日から対象日までに振り替える日が無い場合、対象日を振替休日とする。
	if( yy >= 2007 )
	{
		if ( (result == WEEKDAY 
			|| result == HOLIDAY) && callback != NULL )
		{
			int bFurikae = 0;

			int target_y = yy;
			int target_m = mm;
			int target_d = dd;
			int target_w = ww;
			while( 1 )
			{
				struct tm target = *calcdate(target_y,target_m,target_d,-1);
				target_y = target.tm_year+1900;
				target_m = target.tm_mon+1;
				target_d = target.tm_mday;
				target_w = target.tm_wday;
				HolidayType res = Syukujitu( target_y, target_m, target_d, target_w, NULL );
				//前日が平日、休日の場合、振り替えない
				if( res == WEEKDAY || res == HOLIDAY )
					break;
				//既に振り替えている場合、振り替えない
				if( res == C_HOLIDAY )
					break;
				//前日が祝日かつ日曜日の場合、振り替え対象となる。
				if( res == SYUKUJITSU && target_w == SundayDef )
				{
					bFurikae = 1;
					break;
				}
			}

			if( bFurikae == 1 )
			{
				result = C_HOLIDAY;
				ResultOut(callback,"振替休日",targetdate,result);
			}
		}
	}
	else
	{
		if ((result == WEEKDAY 
			|| result == HOLIDAY) && 
			(ww == MondayDef))
		{
			//月曜以外は振替休日判定不要
			//5/6(火,水)の判定は上記ステップで処理済
			//5/6(月)はここで判定する
			if ( yy>=1973 && mm>=7 && dd>=12 ) 
			{
				struct tm target = *calcdate(yy,mm,dd,-1);
				int target_y = target.tm_year+1900;
				int target_m = target.tm_mon+1;
				int target_d = target.tm_mday;
				int target_w = target.tm_wday;

				HolidayType res = Syukujitu( target_y, target_m, target_d, target_w, NULL );

				if( (res == WEEKDAY || res == HOLIDAY) && res == SYUKUJITSU )
				{
					// 再帰呼出
					result = C_HOLIDAY;
					ResultOut(callback,"振替休日",targetdate,result);
				}
			}
		}
	}

	return result;
}
