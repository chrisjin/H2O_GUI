H2O_GUI
============
Features
----------------
* Font rendering based on FreeType
* IME support
* Renderer based on Win32 GDI
* Native cpp implementation of signal and slot
* Mouse， keyboard, etc. events 
* Basic controls including,
	* Button
	* TextEdit (With IME support, Unicode support)
	* GifPlayer

Demos
-----------------
<p>
	Button down
	![btndown](https://github.com/chrisjin/MyResources/blob/master/H2O/btndown.png)
<p> 
	Button up
	![btnup](https://github.com/chrisjin/MyResources/blob/master/H2O/btnup.png)
<p>
	Chinese input
	![chineseinput](https://github.com/chrisjin/MyResources/blob/master/H2O/chinese.png)
<p>
	A simple gif player.
![Gifplayer](https://github.com/chrisjin/MyResources/blob/master/H2O/GIFPlayer.PNG)
<p>
	A demo start screen of a game
![GamePanel](https://github.com/chrisjin/MyResources/blob/master/H2O/Panel.png)


Code Samples
-------------------
<p>
	Signal-slot system based on member function pointer:
```
	startbutton->connect(Button::s_clicked, this, &WidgetTest::start);
```

```
	void WidgetTest::start()
	{
		gifplayer->start();
	}
```

<p>
	Add control:

```
	innerbt = new Button(Point2D(60, 30), Size2D(80, 40));
	innerbt->setText("Play");
	AddTile(innerbt);

	gifplayer = new GIFPlayer(Point2D(0,0));
	gifplayer->loadGIF("src/BTNSpellBreaker.gif");
	addTile(gifplayer);
```

