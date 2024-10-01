// noinspection HttpUrlsUsage, JSUnusedGlobalSymbols, JSUnresolvedReference,DuplicatedCode

import KeyDownEvent = JQuery.KeyDownEvent;

$((): void => {
  const $body = $('body');
  const $overlay = $('.overlay');
  const $blurToggle = $('#blur-toggle');

  const blurBackground: string | null = window.localStorage.getItem('blurBackground');
  if (blurBackground === 'true') {
    $blurToggle.prop('checked', true);
    $body.addClass('blur-background');
    $overlay.addClass('blur-background');
  } else {
    $blurToggle.prop('checked', false);
    $body.removeClass('blur-background');
    $overlay.removeClass('blur-background');
  }

  $('#searchButton').on('click', () => {
    const query: string = String($('#searchBar').val()).trim();
    const lowerCaseQuery: string = query.toLocaleLowerCase()
    if (lowerCaseQuery.startsWith('purr://')) parseSysLink(lowerCaseQuery);
    else if (isValidUrl(query)) window.location.href = query.startsWith('http://') || query.startsWith('https://') ? query : 'https://' + query;
    else window.location.href = 'https://www.google.com/search?q=' + encodeURIComponent(query);
  });

  $('#searchBar').on('keydown', (event: KeyDownEvent<HTMLElement, undefined>) => {
    if (event.key === 'Enter') $('#searchButton').trigger('click');
  });

  function parseSysLink(link: string) {
    const sysLink: string = link.replace('purr://', '');
    switch (sysLink) {
      case "about":
        window.location.href = `about.html`
        break;

      case "weather":
        window.location.href = `weather.html`
        break;

      case "newtab":
        window.location.href = `index.html`
        break;

      case "kitty":
        window.location.href = `kitty.html`
        break;

      case "settings":
        window.location.href = `settings.html`
        break;

      case "error":
        window.location.href = `error.html`
        break;

      default:
        alert("That link doesnt exist!")
    }
  }

  function isValidUrl(query: string) {
    const hasSpace: boolean = query.includes(' ');
    const hasDot: boolean = query.includes('.');
    const isValidFormat: boolean = /^[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)+$/.test(query);
    return !hasSpace && hasDot && isValidFormat;
  }

  $blurToggle.on('change', function () {
    if ($(this).is(':checked')) {
      $body.addClass('blur-background');
      $overlay.addClass('blur-background');
      window.localStorage.setItem('blurBackground', 'true');
    } else {
      $body.removeClass('blur-background');
      $overlay.removeClass('blur-background');
      window.localStorage.setItem('blurBackground', 'false');
    }
  });

  const images: string[] = [
    '1.png', '2.png', '3.png', '4.png', '5.png',
    '6.png', '7.png', '8.png', '9.png', '10.png',
    '11.png', '12.png', '13.png', '14.png', '15.png'
  ];

  let lastIndex: number = -1;

  function setRandomBackground() {
    let randomIndex;

    do randomIndex = Math.floor(Math.random() * images.length);
    while (randomIndex === lastIndex);

    lastIndex = randomIndex;

    const randomImageUrl = `images/wallpaper/${images[randomIndex]}`;

    $body.css({
      'background-image': `url(${randomImageUrl})`,
      'background-size': 'cover',
      'background-position': 'center',
      'background-repeat': 'no-repeat',
    });
  }

  setRandomBackground();
  $('#bgSwitchButton').on('click', setRandomBackground);

  const $city = $('#city');
  const $temperature = $('#temperature');
  const $unit = $('#unit');
  const $weatherIcon = $('#weather-icon');
  const $weatherDescription = $('#weather-description');
  const $weatherContainer = $('.weather-container');

  function fetchWeather() {
    $.getJSON('http://ip-api.com/json', (locationData: any) => {
      const city: any = locationData.city;
      const lat: any = locationData.lat;
      const lon: any = locationData.lon;

      $.ajax({
        url: `https://purrooser-weather.vercel.app/weather?lat=${lat}&lon=${lon}`,
        method: 'GET',
        headers: {
          'Version': 'Purrooser/1.0'
        },
        success: (weatherData: any) => {
          const temperature: number = Math.round(weatherData.main.temp);
          const weatherCode: any = weatherData.weather[0].id;
          const {description, iconUrl} = getWeatherConditionDescription(weatherCode);
          const unit = "°F";

          $city.text(city);
          $temperature.text(`${temperature}`);
          $unit.text(`${unit}`);
          $weatherIcon.attr('src', iconUrl);
          $weatherDescription.text(description);

          $weatherContainer.css({'display': 'flex'});
          $weatherDescription.show();
        },
        error: () => alert("Error loading weather")
      });
    }).fail(() => alert("Error getting IP"));
  }

  fetchWeather();

  function getWeatherConditionDescription(weatherCode: number) {
    const weatherConditions: { [key: number]: { description: string; iconUrl: string } | undefined } = {
      "200": {description: "Thunderstorm with light rain", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "201": {description: "Thunderstorm with rain", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "202": {description: "Thunderstorm with heavy rain", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "210": {description: "Light thunderstorm", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "211": {description: "Thunderstorm", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "212": {description: "Heavy thunderstorm", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "221": {description: "Ragged thunderstorm", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "230": {description: "Thunderstorm with light drizzle", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "231": {description: "Thunderstorm with drizzle", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "232": {description: "Thunderstorm with heavy drizzle", iconUrl: "https://openweathermap.org/img/wn/11d@2x.png"},
      "300": {description: "Light intensity drizzle", iconUrl: "https://openweathermap.org/img/wn/09d@2x.png"},
      "301": {description: "Drizzle", iconUrl: "https://openweathermap.org/img/wn/09d@2x.png"},
      "302": {description: "Heavy intensity drizzle", iconUrl: "https://openweathermap.org/img/wn/09d@2x.png"},
      "310": {description: "Light intensity drizzle rain", iconUrl: "https://openweathermap.org/img/wn/09d@2x.png"},
      "311": {description: "Drizzle rain", iconUrl: "https://openweathermap.org/img/wn/09d@2x.png"},
      "312": {description: "Heavy intensity drizzle rain", iconUrl: "https://openweathermap.org/img/wn/09d@2x.png"},
      "500": {description: "Light rain", iconUrl: "https://openweathermap.org/img/wn/10d@2x.png"},
      "501": {description: "Moderate rain", iconUrl: "https://openweathermap.org/img/wn/10d@2x.png"},
      "502": {description: "Heavy intensity rain", iconUrl: "https://openweathermap.org/img/wn/10d@2x.png"},
      "503": {description: "Very heavy rain", iconUrl: "https://openweathermap.org/img/wn/10d@2x.png"},
      "504": {description: "Extreme rain", iconUrl: "https://openweathermap.org/img/wn/10d@2x.png"},
      "511": {description: "Freezing rain", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "520": {description: "Light intensity shower rain", iconUrl: "https://openweathermap.org/img/wn/09d@2x.png"},
      "521": {description: "Shower rain", iconUrl: "https://openweathermap.org/img/wn/09d@2x.png"},
      "522": {description: "Heavy intensity shower rain", iconUrl: "https://openweathermap.org/img/wn/09d@2x.png"},
      "600": {description: "Light snow", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "601": {description: "Snow", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "602": {description: "Heavy snow", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "611": {description: "Sleet", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "612": {description: "Light shower sleet", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "615": {description: "Shower sleet", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "620": {description: "Light rain and snow", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "621": {description: "Rain and snow", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "622": {description: "Heavy rain and snow", iconUrl: "https://openweathermap.org/img/wn/13d@2x.png"},
      "701": {description: "Mist", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "711": {description: "Smoke", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "721": {description: "Haze", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "731": {description: "Sand, dust whirls", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "741": {description: "Fog", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "751": {description: "Sand", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "761": {description: "Dust", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "771": {description: "Squall", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "781": {description: "Tornado", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "800": {description: "Clear sky", iconUrl: "https://openweathermap.org/img/wn/01d@2x.png"},
      "801": {description: "Few clouds", iconUrl: "https://openweathermap.org/img/wn/02d@2x.png"},
      "802": {description: "Scattered clouds", iconUrl: "https://openweathermap.org/img/wn/03d@2x.png"},
      "803": {description: "Broken clouds", iconUrl: "https://openweathermap.org/img/wn/04d@2x.png"},
      "804": {description: "Overcast clouds", iconUrl: "https://openweathermap.org/img/wn/04d@2x.png"},
      "900": {description: "Tornado", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "901": {description: "Tropical storm", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "902": {description: "Hurricane", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "903": {description: "Cold", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "904": {description: "Hot", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "905": {description: "Windy", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "906": {description: "Hail", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "951": {description: "Calm", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "952": {description: "Light breeze", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "953": {description: "Gentle breeze", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "954": {description: "Moderate breeze", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "955": {description: "Fresh breeze", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "956": {description: "Strong breeze", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "957": {description: "High wind, near gale", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "958": {description: "Gale", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "959": {description: "Severe gale", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "960": {description: "Storm", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "961": {description: "Violent storm", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
      "962": {description: "Hurricane", iconUrl: "https://openweathermap.org/img/wn/50d@2x.png"},
    };

    return weatherConditions[weatherCode] || {description: "Unknown weather condition", iconUrl: ""};
  }
});
