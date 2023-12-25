struct Country {
    string country_name;
    vector<City> cities;
    string country_iso_code;
    string country_phone_code;
    string country_time_zone;
    vector<Language> languages;    
}

...

// Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
void ParseCitySubjson(Country& country, const Json& json) {
    for (const auto& city_json : json.AsList()) {
        const auto& city_obj = city_json.AsObject();
        country.cities.push_back({city_obj["name"s].AsString(), city_obj["iso_code"s].AsString(),
                          countryo.country_phone_code + city_obj["phone_code"s].AsString(), 
                          country.country_name, 
                          country.country_iso_code,
                          country.country_time_zone, 
                          country.languages});
    }
}

// ParseCitySubjson вызывается только из функции ParseCountryJson следующим образом:
void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString(),
        });
        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        ParseCitySubjson(country, country_obj["cities"s]);
    }
}