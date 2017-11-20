
/*
 * 天気取得
 */
function fetchWeather(latitude, longitude) {
  
  var keyid = "fe3e9f8106b81b2be9cc04cf3d6f25f9";
  
  var req = new XMLHttpRequest();
  req.open('GET', "http://api.openweathermap.org/data/2.5/weather?" +
    "lat=" + latitude + "&lon=" + longitude + "&cnt=1" + "&APPID=" + keyid, true);

  req.onload = function(e) {
    if (req.readyState == 4) {
      if(req.status == 200) {
        console.log(req.responseText);

        var response = JSON.parse(req.responseText);
        var temperature = Math.round(response.main.temp - 273.15);
        var icon = response.weather[0].id;
        var city = response.name;
        console.log("temp:"+temperature);
        console.log("icon:"+icon);
        console.log("city:"+city);
        Pebble.sendAppMessage({"WEATHER_ICON_KEY":icon.toString(10)},function() {
           Pebble.sendAppMessage({"WEATHER_TEMPERATURE_KEY":temperature + "\u00B0C"},
              function() {
                  convGoogleMap(latitude, longitude);
              });
        });
/*        
        Pebble.sendAppMessage({
          "WEATHER_ICON_KEY":icon.toString(10),
          "WEATHER_TEMPERATURE_KEY":temperature + "\u00B0C",
          "WEATHER_CITY_KEY":"天候:" + city}
        );
*/
      } else {
        console.log("Error");
      }
    }
  }
  req.send(null);
}

/*
 * グーグル場所取得
 */
function convGoogleMap(lat,lon) {
  
  var req = new XMLHttpRequest();
  req.open('GET', "https://maps.googleapis.com/maps/api/geocode/json?language=ja&latlng="+lat+","+lon, true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if(req.status == 200) {
        
        var response = JSON.parse(req.responseText);
        var entry = response.results;
        var locateresult;
        for(var i in entry){
          locateresult=entry[i].formatted_address.toString();
          break;
        }
        console.log(locateresult);
        Pebble.sendAppMessage({"WEATHER_CITY_KEY":locateresult});
      }
    }
  }
  req.send(null);
}

/*
 * ニュース送信
 */
function sendGoogleNews( newslist, idx, len, finishcallback ) {
  console.log(idx,'/',len,':',newslist[idx]);
  
  if( idx < len)
  {
    Pebble.sendAppMessage({"NEWS_RES_TITLE_KEY0":newslist[idx]},
                         function()
                          {
                            console.log('sendGoogleNews success');
                            sendGoogleNews( newslist, idx+1, len, finishcallback );
                          },
                         function(e)
                          {
                            console.log('sendGoogleNews error');
                            finishcallback();
                          });
  }
  else
    finishcallback();
}

/*
 * グーグルニュース取得
 */
function fetchGoogleNews( kind ) {
  
  // https://news.google.com/news?hl=ja&ned=us&ie=UTF-8&oe=UTF-8&output=rss&topic=p
  //topic=p,w,s
  
  var req = new XMLHttpRequest();
  
  if( kind == 0 )
    req.open('GET', "https://news.google.com/news?hl=ja&ned=us&ie=UTF-8&oe=UTF-8&output=rss&topic=h", true);
  else
  if( kind == 1 )
    req.open('GET', "https://news.google.com/news?hl=ja&ned=us&ie=UTF-8&oe=UTF-8&output=rss&topic=ir", true);
  else
  if( kind == 2 )
    req.open('GET', "https://news.google.com/news?hl=ja&ned=us&ie=UTF-8&oe=UTF-8&output=rss&topic=w", true);
  else
  if( kind == 3 )
    req.open('GET', "https://news.google.com/news?hl=ja&ned=us&ie=UTF-8&oe=UTF-8&output=rss&topic=p", true);
  else
  if( kind == 4 )
    req.open('GET', "https://news.google.com/news?hl=ja&ned=us&ie=UTF-8&oe=UTF-8&output=rss&topic=e", true);
  else
  if( kind == 5 )
    req.open('GET', "https://news.google.com/news?hl=ja&ned=us&ie=UTF-8&oe=UTF-8&output=rss&topic=s", true);
  else
  if( kind == 6 )
    req.open('GET', "https://news.google.com/news?hl=ja&ned=us&ie=UTF-8&oe=UTF-8&output=rss&topic=t", true);
  else
    return;
  req.onload = function(e) {
    if (req.readyState == 4) {
      if(req.status == 200) {
        var newslist = new Array();
        var responce = xml2json.parser(req.responseText);
        var entry = responce.rss.channel.item
        for(var i=0; i<entry.length; i++){
          newslist.push(entry[i].title);
          
          if( i>=4 )  //リミット4つまで
            break;
        }
       
        console.log('news count:',newslist.length);
        
        sendGoogleNews( newslist, 0, newslist.length, fetchGoogleNews.bind(this, kind+1) );
      }
    }
  }
  req.send(null);
}

/*
 * 位置情報取得成功
 */
function locationSuccess(pos) {
  var coordinates = pos.coords;
  
  //取得した位置情報を記録する。
  localStorage.setItem('lastlocation', JSON.stringify({ lat: coordinates.latitude, lon: coordinates.longitude }));
  
  console.log("locationSuccess:lat="+coordinates.latitude+":log="+coordinates.longitude );
  fetchWeather(coordinates.latitude, coordinates.longitude);
}

/*
 * 位置情報取得失敗
 */
function locationError(err) {
//  console.warn('location error (' + err.code + '): ' + err.message);
  
  var locationjson = localStorage.getItem('lastlocation');
  if( locationjson !== null )
  {
      var location = JSON.parse(locationjson);
      console.log("last location:lat="+location.lat+":log="+location.lon );

      fetchWeather( location.lat, location.lon );
  }
  else {
     Pebble.sendAppMessage({
       "WEATHER_CITY_KEY":"0",
       "WEATHER_CITY_KEY":"",
       "WEATHER_TEMPERATURE_KEY":""
     });
  }
}

/*
 * 位置情報取得タイムアウト設定
 */
var locationOptions = { "timeout": 30000, "maximumAge": 120000 }; 

/*
 * 起動インベト設定
 */
Pebble.addEventListener("ready", function(e) {
  console.log("connect!" + e.ready);
//  locationWatcher = window.navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
//  console.log(e.type);
});

/*
 * メッセージ受信イベント設定
 */
Pebble.addEventListener("appmessage", function(e) {
  console.log("appmessage!");

    if( e.payload["NEWS_REQUEST_KEY"] == 1 ) {
    console.log("NEWS_REQUEST_KEY");
    fetchGoogleNews(0);
  }

  if( e.payload["WEATHER_REQUEST_KEY"] == 1 ) {
    console.log("WEATHER_REQUEST_KEY");
    window.navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
  }

//  console.log(e.type);
//  console.log(e.payload.temperature);
});

/*
 * 終了イベント設定
 */
Pebble.addEventListener("webviewclosed", function(e) {
  console.log("webview closed");
  console.log(e.type);
  console.log(e.response);
});


