// noinspection DuplicatedCode,HttpUrlsUsage,JSUnresolvedReference

import { weatherConditions } from '../main/core.js'

$((): void => {
  const $city = $('#city');
  const $temperature = $('#temperature');
  const $unit = $('#unit');
  const $weatherIcon = $('#weather-icon');
  const $weatherDescription = $('#weather-description');
  const $weatherContainer = $('.weather-container');
  const $datetime = $('#datetime');
  const $humidity = $('#humidity');

  setInterval(updateDateTime, 500);
  fetchWeather();

  function updateDateTime() {
    $datetime.text(new Date().toLocaleString());
  }

  function fetchWeather() {
    $.getJSON('http://ip-api.com/json', (locationData: any) => {
      const city: string | undefined = locationData.city;
      const lat: number | undefined = locationData.lat;
      const lon: number | undefined = locationData.lon;

      if (!city || !lat || !lon) {
        alert("Error parsing location data");
        return;
      }

      $.ajax({
        url: `https://purrooser-weather.vercel.app/weather?lat=${lat}&lon=${lon}`,
        method: 'GET',
        headers: { 'Version': 'Purrooser/1.0' },
        success: (weatherData: any) => {
          const temperature = Math.round(weatherData.main?.temp ?? 0);
          const weatherCode = weatherData.weather?.[0]?.id ?? 0;
          const humidity = weatherData.main?.humidity ?? 0;
          const { description, iconUrl } = getWeatherConditionDescription(weatherCode);
          const unit = "°F";

          $city.text(city);
          $temperature.text(`${temperature}`);
          $unit.text(`${unit}`);
          $weatherIcon.attr('src', iconUrl);
          $weatherDescription.text(description);
          $humidity.text(`${humidity}`);

          $weatherContainer.css({ 'display': 'flex' });
          $weatherDescription.show();

          updateDateTime();
        },
        error: () => alert("Error loading weather")
      });
    }).fail(() => alert("Error getting IP"));
  }

  function getWeatherConditionDescription(weatherCode: number) {
    return weatherConditions[weatherCode] || {description: "Unknown weather condition", iconUrl: ""};
  }
});
