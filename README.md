# Yandex.Metrica(AppMetrica) for Defold

_“This plugin is not endorsed or sponsored by Yandex LLC. This is an independent, unofficial plugin. “_

[Yandex.Metrica(AppMetrica)](https://appmetrica.yandex.ru/) is a free of charge app analytics tool for Android and iOS.

This native extension doesn't implement all Yandex.Metrica functions, but they are enough to track most of the stats of your game.

## How do I use this extension ?
### 1. Add AppMetrica As Dependency

You can use AppMetrica in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/).

Open your `game.project` file and in the dependencies field under project add:
>https://github.com/osov/defold-app-metrica/archive/master.zip
### 2. Get API KEY
Create an app and get API Key
[AppMetrica](https://appmetrica.yandex.ru/docs/mobile-sdk-dg/android/about/android-initialize.html)

### 3. Call AppMetrica Method

In your `main.script` call `init` to start monitoring. It means, for the AppMetrica, that your game finished loading:

```lua

function init(self)
  appmetrica.set_callback(function()
     print("app metrica initialized")
  end)
  appmetrica.initialize(YOUR_KEY)
end

```

## Send events
```lua
function init(self)
   appmetrica.report_event('game_start', '') -- without parameters
   appmetrica.report_event('game_start',  json.encode({key1 = par1, key2 = par2})) -- or with parameters
end
```
