# Yandex.Metrica(AppMetrica) for Defold

*This is an open-source project. It is not affiliated with Yandex LLC.*

*This extension is independent and unofficial, and not associated with Yandex LLC in any way.*

[Yandex.Metrica(AppMetrica)](https://appmetrica.yandex.ru/) is a free of charge app analytics tool for android.

This native extension doesn't implement all Yandex.Metrica functions, but they are enough to track most of the stats of your game.

ATTENTION! Currently only Android SDK is supported! No iOs support in current implementation!
## Supported Platforms

| Platform        | Status |
| --------------- | ------ |
| Android         | Supported ✅ |

## Installation & Usage
### 1. Add AppMetrica As Dependency

You can use AppMetrica in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/).

Open your `game.project` file and in the dependencies field under project add:
>https://github.com/osov/defold-yandex-metrica/archive/master.zip
### 2. Get API KEY
Create an app and get API Key
[AppMetrica](https://appmetrica.yandex.ru/docs/mobile-sdk-dg/android/about/android-initialize.html)

### 3. Call AppMetrica Method

In your `main.script` call `init` to start monitoring. It means, for the AppMetrica, that your game finished loading:

```lua
-- callback loaded(optional)
function listener(event)
	print('appmetrica event type', event.type)
	print('appmetrica event phase', event.phase)
end

function init(self)
 appmetrica.init{
   key = "YOU_KEY",	
   listener = listener
  }
end

```
